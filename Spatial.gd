extends Spatial

var server := UDPServer.new()
var peers = []

var map_id:int = 0
var feet_unset = true


var map_is_open: bool
var compass_is_top_right: bool

var edit_panel_open: bool = true

# This is the path to the texture that will be used for the next created 3d-path
# object or icon object in the UI
var next_texture_path: String = ""

# A pointer to the path object that any new nodes should be appended to. If
# the value is null then a new path will be created the next time a path point
# will be created.
var currently_active_path = null
var currently_active_path_2d = null

# Called when the node enters the scene tree for the first time.
func _ready():
	get_tree().get_root().set_transparent_background(true)
	#ProjectSettings.set_setting("display/window/size/always_on_top", true)
	#OS.set_window_always_on_top(true)

	OS.window_maximized = false
	OS.window_size = Vector2(1920, 1080)
	set_minimal_mouse_block()
	server.listen(4242)
	self.feet_unset = true
	# load_taco_markers("/home/vault/Downloads/tw_ALL_IN_ONE/tw_mc_coretyria.xml")

func set_minimal_mouse_block():
	var top_corner := Vector2(287, 0)
	var bottom_corner := Vector2(314, 32)
	
	if self.edit_panel_open:
		bottom_corner.y = 49
		bottom_corner.x = 314+377
	
	var clickthrough: PoolVector2Array = [
		Vector2(top_corner.x ,top_corner.y),
		Vector2(bottom_corner.x, top_corner.y),
		Vector2(bottom_corner.x,bottom_corner.y),
		Vector2(top_corner.x ,bottom_corner.y)
	]
	OS.set_window_mouse_passthrough(clickthrough)
	$Control/Border.hide()

func set_maximal_mouse_block():
	OS.set_window_mouse_passthrough([])
	$Control/Border.show()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	#OS.window_position = Vector2(1920, 0) # TODO: This does not seem to work	
	#OS.set_window_position(Vector2(1920,0))
	#print(OS.window_position)
	
	#$MeshInstance.rotate(Vector3(0,1,0), .5 * delta)
	#$MeshInstance.rotate_object_local(Vector3(1,0,0), 1 * delta)
	# print(delta)
	server.poll() # Important
	if server.is_connection_available():
		var peer: PacketPeerUDP = server.take_connection()
#		var pkt = peer.get_packet()
		print("accepted peer: %s:%s" % [peer.get_packet_ip(), peer.get_packet_port()])
#		print("Received data: %s" % [pkt.get_string_from_utf8()])
		
#		print(peer.is_listening())

		#peer.put_packet(pkt)
		peers.append(peer)
#		print(len(peers))
	for i in range(0, peers.size()):
		var peer: PacketPeerUDP = peers[i]
		for j in range(0, peer.get_available_packet_count()):
			
			var spb := StreamPeerBuffer.new()
			spb.data_array = peer.get_packet()
			
			var packet_type:int = spb.get_8()
			
			if packet_type == 1:
				decode_frame_packet(spb)
			elif packet_type == 2:
				decode_context_packet(spb)

	return
var map_was_open = false

var last_update:float = 0
var last_player_location := Vector3(0,0,0)
var last_camera_location := Vector3(0,0,0)
var last_camera_location_at_player_location_change := Vector3(0,0,0)
var player_position := Vector3(0,0,0)
var z_innacurate_player_position := Vector3(0,0,0)
func decode_frame_packet(spb: StreamPeerBuffer):
	
	# Delta calculation for between messages
	#var this_update: float = float(OS.get_ticks_usec()/1000000.0)
	#print("d",this_update - last_update)
	#last_update=this_update
	
	var camera_position = Vector3(
		spb.get_float(),
		spb.get_float(),
		spb.get_float()
	)
	var camera_facing = Vector3(
		spb.get_float(),
		spb.get_float(),
		spb.get_float()
	)
	player_position = Vector3( # Foot Position
		spb.get_float(),
		spb.get_float(),
		spb.get_float()
	)
	var map_offset = Vector2(
		spb.get_float(),
		spb.get_float()
	)
	var map_scale: float = spb.get_float()
	if map_scale == 0: #fixing a divide by zero error that occurs when the game loads
		map_scale = 0.000001
	var map_rotation: float = spb.get_float()
	var ui_flags: int = spb.get_32()
	
	map_is_open = (ui_flags & 0x01) == 0x01;
	compass_is_top_right = (ui_flags & 0x02) == 0x02;
	var compass_rotation_is_enabled: bool = (ui_flags & 0x04) == 0x04;
	var game_is_focused: bool = (ui_flags & 0x08) == 0x08;
	var in_competitive_game_mode: bool = (ui_flags & 0x10) == 0x10;
	var chatbox_has_focus: bool = (ui_flags & 0x20) == 0x20;
	var in_combat: bool = (ui_flags & 0x40) == 0x40;
	var unchecked_flag = (ui_flags & 0xFFFFFF80) != 0x00000000;
	
