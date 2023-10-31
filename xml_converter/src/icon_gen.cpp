#include "icon_gen.hpp"

#include <algorithm>
#include <iosfwd>
#include <string>

#include "attribute/bool.hpp"
#include "attribute/float.hpp"
#include "attribute/int.hpp"
#include "attribute/string.hpp"
#include "rapid_helpers.hpp"
#include "rapidxml-1.13/rapidxml.hpp"
#include "string_helper.hpp"
#include "waypoint.pb.h"

using namespace std;

string Icon::classname() {
    return "POI";
}

bool Icon::init_xml_attribute(rapidxml::xml_attribute<>* attribute, vector<XMLError*>* errors, string base_dir) {
    string attributename;
    attributename = normalize(get_attribute_name(attribute));
    if (attributename == "achievementbit") {
        xml_attribute_to_int(attribute, errors, &(this->achievement_bitmask), &(this->achievement_bitmask_is_set));
    }
    else if (attributename == "achievementid") {
        xml_attribute_to_int(attribute, errors, &(this->achievement_id), &(this->achievement_id_is_set));
    }
    else if (attributename == "autotrigger") {
        xml_attribute_to_bool(attribute, errors, &(this->auto_trigger), &(this->auto_trigger_is_set));
    }
    else if (attributename == "bouncedelay") {
        xml_attribute_to_float(attribute, errors, &(this->bounce_delay), &(this->bounce_delay_is_set));
    }
    else if (attributename == "bounceduration") {
        xml_attribute_to_float(attribute, errors, &(this->bounce_duration), &(this->bounce_duration_is_set));
    }
    else if (attributename == "bounceheight") {
        xml_attribute_to_float(attribute, errors, &(this->bounce_height), &(this->bounce_height_is_set));
    }
    else if (attributename == "canfade") {
        xml_attribute_to_bool(attribute, errors, &(this->can_fade), &(this->can_fade_is_set));
    }
    else if (attributename == "type") {
        xml_attribute_to_marker_category(attribute, errors, &(this->category), &(this->category_is_set));
    }
    else if (attributename == "category") {
        xml_attribute_to_marker_category(attribute, errors, &(this->category), &(this->category_is_set));
    }
    else if (attributename == "color") {
        xml_attribute_to_color(attribute, errors, &(this->color), &(this->color_is_set));
    }
    else if (attributename == "bhcolor") {
        xml_attribute_to_color(attribute, errors, &(this->color), &(this->color_is_set));
    }
    else if (attributename == "alpha") {
        xml_attribute_to_float(attribute, errors, &(this->color.alpha), &(this->color_is_set));
    }
    else if (attributename == "blue") {
        xml_attribute_to_float(attribute, errors, &(this->color.blue), &(this->color_is_set));
    }
    else if (attributename == "green") {
        xml_attribute_to_float(attribute, errors, &(this->color.green), &(this->color_is_set));
    }
    else if (attributename == "red") {
        xml_attribute_to_float(attribute, errors, &(this->color.red), &(this->color_is_set));
    }
    else if (attributename == "copy") {
        xml_attribute_to_string(attribute, errors, &(this->copy_clipboard), &(this->copy_clipboard_is_set));
    }
    else if (attributename == "copyclipboard") {
        xml_attribute_to_string(attribute, errors, &(this->copy_clipboard), &(this->copy_clipboard_is_set));
    }
    else if (attributename == "copymessage") {
        xml_attribute_to_string(attribute, errors, &(this->copy_message), &(this->copy_message_is_set));
    }
    else if (attributename == "cull") {
        xml_attribute_to_cull_chirality(attribute, errors, &(this->cull_chirality), &(this->cull_chirality_is_set));
    }
    else if (attributename == "fadefar") {
        xml_attribute_to_float(attribute, errors, &(this->distance_fade_end), &(this->distance_fade_end_is_set));
    }
    else if (attributename == "distancefadeend") {
        xml_attribute_to_float(attribute, errors, &(this->distance_fade_end), &(this->distance_fade_end_is_set));
    }
    else if (attributename == "fadenear") {
        xml_attribute_to_float(attribute, errors, &(this->distance_fade_start), &(this->distance_fade_start_is_set));
    }
    else if (attributename == "distancefadestart") {
        xml_attribute_to_float(attribute, errors, &(this->distance_fade_start), &(this->distance_fade_start_is_set));
    }
    else if (attributename == "rotate") {
        xml_attribute_to_euler_rotation(attribute, errors, &(this->euler_rotation), &(this->euler_rotation_is_set));
    }
    else if (attributename == "rotatex") {
        xml_attribute_to_float(attribute, errors, &(this->euler_rotation.x_rotation), &(this->euler_rotation_is_set));
    }
    else if (attributename == "rotatey") {
        xml_attribute_to_float(attribute, errors, &(this->euler_rotation.y_rotation), &(this->euler_rotation_is_set));
    }
    else if (attributename == "rotatez") {
        xml_attribute_to_float(attribute, errors, &(this->euler_rotation.z_rotation), &(this->euler_rotation_is_set));
    }
    else if (attributename == "festival") {
        xml_attribute_to_festival_filter(attribute, errors, &(this->festival_filter), &(this->festival_filter_is_set));
    }
    else if (attributename == "guid") {
        xml_attribute_to_unique_id(attribute, errors, &(this->guid), &(this->guid_is_set));
    }
    else if (attributename == "hascountdown") {
        xml_attribute_to_bool(attribute, errors, &(this->has_countdown), &(this->has_countdown_is_set));
    }
    else if (attributename == "heightoffset") {
        xml_attribute_to_float(attribute, errors, &(this->height_offset), &(this->height_offset_is_set));
    }
    else if (attributename == "bhheightoffset") {
        xml_attribute_to_float(attribute, errors, &(this->height_offset), &(this->height_offset_is_set));
    }
    else if (attributename == "hide") {
        xml_attribute_to_marker_category(attribute, errors, &(this->hide_category), &(this->hide_category_is_set));
    }
    else if (attributename == "iconfile") {
        xml_attribute_to_image(attribute, errors, &(this->icon), &(this->icon_is_set));
    }
    else if (attributename == "iconsize") {
        xml_attribute_to_float(attribute, errors, &(this->icon_size), &(this->icon_size_is_set));
    }
    else if (attributename == "info") {
        xml_attribute_to_string(attribute, errors, &(this->info_message), &(this->info_message_is_set));
    }
    else if (attributename == "invertbehavior") {
        xml_attribute_to_bool(attribute, errors, &(this->invert_visibility), &(this->invert_visibility_is_set));
    }
    else if (attributename == "mapdisplaysize") {
        xml_attribute_to_int(attribute, errors, &(this->map_display_size), &(this->map_display_size_is_set));
    }
    else if (attributename == "mapid") {
        xml_attribute_to_int(attribute, errors, &(this->map_id), &(this->map_id_is_set));
    }
    else if (attributename == "maptype") {
        xml_attribute_to_map_type_filter(attribute, errors, &(this->map_type_filter), &(this->map_type_filter_is_set));
    }
    else if (attributename == "maxsize") {
        xml_attribute_to_int(attribute, errors, &(this->maximum_size_on_screen), &(this->maximum_size_on_screen_is_set));
    }
    else if (attributename == "minsize") {
        xml_attribute_to_int(attribute, errors, &(this->minimum_size_on_screen), &(this->minimum_size_on_screen_is_set));
    }
    else if (attributename == "mount") {
        xml_attribute_to_mount_filter(attribute, errors, &(this->mount_filter), &(this->mount_filter_is_set));
    }
    else if (attributename == "position") {
        xml_attribute_to_position(attribute, errors, &(this->position), &(this->position_is_set));
    }
    else if (attributename == "xpos") {
        xml_attribute_to_float(attribute, errors, &(this->position.x_position), &(this->position_is_set));
    }
    else if (attributename == "positionx") {
        xml_attribute_to_float(attribute, errors, &(this->position.x_position), &(this->position_is_set));
    }
    else if (attributename == "ypos") {
        xml_attribute_to_float(attribute, errors, &(this->position.y_position), &(this->position_is_set));
    }
    else if (attributename == "positiony") {
        xml_attribute_to_float(attribute, errors, &(this->position.y_position), &(this->position_is_set));
    }
    else if (attributename == "zpos") {
        xml_attribute_to_float(attribute, errors, &(this->position.z_position), &(this->position_is_set));
    }
    else if (attributename == "positionz") {
        xml_attribute_to_float(attribute, errors, &(this->position.z_position), &(this->position_is_set));
    }
    else if (attributename == "profession") {
        xml_attribute_to_profession_filter(attribute, errors, &(this->profession_filter), &(this->profession_filter_is_set));
    }
    else if (attributename == "ingamevisibility") {
        xml_attribute_to_bool(attribute, errors, &(this->render_ingame), &(this->render_ingame_is_set));
    }
    else if (attributename == "bhingamevisibility") {
        xml_attribute_to_bool(attribute, errors, &(this->render_ingame), &(this->render_ingame_is_set));
    }
    else if (attributename == "mapvisibility") {
        xml_attribute_to_bool(attribute, errors, &(this->render_on_map), &(this->render_on_map_is_set));
    }
    else if (attributename == "bhmapvisibility") {
        xml_attribute_to_bool(attribute, errors, &(this->render_on_map), &(this->render_on_map_is_set));
    }
    else if (attributename == "minimapvisibility") {
        xml_attribute_to_bool(attribute, errors, &(this->render_on_minimap), &(this->render_on_minimap_is_set));
    }
    else if (attributename == "bhminimapvisibility") {
        xml_attribute_to_bool(attribute, errors, &(this->render_on_minimap), &(this->render_on_minimap_is_set));
    }
    else if (attributename == "behavior") {
        xml_attribute_to_reset_behavior(attribute, errors, &(this->reset_behavior), &(this->reset_behavior_is_set));
    }
    else if (attributename == "resetlength") {
        xml_attribute_to_float(attribute, errors, &(this->reset_length), &(this->reset_length_is_set));
    }
    else if (attributename == "scaleonmapwithzoom") {
        xml_attribute_to_bool(attribute, errors, &(this->scale_on_map_with_zoom), &(this->scale_on_map_with_zoom_is_set));
    }
    else if (attributename == "schedule") {
        xml_attribute_to_string(attribute, errors, &(this->schedule), &(this->schedule_is_set));
    }
    else if (attributename == "scheduleduration") {
        xml_attribute_to_float(attribute, errors, &(this->schedule_duration), &(this->schedule_duration_is_set));
    }
    else if (attributename == "show") {
        xml_attribute_to_marker_category(attribute, errors, &(this->show_category), &(this->show_category_is_set));
    }
    else if (attributename == "specialization") {
        xml_attribute_to_specialization_filter(attribute, errors, &(this->specialization_filter), &(this->specialization_filter_is_set));
    }
    else if (attributename == "race") {
        xml_attribute_to_species_filter(attribute, errors, &(this->species_filter), &(this->species_filter_is_set));
    }
    else if (attributename == "species") {
        xml_attribute_to_species_filter(attribute, errors, &(this->species_filter), &(this->species_filter_is_set));
    }
    else if (attributename == "toggle") {
        xml_attribute_to_marker_category(attribute, errors, &(this->toggle_category), &(this->toggle_category_is_set));
    }
    else if (attributename == "togglecategory") {
        xml_attribute_to_marker_category(attribute, errors, &(this->toggle_category), &(this->toggle_category_is_set));
    }
    else if (attributename == "tipdescription") {
        xml_attribute_to_string(attribute, errors, &(this->tooltip_description), &(this->tooltip_description_is_set));
    }
    else if (attributename == "tipname") {
        xml_attribute_to_string(attribute, errors, &(this->tooltip_name), &(this->tooltip_name_is_set));
    }
    else if (attributename == "triggerrange") {
        xml_attribute_to_float(attribute, errors, &(this->trigger_range), &(this->trigger_range_is_set));
    }
    else if (attributename == "inforange") {
        xml_attribute_to_float(attribute, errors, &(this->trigger_range), &(this->trigger_range_is_set));
    }
    else {
        return false;
    }
    return true;
}

