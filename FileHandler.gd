static func call_xml_converter(executable_path: String, args: PoolStringArray):
	var output: Array = []
	print(args)
	var result: int = OS.execute(executable_path, args, true, output, true)
	print(output)
	if result != OK:
		print("Failed to execute the command. Error code:", result)
	else:
		print("Command executed successfully.")

static func create_directory_if_missing(path: String):
	var dir = Directory.new()
	if not dir.dir_exists(path):
		var success = dir.make_dir(path)
		if success != OK:
			print("Error: Could not create data folder:", path)