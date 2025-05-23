#pragma once

#include <functional>
#include <string>
#include <vector>

#include "attribute/color.hpp"
#include "attribute/cull_chirality_gen.hpp"
#include "attribute/festival_filter_gen.hpp"
#include "attribute/image.hpp"
#include "attribute/map_type_filter_gen.hpp"
#include "attribute/marker_category.hpp"
#include "attribute/mount_filter_gen.hpp"
#include "attribute/profession_filter_gen.hpp"
#include "attribute/specialization_filter_gen.hpp"
#include "attribute/species_filter_gen.hpp"
#include "attribute/trail_data.hpp"
#include "attribute/unique_id.hpp"
#include "guildpoint.pb.h"
#include "parseable.hpp"
#include "rapidxml-1.13/rapidxml.hpp"
#include "state_structs/xml_reader_state.hpp"

class XMLError;

class Trail : public Parseable {
 public:
    int achievement_bit_index;
    int achievement_id;
    float animation_speed;
    Attribute::MarkerCategory::MarkerCategory category;
    Attribute::Color::Color color;
    Attribute::CullChirality::CullChirality cull_chirality;
    bool disable_player_cutout;
    float distance_fade_end;
    float distance_fade_start;
    Attribute::FestivalFilter::FestivalFilter festival_filter;
    Attribute::UniqueId::UniqueId guid;
    bool is_wall;
    int map_display_size;
    int map_id;
    Attribute::MapTypeFilter::MapTypeFilter map_type_filter;
    Attribute::MountFilter::MountFilter mount_filter;
    Attribute::ProfessionFilter::ProfessionFilter profession_filter;
    bool render_ingame;
    bool render_on_map;
    bool render_on_minimap;
    std::string schedule;
    float schedule_duration;
    Attribute::SpecializationFilter::SpecializationFilter specialization_filter;
    Attribute::SpeciesFilter::SpeciesFilter species_filter;
    Attribute::Image::Image texture;
    Attribute::TrailData::TrailData trail_data;
    float trail_scale;
    bool achievement_bit_index_is_set = false;
    bool achievement_id_is_set = false;
    bool animation_speed_is_set = false;
    bool category_is_set = false;
    bool color_is_set = false;
    bool cull_chirality_is_set = false;
    bool disable_player_cutout_is_set = false;
    bool distance_fade_end_is_set = false;
    bool distance_fade_start_is_set = false;
    bool festival_filter_is_set = false;
    bool guid_is_set = false;
    bool is_wall_is_set = false;
    bool map_display_size_is_set = false;
    bool map_id_is_set = false;
    bool map_type_filter_is_set = false;
    bool mount_filter_is_set = false;
    bool profession_filter_is_set = false;
    bool render_ingame_is_set = false;
    bool render_on_map_is_set = false;
    bool render_on_minimap_is_set = false;
    bool schedule_is_set = false;
    bool schedule_duration_is_set = false;
    bool specialization_filter_is_set = false;
    bool species_filter_is_set = false;
    bool texture_is_set = false;
    bool trail_data_is_set = false;
    bool trail_scale_is_set = false;
    virtual rapidxml::xml_node<char>* as_xml(XMLWriterState* state) const;
    virtual std::string classname();
    bool init_xml_attribute(rapidxml::xml_attribute<>* attribute, std::vector<XMLError*>* errors, XMLReaderState* state);
    guildpoint::Trail as_protobuf(ProtoWriterState* state) const;
    void parse_protobuf(guildpoint::Trail proto_trail, ProtoReaderState* state);
    bool validate_attributes_of_type_marker_category();
};