bool Icon::validate_attributes_of_type_marker_category() {
    // TODO: validate "category"
    // TODO: validate "hide_category"
    // TODO: validate "show_category"
    // TODO: validate "toggle_category"
    return true;
}

vector<string> Icon::as_xml() const {
    vector<string> xml_node_contents;
    xml_node_contents.push_back("<POI ");
    if (this->achievement_bitmask_is_set) {
        xml_node_contents.push_back(int_to_xml_attribute("AchievementBit", &this->achievement_bitmask));
    }
    if (this->achievement_id_is_set) {
        xml_node_contents.push_back(int_to_xml_attribute("AchievementId", &this->achievement_id));
    }
    if (this->auto_trigger_is_set) {
        xml_node_contents.push_back(bool_to_xml_attribute("AutoTrigger", &this->auto_trigger));
    }
    if (this->bounce_delay_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("BounceDelay", &this->bounce_delay));
    }
    if (this->bounce_duration_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("BounceDuration", &this->bounce_duration));
    }
    if (this->bounce_height_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("BounceHeight", &this->bounce_height));
    }
    if (this->can_fade_is_set) {
        xml_node_contents.push_back(bool_to_xml_attribute("CanFade", &this->can_fade));
    }
    if (this->category_is_set) {
        xml_node_contents.push_back(marker_category_to_xml_attribute("Type", &this->category));
    }
    if (this->color_is_set) {
        xml_node_contents.push_back(color_to_xml_attribute("Color", &this->color));
    }
    if (this->color_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("Alpha", &this->color.alpha));
    }
    if (this->copy_clipboard_is_set) {
        xml_node_contents.push_back(string_to_xml_attribute("Copy", &this->copy_clipboard));
    }
    if (this->copy_message_is_set) {
        xml_node_contents.push_back(string_to_xml_attribute("CopyMessage", &this->copy_message));
    }
    if (this->cull_chirality_is_set) {
        xml_node_contents.push_back(cull_chirality_to_xml_attribute("Cull", &this->cull_chirality));
    }
    if (this->distance_fade_end_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("FadeFar", &this->distance_fade_end));
    }
    if (this->distance_fade_start_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("FadeNear", &this->distance_fade_start));
    }
    if (this->festival_filter_is_set) {
        xml_node_contents.push_back(festival_filter_to_xml_attribute("Festival", &this->festival_filter));
    }
    if (this->guid_is_set) {
        xml_node_contents.push_back(unique_id_to_xml_attribute("GUID", &this->guid));
    }
    if (this->has_countdown_is_set) {
        xml_node_contents.push_back(bool_to_xml_attribute("HasCountdown", &this->has_countdown));
    }
    if (this->height_offset_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("HeightOffset", &this->height_offset));
    }
    if (this->hide_category_is_set) {
        xml_node_contents.push_back(marker_category_to_xml_attribute("Hide", &this->hide_category));
    }
    if (this->icon_is_set) {
        xml_node_contents.push_back(image_to_xml_attribute("IconFile", &this->icon));
    }
    if (this->icon_size_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("IconSize", &this->icon_size));
    }
    if (this->info_message_is_set) {
        xml_node_contents.push_back(string_to_xml_attribute("Info", &this->info_message));
    }
    if (this->invert_visibility_is_set) {
        xml_node_contents.push_back(bool_to_xml_attribute("InvertBehavior", &this->invert_visibility));
    }
    if (this->map_display_size_is_set) {
        xml_node_contents.push_back(int_to_xml_attribute("MapDisplaySize", &this->map_display_size));
    }
    if (this->map_id_is_set) {
        xml_node_contents.push_back(int_to_xml_attribute("MapID", &this->map_id));
    }
    if (this->map_type_filter_is_set) {
        xml_node_contents.push_back(map_type_filter_to_xml_attribute("MapType", &this->map_type_filter));
    }
    if (this->maximum_size_on_screen_is_set) {
        xml_node_contents.push_back(int_to_xml_attribute("MaxSize", &this->maximum_size_on_screen));
    }
    if (this->minimum_size_on_screen_is_set) {
        xml_node_contents.push_back(int_to_xml_attribute("MinSize", &this->minimum_size_on_screen));
    }
    if (this->mount_filter_is_set) {
        xml_node_contents.push_back(mount_filter_to_xml_attribute("Mount", &this->mount_filter));
    }
    if (this->position_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("XPos", &this->position.x_position));
    }
    if (this->position_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("YPos", &this->position.y_position));
    }
    if (this->position_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("ZPos", &this->position.z_position));
    }
    if (this->profession_filter_is_set) {
        xml_node_contents.push_back(profession_filter_to_xml_attribute("Profession", &this->profession_filter));
    }
    if (this->render_ingame_is_set) {
        xml_node_contents.push_back(bool_to_xml_attribute("IngameVisibility", &this->render_ingame));
    }
    if (this->render_on_map_is_set) {
        xml_node_contents.push_back(bool_to_xml_attribute("MapVisibility", &this->render_on_map));
    }
    if (this->render_on_minimap_is_set) {
        xml_node_contents.push_back(bool_to_xml_attribute("MinimapVisibility", &this->render_on_minimap));
    }
    if (this->reset_behavior_is_set) {
        xml_node_contents.push_back(reset_behavior_to_xml_attribute("Behavior", &this->reset_behavior));
    }
    if (this->reset_length_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("ResetLength", &this->reset_length));
    }
    if (this->scale_on_map_with_zoom_is_set) {
        xml_node_contents.push_back(bool_to_xml_attribute("ScaleOnMapWithZoom", &this->scale_on_map_with_zoom));
    }
    if (this->schedule_is_set) {
        xml_node_contents.push_back(string_to_xml_attribute("Schedule", &this->schedule));
    }
    if (this->schedule_duration_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("ScheduleDuration", &this->schedule_duration));
    }
    if (this->show_category_is_set) {
        xml_node_contents.push_back(marker_category_to_xml_attribute("Show", &this->show_category));
    }
    if (this->specialization_filter_is_set) {
        xml_node_contents.push_back(specialization_filter_to_xml_attribute("Specialization", &this->specialization_filter));
    }
    if (this->species_filter_is_set) {
        xml_node_contents.push_back(species_filter_to_xml_attribute("Race", &this->species_filter));
    }
    if (this->toggle_category_is_set) {
        xml_node_contents.push_back(marker_category_to_xml_attribute("Toggle", &this->toggle_category));
    }
    if (this->tooltip_description_is_set) {
        xml_node_contents.push_back(string_to_xml_attribute("TipDescription", &this->tooltip_description));
    }
    if (this->tooltip_name_is_set) {
        xml_node_contents.push_back(string_to_xml_attribute("TipName", &this->tooltip_name));
    }
    if (this->trigger_range_is_set) {
        xml_node_contents.push_back(float_to_xml_attribute("TriggerRange", &this->trigger_range));
    }
    xml_node_contents.push_back("/>");
    return xml_node_contents;
}