#	var map_size = spb.get_float()

	
	if map_is_open != map_was_open:
		$Paths.visible = !map_is_open
		$Icons.visible = !map_is_open
		reset_minimap_masks()
		map_was_open = map_is_open

	if unchecked_flag:
		print("Unchecked Flag", (ui_flags & 0xFFFFFF80))
	
#	if game_is_focused:
#		print("game_is_focused")
#	else:
#		print("game is not focused")

#	print("chatbox has focus ", chatbox_has_focus)
	
	# Position the camera in the same location as it in in-game
	$CameraMount.translation.x = camera_position.x
	$CameraMount.translation.y = camera_position.y
	$CameraMount.translation.z = -camera_position.z
#	if ((player_position - last_player_location).length() != 0 || (camera_position - last_camera_location).length() != 0):
#		print(camera_position.x - last_camera_location.x, "\t" ,player_position.x - last_player_location.x)
#		last_camera_location_at_player_location_change = camera_position
#	last_player_location = player_position
#	last_camera_location = camera_position
	
	# Orent the camera in the same rotation as it is facing in game
	$CameraMount/Camera.rotation.x = asin(camera_facing.y)
	$CameraMount.rotation.y = -atan2(camera_facing.x, camera_facing.z)
	#print(-atan2(camera_facing.x, camera_facing.z))
	
	#$MiniMap
	#print(map_scale)
	var map_scale_min = 0.853334
	var map_scale_max = 17.066666
	var map_scale_difference = map_scale_max / map_scale_min
	var default_size = 1.925
	var smallest_relative_scale =  default_size / map_scale_difference

	# in-engine units are meters
	# in-game units are inches
	# continent map units are 24inches to 1 condinenet map unit
	# 1 meter = 39.37008 inches
	# 39.37008 / 24 = 1.64042
	# meters -> 24 inches
	# Info gathered from https://wiki.guildwars2.com/wiki/API:Maps
	var map_object_scaling = 1.64042/map_scale

	var map_size = get_viewport().size
	var map_corner = Vector2(0, 0)
	
	if (!map_is_open):
		map_size = Vector2(compass_width, compass_height)
		if !compass_is_top_right:
			map_corner = get_viewport().size - Vector2(compass_width, compass_height + 36)
		else:
			map_corner = Vector2(get_viewport().size.x - compass_width, 0)

	var player_map_position: Vector2 = Vector2(player_position.x, -player_position.z)*map_object_scaling

	var delta_position = Vector2(0,0)
	if (map_rotation != 0 && !map_is_open):
		var pivot = Vector2(0,0)
		var radians = map_rotation

		var cosTheta = cos(radians)
		var sinTheta = sin(radians)

		var x = (cosTheta * (player_map_position.x - pivot.x) - sinTheta * (player_map_position.y - pivot.y) + pivot.x);
		var y = (sinTheta * (player_map_position.x - pivot.x) + cosTheta * (player_map_position.y - pivot.y) + pivot.y);
		
		delta_position = player_map_position - Vector2(x, y);
		
		#print(map_rotation)
		$Control/MiniMap.rotation = map_rotation
	else:
		$Control/MiniMap.rotation = 0
	
	var map_midpoint = map_size/2 + map_corner;
	
	$Control/MiniMap.scale=Vector2(map_object_scaling, map_object_scaling)
	#print(map_offset)
	var map_translation = map_offset
	$Control/MiniMap.position = (map_translation / map_scale) + map_midpoint - player_map_position + delta_position
	

	
	
	#map_scale: float = spb.get_float()
	#var map_rotation: float = spb.get_float()
	#print(map_scale) #0.853334 -> 17.066666   for the megamap
	# This should be transformed into 2 -> something smaller 
	# minimap 1 -> 4.125
	#print(map_rotation) # Not used for megamap
	
	var new_feet_location = Vector3(player_position.x, player_position.y, -player_position.z)
	#print(player_position)
	$FeetLocation.translation = new_feet_location

