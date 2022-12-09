#pragma once

#include <string>
#include <vector>

#include "../rapidxml-1.13/rapidxml.hpp"
{% if type == "Enum":%}
#include "waypoint.pb.h"

class XMLError;

enum {{class_name}} {
    {% for attribute_variable in attribute_variables: %}
        {{attribute_variable.attribute_name}},
    {% endfor %}
};
{% else: %}
class XMLError;
namespace waypoint {
class {{class_name}};
}

class {{class_name}} {
 public:
    {% for attribute_variable in attribute_variables: %}
    {{attribute_variable.cpp_type}} {{attribute_variable.attribute_name}};
    {% endfor %}

    virtual std::string classname() {
        return "{{class_name}}";
    }
};
{% endif %}
{{class_name}} parse_{{attribute_name}}(rapidxml::xml_attribute<>* input, std::vector<XMLError*>* errors);
std::string stringify_{{attribute_name}}({{class_name}} attribute_value);
{% if type == "Enum":%}
waypoint::{{class_name}} to_proto_{{attribute_name}}({{class_name}} attribute_value);
{% else: %}
waypoint::{{class_name}}* to_proto_{{attribute_name}}({{class_name}} attribute_value);
{% endif %}
{{class_name}} from_proto_{{attribute_name}}(waypoint::{{class_name}} proto_{{attribute_name}});