waypoint::Icon Icon::as_protobuf() const {
    waypoint::Icon proto_icon;
    if (this->achievement_bitmask_is_set) {
        proto_icon.set_achievement_bit(to_proto_int(this->achievement_bitmask));
    }
    if (this->achievement_id_is_set) {
        proto_icon.set_achievement_id(to_proto_int(this->achievement_id));
    }
    if (this->auto_trigger_is_set) {
        proto_icon.mutable_trigger()->set_auto_trigger(to_proto_bool(this->auto_trigger));
    }
    if (this->bounce_delay_is_set) {
        proto_icon.mutable_trigger()->set_bounce_delay(to_proto_float(this->bounce_delay));
    }
    if (this->bounce_duration_is_set) {
        proto_icon.mutable_trigger()->set_bounce_duration(to_proto_float(this->bounce_duration));
    }
    if (this->bounce_height_is_set) {
        proto_icon.mutable_trigger()->set_bounce_height(to_proto_float(this->bounce_height));
    }
    if (this->can_fade_is_set) {
        proto_icon.set_can_fade(to_proto_bool(this->can_fade));
    }
    if (this->category_is_set) {
        proto_icon.set_allocated_category(to_proto_marker_category(this->category));
    }
    if (this->color_is_set) {
        proto_icon.set_allocated_rgba_color(to_proto_color(this->color));
    }
    if (this->copy_clipboard_is_set) {
        proto_icon.mutable_trigger()->set_action_copy_clipboard(to_proto_string(this->copy_clipboard));
    }
    if (this->copy_message_is_set) {
        proto_icon.mutable_trigger()->set_action_copy_message(to_proto_string(this->copy_message));
    }
    if (this->cull_chirality_is_set) {
        proto_icon.set_cull_chirality(to_proto_cull_chirality(this->cull_chirality));
    }
    if (this->distance_fade_end_is_set) {
        proto_icon.set_distance_fade_end(to_proto_float(this->distance_fade_end));
    }
    if (this->distance_fade_start_is_set) {
        proto_icon.set_distance_fade_start(to_proto_float(this->distance_fade_start));
    }
    if (this->euler_rotation_is_set) {
        proto_icon.set_allocated_euler_rotation(to_proto_euler_rotation(this->euler_rotation));
    }
    if (this->festival_filter_is_set) {
        proto_icon.set_allocated_festival_filter(to_proto_festival_filter(this->festival_filter));
    }
    if (this->guid_is_set) {
        proto_icon.set_guid(to_proto_unique_id(this->guid));
    }
    if (this->has_countdown_is_set) {
        proto_icon.mutable_trigger()->set_has_countdown(to_proto_bool(this->has_countdown));
    }
    if (this->height_offset_is_set) {
        proto_icon.set_height_offset(to_proto_float(this->height_offset));
    }
    if (this->hide_category_is_set) {
        proto_icon.mutable_trigger()->set_allocated_action_hide_category(to_proto_marker_category(this->hide_category));
    }
    if (this->icon_is_set) {
        proto_icon.set_allocated_texture_path(to_proto_image(this->icon));
    }
    if (this->icon_size_is_set) {
        proto_icon.set_tentative__scale(to_proto_float(this->icon_size));
    }
    if (this->info_message_is_set) {
        proto_icon.mutable_trigger()->set_action_info_message(to_proto_string(this->info_message));
    }
    if (this->invert_visibility_is_set) {
        proto_icon.mutable_trigger()->set_invert_display(to_proto_bool(this->invert_visibility));
    }
    if (this->map_display_size_is_set) {
        proto_icon.set_map_display_size(to_proto_int(this->map_display_size));
    }
    if (this->map_id_is_set) {
        proto_icon.set_map_id(to_proto_int(this->map_id));
    }
    if (this->map_type_filter_is_set) {
        proto_icon.set_allocated_map_type_filter(to_proto_map_type_filter(this->map_type_filter));
    }
    if (this->maximum_size_on_screen_is_set) {
        proto_icon.set_maximum_size_on_screen(to_proto_int(this->maximum_size_on_screen));
    }
    if (this->minimum_size_on_screen_is_set) {
        proto_icon.set_minimum_size_on_screen(to_proto_int(this->minimum_size_on_screen));
    }
    if (this->mount_filter_is_set) {
        proto_icon.set_allocated_mount_filter(to_proto_mount_filter(this->mount_filter));
    }
    if (this->position_is_set) {
        proto_icon.set_allocated_position(to_proto_position(this->position));
    }
    if (this->profession_filter_is_set) {
        proto_icon.set_allocated_profession_filter(to_proto_profession_filter(this->profession_filter));
    }
    if (this->render_ingame_is_set) {
        proto_icon.set_tentative__render_ingame(to_proto_bool(this->render_ingame));
    }
    if (this->render_on_map_is_set) {
        proto_icon.set_tentative__render_on_map(to_proto_bool(this->render_on_map));
    }
    if (this->render_on_minimap_is_set) {
        proto_icon.set_tentative__render_on_minimap(to_proto_bool(this->render_on_minimap));
    }
    if (this->reset_behavior_is_set) {
        proto_icon.mutable_trigger()->set_reset_behavior(to_proto_reset_behavior(this->reset_behavior));
    }
    if (this->reset_length_is_set) {
        proto_icon.mutable_trigger()->set_reset_length(to_proto_float(this->reset_length));
    }
    if (this->scale_on_map_with_zoom_is_set) {
        proto_icon.set_scale_on_map_with_zoom(to_proto_bool(this->scale_on_map_with_zoom));
    }
    if (this->schedule_is_set) {
        proto_icon.set_bhdraft__schedule(to_proto_string(this->schedule));
    }
    if (this->schedule_duration_is_set) {
        proto_icon.set_bhdraft__schedule_duration(to_proto_float(this->schedule_duration));
    }
    if (this->show_category_is_set) {
        proto_icon.mutable_trigger()->set_allocated_action_show_category(to_proto_marker_category(this->show_category));
    }
    if (this->specialization_filter_is_set) {
        proto_icon.set_allocated_specialization_filter(to_proto_specialization_filter(this->specialization_filter));
    }
    if (this->species_filter_is_set) {
        proto_icon.set_allocated_species_filter(to_proto_species_filter(this->species_filter));
    }
    if (this->toggle_category_is_set) {
        proto_icon.mutable_trigger()->set_allocated_action_toggle_category(to_proto_marker_category(this->toggle_category));
    }
    if (this->tooltip_description_is_set) {
        proto_icon.set_tip_description(to_proto_string(this->tooltip_description));
    }
    if (this->tooltip_name_is_set) {
        proto_icon.set_tip_name(to_proto_string(this->tooltip_name));
    }
    if (this->trigger_range_is_set) {
        proto_icon.mutable_trigger()->set_range(to_proto_float(this->trigger_range));
    }
    return proto_icon;
}