#var new_feet_location = Vector3(camera_position.x, camera_position.y-1, -camera_position.z+5)
#	if feet_unset:
#		$FeetLocation.translation = new_feet_location
#		feet_unset = false
#	else:
#		$FeetLocation.moveto(new_feet_location)
#		print(this_update - last_update)
	
	#$FeetLocation.translation.x = player_position.x
	#$FeetLocation.translation.y = player_position.y
	#$FeetLocation.translation.z = -player_position.z
	#print(player_position.x)
#	print(map_is_open, map_rotation, map_offset)



func remap(min_in, max_in, min_out, max_out, value):
	return (value - min_in) / (max_in - min_in) * (max_out - min_out) + min_out


var compass_height: int = 0;
var compass_width: int = 0;
func decode_context_packet(spb: StreamPeerBuffer):
	compass_width = spb.get_16()
	compass_height = spb.get_16()
	var old_map_id = self.map_id
	self.map_id  = spb.get_32()

	var identity_length: int = spb.get_32()
	var identity_str = spb.get_utf8_string(identity_length)
	var identity = JSON.parse(identity_str).result
	
	# FOV Calculations
	# The minimum value on the FOV slider gives a float value in this field of 0.436
	# The maximum value on the FOV slider gives a float value in this field of 1.222
	# According to https://thatshaman.com/tools/fov/ the FOV range is (25 -> 70)
	# This function maps a value between 0.436 and 1.222 to a value between 25 and 70
	$CameraMount/Camera.fov = (((identity["fov"] - 0.436) / 0.786) * 45) + 25

	if self.map_id != old_map_id:
		print("New Map")
		gen_map_markers()

	# TODO move this to reset_minimap_masks
	for child in $Paths.get_children():
		child.get_node("CSGPolygon").material.set_shader_param("map_size", Vector2(compass_width, compass_height))
	
	# TODO move this to reset_minimap_masks
	for icon in $Icons.get_children():
		icon.material_override.set_shader_param("map_size", Vector2(compass_width, compass_height))

	reset_minimap_masks()

var compass_corner1
var compass_corner2
func reset_minimap_masks():
	var viewport_size = get_viewport().size
	compass_corner1 = Vector2(0, 0)
	compass_corner2 = viewport_size
	if !map_is_open && !compass_is_top_right:
		compass_corner1 = Vector2(viewport_size.x-compass_width, 36)
		compass_corner2 = compass_corner1 + Vector2(compass_width, compass_height)
	elif !map_is_open && compass_is_top_right:
		compass_corner1 = viewport_size - Vector2(compass_width, compass_height)
		compass_corner2 = compass_corner1 + Vector2(compass_width, compass_height)
	
	for minimap_path in $Control/MiniMap.get_children():
		minimap_path.material.set_shader_param("minimap_corner", compass_corner1)
		minimap_path.material.set_shader_param("minimap_corner2", compass_corner2)

var markerdata = {}
var marker_file_path = ""
func load_taco_markers(marker_json_file):
	self.marker_file_path = marker_json_file
	print("Loading Path", marker_json_file)
	
	var file = File.new()
	file.open(marker_json_file, file.READ)
	var text = file.get_as_text()
	self.markerdata = JSON.parse(text).result
	#print(self.markerdata)
	gen_map_markers()

