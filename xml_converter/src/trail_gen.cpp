#include "trail_gen.hpp"
#include <typeinfo>
#include <string>

using namespace std;

string Trail::classname() {
    return "Trail";
}
bool Trail::init_xml_attribute(rapidxml::xml_attribute<>* attribute, vector<XMLError*> *errors) {
    string attributename; 
    attributename = normalize(get_attribute_name(attribute)); 
    if (attributename == "achievementbit") {
        this->achievement_bitmask = parse_int(attribute, errors);
        this->achievement_bitmask_is_set = true;
    }
    else if (attributename == "achievementid") {
        this->achievement_id = parse_int(attribute, errors);
        this->achievement_id_is_set = true;
    }
    else if (attributename == "alpha") {
        this->alpha = parse_float(attribute, errors);
        this->alpha_is_set = true;
    }
    else if (attributename == "animspeed") {
        this->animation_speed = parse_float(attribute, errors);
        this->animation_speed_is_set = true;
    }
    else if (attributename == "animationspeed") {
        this->animation_speed = parse_float(attribute, errors);
        this->animation_speed_is_set = true;
    }
    else if (attributename == "canfade") {
        this->can_fade = parse_bool(attribute, errors);
        this->can_fade_is_set = true;
    }
    else if (attributename == "type") {
        this->category = parse_marker_category(attribute, errors);
        this->category_is_set = true;
    }
    else if (attributename == "category") {
        this->category = parse_marker_category(attribute, errors);
        this->category_is_set = true;
    }
    else if (attributename == "color") {
        this->color = parse_color(attribute, errors);
        this->color_is_set = true;
    }
    else if (attributename == "cull") {
        this->cull_chirality = parse_cull_chirality(attribute, errors);
        this->cull_chirality_is_set = true;
    }
    else if (attributename == "fadefar") {
        this->distance_fade_end = parse_float(attribute, errors);
        this->distance_fade_end_is_set = true;
    }
    else if (attributename == "distancefadeend") {
        this->distance_fade_end = parse_float(attribute, errors);
        this->distance_fade_end_is_set = true;
    }
    else if (attributename == "fadenear") {
        this->distance_fade_start = parse_float(attribute, errors);
        this->distance_fade_start_is_set = true;
    }
    else if (attributename == "distancefadestart") {
        this->distance_fade_start = parse_float(attribute, errors);
        this->distance_fade_start_is_set = true;
    }
    else if (attributename == "festival") {
        this->festival_filter = parse_festival_filter(attribute, errors);
        this->festival_filter_is_set = true;
    }
    else if (attributename == "guid") {
        this->guid = parse_unique_id(attribute, errors);
        this->guid_is_set = true;
    }
    else if (attributename == "iswall") {
        this->is_wall = parse_bool(attribute, errors);
        this->is_wall_is_set = true;
    }
    else if (attributename == "mapdisplaysize") {
        this->map_display_size = parse_int(attribute, errors);
        this->map_display_size_is_set = true;
    }
    else if (attributename == "mapid") {
        this->map_id = parse_int(attribute, errors);
        this->map_id_is_set = true;
    }
    else if (attributename == "mapid") {
        this->map_type_filter = parse_map_type_filter(attribute, errors);
        this->map_type_filter_is_set = true;
    }
    else if (attributename == "mount") {
        this->mount_filter = parse_mount_filter(attribute, errors);
        this->mount_filter_is_set = true;
    }
    else if (attributename == "profession") {
        this->profession_filter = parse_profession_filter(attribute, errors);
        this->profession_filter_is_set = true;
    }
    else if (attributename == "ingamevisibility") {
        this->render_ingame = parse_bool(attribute, errors);
        this->render_ingame_is_set = true;
    }
    else if (attributename == "bhingamevisibility") {
        this->render_ingame = parse_bool(attribute, errors);
        this->render_ingame_is_set = true;
    }
    else if (attributename == "mapvisibility") {
        this->render_on_map = parse_bool(attribute, errors);
        this->render_on_map_is_set = true;
    }
    else if (attributename == "bhmapvisibility") {
        this->render_on_map = parse_bool(attribute, errors);
        this->render_on_map_is_set = true;
    }
    else if (attributename == "minimapvisibility") {
        this->render_on_minimap = parse_bool(attribute, errors);
        this->render_on_minimap_is_set = true;
    }
    else if (attributename == "bhminimapvisibility") {
        this->render_on_minimap = parse_bool(attribute, errors);
        this->render_on_minimap_is_set = true;
    }
    else if (attributename == "schedule") {
        this->schedule = parse_string(attribute, errors);
        this->schedule_is_set = true;
    }
    else if (attributename == "scheduleduration") {
        this->schedule_duration = parse_float(attribute, errors);
        this->schedule_duration_is_set = true;
    }
    else if (attributename == "specialization") {
        this->specialization_filter = parse_specialization_filter(attribute, errors);
        this->specialization_filter_is_set = true;
    }
    else if (attributename == "race") {
        this->species_filter = parse_species_filter(attribute, errors);
        this->species_filter_is_set = true;
    }
    else if (attributename == "species") {
        this->species_filter = parse_species_filter(attribute, errors);
        this->species_filter_is_set = true;
    }
    else if (attributename == "texture") {
        this->texture = parse_image(attribute, errors);
        this->texture_is_set = true;
    }
    else if (attributename == "traildata") {
        this->trail_data = parse_trail_data(attribute, errors);
        this->trail_data_is_set = true;
    }
    else if (attributename == "trailscale") {
        this->trail_scale = parse_float(attribute, errors);
        this->trail_scale_is_set = true;
    }
    else {
        return false;
    }
    return true;
}
bool Trail::validate_attributes_of_type_marker_category() {
    // TODO: validate "category"
    return true;
}