void Icon::parse_protobuf(waypoint::Icon proto_icon) {
    if (proto_icon.achievement_bit() != 0) {
        this->achievement_bitmask = from_proto_int(proto_icon.achievement_bit());
        this->achievement_bitmask_is_set = true;
    }
    if (proto_icon.achievement_id() != 0) {
        this->achievement_id = from_proto_int(proto_icon.achievement_id());
        this->achievement_id_is_set = true;
    }
    if (proto_icon.trigger().auto_trigger() != 0) {
        this->auto_trigger = from_proto_bool(proto_icon.trigger().auto_trigger());
        this->auto_trigger_is_set = true;
    }
    if (proto_icon.trigger().bounce_delay() != 0) {
        this->bounce_delay = from_proto_float(proto_icon.trigger().bounce_delay());
        this->bounce_delay_is_set = true;
    }
    if (proto_icon.trigger().bounce_duration() != 0) {
        this->bounce_duration = from_proto_float(proto_icon.trigger().bounce_duration());
        this->bounce_duration_is_set = true;
    }
    if (proto_icon.trigger().bounce_height() != 0) {
        this->bounce_height = from_proto_float(proto_icon.trigger().bounce_height());
        this->bounce_height_is_set = true;
    }
    if (proto_icon.can_fade() != 0) {
        this->can_fade = from_proto_bool(proto_icon.can_fade());
        this->can_fade_is_set = true;
    }
    if (proto_icon.has_category()) {
        this->category = from_proto_marker_category(proto_icon.category());
        this->category_is_set = true;
    }
    if (proto_icon.has_rgba_color()) {
        this->color = from_proto_color(proto_icon.rgba_color());
        this->color_is_set = true;
    }
    if (proto_icon.trigger().action_copy_clipboard() != "") {
        this->copy_clipboard = from_proto_string(proto_icon.trigger().action_copy_clipboard());
        this->copy_clipboard_is_set = true;
    }
    if (proto_icon.trigger().action_copy_message() != "") {
        this->copy_message = from_proto_string(proto_icon.trigger().action_copy_message());
        this->copy_message_is_set = true;
    }
    if (proto_icon.cull_chirality() != 0) {
        this->cull_chirality = from_proto_cull_chirality(proto_icon.cull_chirality());
        this->cull_chirality_is_set = true;
    }
    if (proto_icon.distance_fade_end() != 0) {
        this->distance_fade_end = from_proto_float(proto_icon.distance_fade_end());
        this->distance_fade_end_is_set = true;
    }
    if (proto_icon.distance_fade_start() != 0) {
        this->distance_fade_start = from_proto_float(proto_icon.distance_fade_start());
        this->distance_fade_start_is_set = true;
    }
    if (proto_icon.has_euler_rotation()) {
        this->euler_rotation = from_proto_euler_rotation(proto_icon.euler_rotation());
        this->euler_rotation_is_set = true;
    }
    if (proto_icon.has_festival_filter()) {
        this->festival_filter = from_proto_festival_filter(proto_icon.festival_filter());
        this->festival_filter_is_set = true;
    }
    if (proto_icon.guid() != "") {
        this->guid = from_proto_unique_id(proto_icon.guid());
        this->guid_is_set = true;
    }
    if (proto_icon.trigger().has_countdown() != 0) {
        this->has_countdown = from_proto_bool(proto_icon.trigger().has_countdown());
        this->has_countdown_is_set = true;
    }
    if (proto_icon.height_offset() != 0) {
        this->height_offset = from_proto_float(proto_icon.height_offset());
        this->height_offset_is_set = true;
    }
    if (proto_icon.trigger().has_action_hide_category()) {
        this->hide_category = from_proto_marker_category(proto_icon.trigger().action_hide_category());
        this->hide_category_is_set = true;
    }
    if (proto_icon.has_texture_path()) {
        this->icon = from_proto_image(proto_icon.texture_path());
        this->icon_is_set = true;
    }
    if (proto_icon.tentative__scale() != 0) {
        this->icon_size = from_proto_float(proto_icon.tentative__scale());
        this->icon_size_is_set = true;
    }
    if (proto_icon.trigger().action_info_message() != "") {
        this->info_message = from_proto_string(proto_icon.trigger().action_info_message());
        this->info_message_is_set = true;
    }
    if (proto_icon.trigger().invert_display() != 0) {
        this->invert_visibility = from_proto_bool(proto_icon.trigger().invert_display());
        this->invert_visibility_is_set = true;
    }
    if (proto_icon.map_display_size() != 0) {
        this->map_display_size = from_proto_int(proto_icon.map_display_size());
        this->map_display_size_is_set = true;
    }
    if (proto_icon.map_id() != 0) {
        this->map_id = from_proto_int(proto_icon.map_id());
        this->map_id_is_set = true;
    }
    if (proto_icon.has_map_type_filter()) {
        this->map_type_filter = from_proto_map_type_filter(proto_icon.map_type_filter());
        this->map_type_filter_is_set = true;
    }
    if (proto_icon.maximum_size_on_screen() != 0) {
        this->maximum_size_on_screen = from_proto_int(proto_icon.maximum_size_on_screen());
        this->maximum_size_on_screen_is_set = true;
    }
    if (proto_icon.minimum_size_on_screen() != 0) {
        this->minimum_size_on_screen = from_proto_int(proto_icon.minimum_size_on_screen());
        this->minimum_size_on_screen_is_set = true;
    }
    if (proto_icon.has_mount_filter()) {
        this->mount_filter = from_proto_mount_filter(proto_icon.mount_filter());
        this->mount_filter_is_set = true;
    }
    if (proto_icon.has_position()) {
        this->position = from_proto_position(proto_icon.position());
        this->position_is_set = true;
    }
    if (proto_icon.has_profession_filter()) {
        this->profession_filter = from_proto_profession_filter(proto_icon.profession_filter());
        this->profession_filter_is_set = true;
    }
    if (proto_icon.tentative__render_ingame() != 0) {
        this->render_ingame = from_proto_bool(proto_icon.tentative__render_ingame());
        this->render_ingame_is_set = true;
    }
    if (proto_icon.tentative__render_on_map() != 0) {
        this->render_on_map = from_proto_bool(proto_icon.tentative__render_on_map());
        this->render_on_map_is_set = true;
    }
    if (proto_icon.tentative__render_on_minimap() != 0) {
        this->render_on_minimap = from_proto_bool(proto_icon.tentative__render_on_minimap());
        this->render_on_minimap_is_set = true;
    }
    if (proto_icon.trigger().reset_behavior() != 0) {
        this->reset_behavior = from_proto_reset_behavior(proto_icon.trigger().reset_behavior());
        this->reset_behavior_is_set = true;
    }
    if (proto_icon.trigger().reset_length() != 0) {
        this->reset_length = from_proto_float(proto_icon.trigger().reset_length());
        this->reset_length_is_set = true;
    }
    if (proto_icon.scale_on_map_with_zoom() != 0) {
        this->scale_on_map_with_zoom = from_proto_bool(proto_icon.scale_on_map_with_zoom());
        this->scale_on_map_with_zoom_is_set = true;
    }
    if (proto_icon.bhdraft__schedule() != "") {
        this->schedule = from_proto_string(proto_icon.bhdraft__schedule());
        this->schedule_is_set = true;
    }
    if (proto_icon.bhdraft__schedule_duration() != 0) {
        this->schedule_duration = from_proto_float(proto_icon.bhdraft__schedule_duration());
        this->schedule_duration_is_set = true;
    }
    if (proto_icon.trigger().has_action_show_category()) {
        this->show_category = from_proto_marker_category(proto_icon.trigger().action_show_category());
        this->show_category_is_set = true;
    }
    if (proto_icon.has_specialization_filter()) {
        this->specialization_filter = from_proto_specialization_filter(proto_icon.specialization_filter());
        this->specialization_filter_is_set = true;
    }
    if (proto_icon.has_species_filter()) {
        this->species_filter = from_proto_species_filter(proto_icon.species_filter());
        this->species_filter_is_set = true;
    }
    if (proto_icon.trigger().has_action_toggle_category()) {
        this->toggle_category = from_proto_marker_category(proto_icon.trigger().action_toggle_category());
        this->toggle_category_is_set = true;
    }
    if (proto_icon.tip_description() != "") {
        this->tooltip_description = from_proto_string(proto_icon.tip_description());
        this->tooltip_description_is_set = true;
    }
    if (proto_icon.tip_name() != "") {
        this->tooltip_name = from_proto_string(proto_icon.tip_name());
        this->tooltip_name_is_set = true;
    }
    if (proto_icon.trigger().range() != 0) {
        this->trigger_range = from_proto_float(proto_icon.trigger().range());
        this->trigger_range_is_set = true;
    }
}