var path_scene = load("res://Path.tscn")
var icon_scene = load("res://Icon.tscn")
var path2d_scene = load("res://Path2D.tscn")
var gizmo_scene = load("res://Gizmo/PointEdit.tscn")
##########Gizmo Stuff###########3
# How long the ray to search for 3D clickable object should be.
# Shorter is faster but cannot click thing far away.
# Longer is slower but can click things farther away.
var ray_length = 1000

# The last object that was hovered by the mouse. May be null, may be a dangling
# reference to a non-existant node.
var last_hover = null

# The last object that was selected by a click. May be null, may be a dangling
# reference to a non-existant node.
var last_selected = null

################################################################################
# Hand the mouse input of clicking and hovering over an object
################################################################################
func _input(event):
	# If the left mouse button is clicked.
	if event is InputEventMouseButton and event.pressed and event.button_index == 1:
		# Emit a ray from the mouse position to see if it intersects with any
		# clickable items.
		var camera = $CameraMount/Camera
		var start_coordinate = camera.project_ray_origin(event.position)
		var end_coordinate = start_coordinate + camera.project_ray_normal(event.position) * self.ray_length
		var space_state = get_world().direct_space_state
		var result = space_state.intersect_ray(start_coordinate, end_coordinate)

		# If if the ray intersects with a node then the mouse successfully
		# clicked something.
		if result:
			if is_instance_valid(self.last_selected) and self.last_selected.has_method("clear_selection") and self.last_selected != result["collider"].get_parent():
				last_selected.clear_selection()
			# Call the select() function on the object that was clicked
			result["collider"].select(camera, event)
			self.last_selected = result["collider"].get_parent()
		else:
			if is_instance_valid(self.last_selected) and self.last_selected.has_method("clear_selection"):
				last_selected.clear_selection()
			self.last_selected = null

	# If the mouse is moved.
	if event is InputEventMouseMotion:
		# Emit a ray from the mouse position to see if it intersects with any
		# clickable items.
		var camera = $CameraMount/Camera
		var start_coordinate = camera.project_ray_origin(event.position)
		var end_coordinate = start_coordinate + camera.project_ray_normal(event.position) * self.ray_length
		var space_state = get_world().direct_space_state
		var result = space_state.intersect_ray(start_coordinate, end_coordinate)

		# If the ray intersects with a node then the mouse is visually hovering
		# over something.
		if result:
			# If there is something that is currently hovered then unhover it
			if is_instance_valid(self.last_hover) and self.last_hover.has_method("unhover") and self.last_hover != result["collider"]:
				self.last_hover.unhover()
			# Call the hover function on the new object that is being hovered
			result["collider"].hover()
			self.last_hover = result["collider"]
		# If nothing is hovere then try to unhover the object and set the
		# currently hovered object to null.
		else:
			if is_instance_valid(self.last_hover) and self.last_hover.has_method("unhover"):
				self.last_hover.unhover()
			self.last_hover = null
			
			
################################################################################
#
################################################################################
var path_3d_markers: Array
var path_2d_markers: Array
var icon_markers: Array
var area_3d_markers: Array
var area_2d_markers: Array
onready var icons = $Icons
onready var paths = $Paths
onready var minimap = $Control/MiniMap

func gen_map_markers():
	for child in paths.get_children():
		child.queue_free()
		path_3d_markers.clear()

	for path2d in minimap.get_children():
		path2d.queue_free()
		path_2d_markers.clear()
		
	for icon in icons.get_children():
		icon.queue_free()
		icon_markers.clear()
	


	if str(map_id) in markerdata:
#		print("Found Map")


		var map_markerdata = markerdata[str(map_id)]
#		print("Paths Found:", len(map_markerdata["paths"]))
		for path in map_markerdata["paths"]:
			var texture_path = self.marker_file_path.get_base_dir() + "/"+ path["texture"]
			gen_new_path(path["points"], texture_path)
			