vector<string> Trail::as_xml() const {
    vector<string> xml_node_contents;
    xml_node_contents.push_back("<Trail ");
    if (this->achievement_bitmask_is_set) {
        xml_node_contents.push_back(" AchievementBit=\"" + stringify_int(this->achievement_bitmask) + "\"");
    }
    if (this->achievement_id_is_set) {
        xml_node_contents.push_back(" AchievementId=\"" + stringify_int(this->achievement_id) + "\"");
    }
    if (this->alpha_is_set) {
        xml_node_contents.push_back(" Alpha=\"" + stringify_float(this->alpha) + "\"");
    }
    if (this->animation_speed_is_set) {
        xml_node_contents.push_back(" AnimSpeed=\"" + stringify_float(this->animation_speed) + "\"");
    }
    if (this->can_fade_is_set) {
        xml_node_contents.push_back(" CanFade=\"" + stringify_bool(this->can_fade) + "\"");
    }
    if (this->category_is_set) {
        xml_node_contents.push_back(" Type=\"" + stringify_marker_category(this->category) + "\"");
    }
    if (this->color_is_set) {
        xml_node_contents.push_back(" Color=\"" + stringify_color(this->color) + "\"");
    }
    if (this->cull_chirality_is_set) {
        xml_node_contents.push_back(" Cull=\"" + stringify_cull_chirality(this->cull_chirality) + "\"");
    }
    if (this->distance_fade_end_is_set) {
        xml_node_contents.push_back(" FadeFar=\"" + stringify_float(this->distance_fade_end) + "\"");
    }
    if (this->distance_fade_start_is_set) {
        xml_node_contents.push_back(" FadeNear=\"" + stringify_float(this->distance_fade_start) + "\"");
    }
    if (this->festival_filter_is_set) {
        xml_node_contents.push_back(" Festival=\"" + stringify_festival_filter(this->festival_filter) + "\"");
    }
    if (this->guid_is_set) {
        xml_node_contents.push_back(" GUID=\"" + stringify_unique_id(this->guid) + "\"");
    }
    if (this->is_wall_is_set) {
        xml_node_contents.push_back(" IsWall=\"" + stringify_bool(this->is_wall) + "\"");
    }
    if (this->map_display_size_is_set) {
        xml_node_contents.push_back(" MapDisplaySize=\"" + stringify_int(this->map_display_size) + "\"");
    }
    if (this->map_id_is_set) {
        xml_node_contents.push_back(" MapID=\"" + stringify_int(this->map_id) + "\"");
    }
    if (this->map_type_filter_is_set) {
        xml_node_contents.push_back(" MapID=\"" + stringify_map_type_filter(this->map_type_filter) + "\"");
    }
    if (this->mount_filter_is_set) {
        xml_node_contents.push_back(" Mount=\"" + stringify_mount_filter(this->mount_filter) + "\"");
    }
    if (this->profession_filter_is_set) {
        xml_node_contents.push_back(" Profession=\"" + stringify_profession_filter(this->profession_filter) + "\"");
    }
    if (this->render_ingame_is_set) {
        xml_node_contents.push_back(" IngameVisibility=\"" + stringify_bool(this->render_ingame) + "\"");
    }
    if (this->render_on_map_is_set) {
        xml_node_contents.push_back(" MapVisibility=\"" + stringify_bool(this->render_on_map) + "\"");
    }
    if (this->render_on_minimap_is_set) {
        xml_node_contents.push_back(" MinimapVisibility=\"" + stringify_bool(this->render_on_minimap) + "\"");
    }
    if (this->schedule_is_set) {
        xml_node_contents.push_back(" Schedule=\"" + stringify_string(this->schedule) + "\"");
    }
    if (this->schedule_duration_is_set) {
        xml_node_contents.push_back(" ScheduleDuration=\"" + stringify_float(this->schedule_duration) + "\"");
    }
    if (this->specialization_filter_is_set) {
        xml_node_contents.push_back(" Specialization=\"" + stringify_specialization_filter(this->specialization_filter) + "\"");
    }
    if (this->species_filter_is_set) {
        xml_node_contents.push_back(" Race=\"" + stringify_species_filter(this->species_filter) + "\"");
    }
    if (this->texture_is_set) {
        xml_node_contents.push_back(" Texture=\"" + stringify_image(this->texture) + "\"");
    }
    if (this->trail_data_is_set) {
        xml_node_contents.push_back(" TrailData=\"" + stringify_trail_data(this->trail_data) + "\"");
    }
    if (this->trail_scale_is_set) {
        xml_node_contents.push_back(" TrailScale=\"" + stringify_float(this->trail_scale) + "\"");
    }
    xml_node_contents.push_back("/>");
    return xml_node_contents;
}