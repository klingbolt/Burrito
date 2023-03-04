#pragma once

#include <string>
#include <vector>

#include "../rapidxml-1.13/rapidxml.hpp"
#include "waypoint.pb.h"

class XMLError;
namespace waypoint {
class RGBA;
}

class Color {
 public:
    std::string hex;
    float alpha;
};

Color parse_color(rapidxml::xml_attribute<>* input, std::vector<XMLError*>* errors);

std::string stringify_color(Color attribute_value);

waypoint::RGBAColor* to_proto_color(Color attribute_value);

Color from_proto_color(waypoint::RGBAColor attribute_value);