#			var points_2d: PoolVector2Array = [] 
#
#			# Create a new 3D path
#			var new_path = path_scene.instance()
#			var new_curve = Curve3D.new()
#			for point in path["points"]:
#				new_curve.add_point(Vector3(point[0], point[1], -point[2]))
#				points_2d.append(Vector2(point[0], -point[2]))
#
#			new_path.curve = new_curve
#			path_3d_markers.append(new_path)
#			paths.add_child(new_path)
#
#			var texture_file = File.new()
#			var image = Image.new()
#			texture_file.open(self.marker_file_path.get_base_dir() + "/"+ path["texture"], File.READ)
#			image.load_png_from_buffer(texture_file.get_buffer(texture_file.get_len()))
#			texture_file.close()
#			image.lock()
#
#			var texture = ImageTexture.new()
#			texture.create_from_image(image, 6)
#			new_path.get_node("CSGPolygon").material.set_shader_param("texture_albedo", texture)
#
#			# Create a new 2D Path
#			var new_2d_path = path2d_scene.instance()
#			new_2d_path.points = points_2d
#			new_2d_path.texture = texture
#			path_2d_markers.append(new_2d_path)
#			minimap.add_child(new_2d_path)
#
#			self.currently_active_path = new_path
#			self.currently_active_path_2d = new_2d_path

		for icon in map_markerdata["icons"]:
			var position = Vector3(icon["position"][0], icon["position"][1], icon["position"][2])
			var texture_path = self.marker_file_path.get_base_dir() + "/"+ icon["texture"]
			gen_new_icon(position, texture_path)
#			var new_icon = icon_scene.instance()
#			new_icon.translation = Vector3(icon["position"][0], icon["position"][1], -icon["position"][2])
#
#			var texture_file = File.new()
#			var image = Image.new()
#			texture_file.open(self.marker_file_path.get_base_dir() + "/"+ icon["texture"], File.READ)
#			image.load_png_from_buffer(texture_file.get_buffer(texture_file.get_len()))
#			texture_file.close()
#			image.lock()
#
#			var texture = ImageTexture.new()
#			texture.create_from_image(image) #, 6)
#			new_icon.texture = texture
#			new_icon.material_override.set_shader_param("texture_albedo", texture)
#
#			icon_markers.append(new_icon)
#			icons.add_child(new_icon)

func gen_new_path(points: Array, texture_path: String):
	var points_2d: PoolVector2Array = [] 

	# Create a new 3D path
	var new_path = path_scene.instance()
	var new_curve = Curve3D.new()
	for point in points:
		new_curve.add_point(Vector3(point[0], point[1], -point[2]))
		points_2d.append(Vector2(point[0], -point[2]))

	new_path.curve = new_curve
	path_3d_markers.append(new_path)
	paths.add_child(new_path)
	
	var texture_file = File.new()
	var image = Image.new()
	texture_file.open(texture_path, File.READ)
	image.load_png_from_buffer(texture_file.get_buffer(texture_file.get_len()))
	texture_file.close()
	image.lock()
	
	var texture = ImageTexture.new()
	texture.create_from_image(image, 6)
	new_path.get_node("CSGPolygon").material.set_shader_param("texture_albedo", texture)
	
	# Create a new 2D Path
	var new_2d_path = path2d_scene.instance()
	new_2d_path.points = points_2d
	new_2d_path.texture = texture
	path_2d_markers.append(new_2d_path)
	minimap.add_child(new_2d_path)
	
	self.currently_active_path = new_path
	self.currently_active_path_2d = new_2d_path

func gen_new_icon(position: Vector3, texture_path: String):
	position.z = -position.z

	print("Generating Icon at", position, "with texture", texture_path)
	var new_icon = icon_scene.instance()
	new_icon.translation = position
			
	var texture_file = File.new()
	var image = Image.new()
	texture_file.open(texture_path, File.READ)
	image.load_png_from_buffer(texture_file.get_buffer(texture_file.get_len()))
	texture_file.close()
	image.lock()
			
	var texture = ImageTexture.new()
	texture.create_from_image(image) #, 6)
	new_icon.texture = texture
	new_icon.material_override.set_shader_param("texture_albedo", texture)
			
	icon_markers.append(new_icon)
	icons.add_child(new_icon)

func _on_main_menu_toggle_pressed():
	$Control/Dialogs/MainMenu.show()	
	set_maximal_mouse_block()

func _on_FileDialog_file_selected(path):
	load_taco_markers(path)

################################################################################
# The adjust nodes button creates handles at all the node points to allow for
# editing of them via in-game interface. (Nodes can only be edited if the input
# passthrough is blocked, thus preventing any camera movement or player movement
################################################################################
var adjusting = false
func _on_AdjustNodesButton_pressed():
	if self.adjusting:
		self.adjusting = false
		clear_adjustment_nodes()
		set_minimal_mouse_block()		
	else:
		self.adjusting = true
		set_maximal_mouse_block()
		
		for index in range(len(path_3d_markers)):
			var path = path_3d_markers[index]
			var path2d = path_2d_markers[index]
			var curve: Curve3D = path.curve
			for i in range(curve.get_point_count()):
				var new_gizmo = gizmo_scene.instance()
				new_gizmo.translation = curve.get_point_position(i)
				new_gizmo.link_point("path", path, path2d, i)
				$Gizmos.add_child(new_gizmo)
		
		for index in range(len(icon_markers)):
			var icon = icon_markers[index]
			var new_gizmo = gizmo_scene.instance()
			new_gizmo.translation = icon.translation
			new_gizmo.link_point("icon", icon)
			$Gizmos.add_child(new_gizmo)
			
func clear_adjustment_nodes():
	for child in $Gizmos.get_children():
		child.queue_free()


func _on_Dialog_hide():
	for dialog in $Control/Dialogs.get_children():
		if dialog.visible:
			return
	set_minimal_mouse_block()


func _on_LoadPath_pressed():
	var open_dialog: FileDialog = $Control/Dialogs/FileDialog
	open_dialog.show()
	open_dialog.set_current_dir(open_dialog.current_dir)


func _on_RangesButton_pressed():
	$Control/Dialogs/RangesDialog.show()

var path_resolution = 1
func _on_PathResolution_value_changed(value):
	path_resolution = value
	
	for path in $Paths.get_children():
		var csg:CSGPolygon = path.get_node("CSGPolygon")
		csg.path_interval = path_resolution
		csg.material.set_shader_param("interval", path_resolution)



func _on_CloseEditorQuickPanel_pressed():
	$Control/GlobalMenuButton/EditorQuckPanel.hide()
	edit_panel_open = false

func _on_OpenEditorQuickPanel_pressed():
	$Control/GlobalMenuButton/EditorQuckPanel.show()
	edit_panel_open = true


func _on_ChangeTexture_pressed():
	$Control/Dialogs/TexturePathOpen.show()
	var texture_path_dialog:FileDialog = $Control/Dialogs/TexturePathOpen
	texture_path_dialog.set_current_dir(texture_path_dialog.current_dir)
	set_maximal_mouse_block()

################################################################################
# Set the file that will be used to create a new path or icon when a new path
# or icon is created.
################################################################################
func _on_TexturePathOpen_file_selected(path):
	self.next_texture_path = path

################################################################################
# Null out the currently active path so that a new one is created the next time
# a path node is created.
################################################################################
func _on_NewPath_pressed():
	self.currently_active_path = null

################################################################################
# Create a new icon and give it the texture
################################################################################
func _on_NewIcon_pressed():
	gen_new_icon(self.player_position, self.next_texture_path)

# A new path point is created
func _on_NewPathPoint_pressed():
	if self.currently_active_path == null:
		print("i am generating a new path")
		gen_new_path([self.player_position], self.next_texture_path)
	else:
		print("i am adding a point to the path")
		var z_accurate_player_position = player_position
		z_accurate_player_position.z = -z_accurate_player_position.z
		self.currently_active_path.curve.add_point(z_accurate_player_position)
		self.currently_active_path_2d.add_point(Vector2(self.player_position.x, -self.player_position.z))

		# Add a point to the currently active path (and the 2d path)
		
	print("hello I am a new path point")