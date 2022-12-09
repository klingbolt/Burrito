#include "{{cpp_class_header}}_gen.hpp"

#include <algorithm>
{% for absolute_include in cpp_includes.sorted_cpp_absolute_includes() %}
#include <{{absolute_include}}>
{% endfor %}

{% for relative_include in cpp_includes.sorted_cpp_relative_includes() %}
#include "{{relative_include}}"
{% endfor %}

{% for forward_declaration in cpp_includes.sorted_cpp_forward_declarations() %}
class {{forward_declaration}};
{% endfor %}
using namespace std;

string {{cpp_class}}::classname() {
    return "{{xml_class_name}}";
}
{% if cpp_class == "Category": %}
void {{cpp_class}}::init_from_xml(rapidxml::xml_node<>* node, vector<XMLError*>* errors) {
    for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
        bool is_icon_value = this->default_icon.init_xml_attribute(attribute, errors);
        bool is_trail_value = this->default_trail.init_xml_attribute(attribute, errors);

        if (init_xml_attribute(attribute, errors)) {
        }
        else if (is_icon_value || is_trail_value) {
        }
        else {
            errors->push_back(new XMLAttributeNameError("Unknown " + this->classname() + " attribute ", attribute));
        }
    }
}
{% endif %}

bool {{cpp_class}}::init_xml_attribute(rapidxml::xml_attribute<>* attribute, vector<XMLError*>* errors) {
    string attributename;
    attributename = normalize(get_attribute_name(attribute));
    {% for n, attribute_variable in enumerate(attribute_variables) %}
    {% for i, value in enumerate(attribute_variable.xml_fields) %}
    {% if i == 0 and n == 0: %}
    if (attributename == "{{value}}") {
        this->{{attribute_variable.attribute_name}} = parse_{{attribute_variable.class_name}}(attribute, errors);
        this->{{attribute_variable.attribute_name}}_is_set = true;
    }
    {% elif (attribute_variable.attribute_type == "CompoundValue" and attribute_variable.is_child == true) %}
    else if (attributename == "{{value}}") {
        this->{{attribute_variable.attribute_name}} = parse_float(attribute, errors);
        this->{{attribute_variable.attribute_name}}_is_set = true;
    }
    {% else: %}
    else if (attributename == "{{value}}") {
        this->{{attribute_variable.attribute_name}} = parse_{{attribute_variable.class_name}}(attribute, errors);
        this->{{attribute_variable.attribute_name}}_is_set = true;
    }
    {% endif %}
    {% endfor %}
    {% endfor %}
    else {
        return false;
    }
    return true;
}

{%- if attributes_of_type_marker_category %}

bool {{cpp_class}}::validate_attributes_of_type_marker_category() {
    {% for attribute in attributes_of_type_marker_category %}
    // TODO: validate "{{attribute}}"
    {% endfor %}
    return true;
}
{% endif %}

vector<string> {{cpp_class}}::as_xml() const {
    vector<string> xml_node_contents;
    xml_node_contents.push_back("<{{xml_class_name}} ");
    {% for attribute_variable in attribute_variables %}
    {% if (attribute_variable.attribute_type == "CompoundValue") %}
    {% if (attribute_variable.xml_export == "Children" and attribute_variable.is_child == true) %}
    if (this->{{attribute_variable.attribute_name}}_is_set) {
        xml_node_contents.push_back(" {{attribute_variable.default_xml_fields[0]}}=\"" + to_string(this->{{attribute_variable.attribute_name}}) + "\"");
    }
    {% elif (attribute_variable.xml_export == "Parent" and attribute_variable.is_child == false)%}
    if (this->{{attribute_variable.attribute_name}}_is_set) {
        xml_node_contents.push_back(" {{attribute_variable.default_xml_fields[0]}}=\"" + stringify_{{attribute_variable.class_name}}(this->{{attribute_variable.attribute_name}}) + "\"");
    }
    {% elif (attribute_variable.xml_export == "Parent and Children")%}
    {% for value in attribute_variable.xml_fields %}
    if (this->{{attribute_variable.attribute_name}}_is_set) {
        xml_node_contents.push_back(" {{value}}=\"" + stringify_{{attribute_variable.class_name}}(this->{{attribute_variable.attribute_name}}) + "\"");
    {% endfor %}
    }
    {% endif %}
    {% else: %}
    if (this->{{attribute_variable.attribute_name}}_is_set) {
        xml_node_contents.push_back(" {{attribute_variable.default_xml_fields[0]}}=\"" + stringify_{{attribute_variable.class_name}}(this->{{attribute_variable.attribute_name}}) + "\"");
    }
    {% endif %}
{% endfor %}
{% if cpp_class == "Category": %}
    xml_node_contents.push_back(">\n");

    for (const auto& [key, val] : this->children) {
        string text;
        for (const auto& s : val.as_xml()) {
            text += s;
        }

        xml_node_contents.push_back("\t" + text);
    }

    xml_node_contents.push_back("</MarkerCategory>\n");
{% else: %}
    xml_node_contents.push_back("/>");
{% endif %}
    return xml_node_contents;
}

waypoint::Waypoint {{cpp_class}}::as_protobuf() const {
    waypoint::{{cpp_class}} proto_{{cpp_class_header}};
    {% if cpp_class == "Icon": %}
    waypoint::Trigger* trigger = nullptr;
    {% endif %}
    {%for attribute_variable in attribute_variables%}
    {% if (attribute_variable.is_trigger == true)%}
    {% if (attribute_variable.attribute_type == "Custom")%}
    if (this->{{attribute_variable.attribute_name}}_is_set) {
        if (trigger == nullptr) {
            trigger = new waypoint::Trigger();
        }
        trigger->set_allocated_{{attribute_variable.protobuf_field}}(to_proto_{{attribute_variable.class_name}}(this->{{attribute_variable.attribute_name}}));
    }
    {% else: %}
    if (this->{{attribute_variable.attribute_name}}_is_set) {
        if (trigger == nullptr) {
            trigger = new waypoint::Trigger();
        }
        trigger->set_{{attribute_variable.protobuf_field}}(to_proto_{{attribute_variable.class_name}}(this->{{attribute_variable.attribute_name}}));
    }
    {% endif %}
    {% else: %}
    {% if (attribute_variable.attribute_type == "Custom" and attribute_variable.class_name == "TrailDataMapId")%}
//TODO: TrailDataMapID is currently not implemented
    {% elif (attribute_variable.attribute_type == "Enum")%}
    if (this->{{attribute_variable.attribute_name}}_is_set) {
        proto_{{cpp_class_header}}.set_{{attribute_variable.protobuf_field}}(to_proto_{{attribute_variable.class_name}}(this->{{attribute_variable.attribute_name}}));
    }
    {% elif (attribute_variable.attribute_type in ["MultiflagValue", "CompoundValue", "Custom"]) and attribute_variable.is_child == false%}
    if (this->{{attribute_variable.attribute_name}}_is_set) {
        proto_{{cpp_class_header}}.set_allocated_{{attribute_variable.protobuf_field}}(to_proto_{{attribute_variable.class_name}}(this->{{attribute_variable.attribute_name}}));
    }
    {% elif attribute_variable.is_child == true%}
    {% else: %}
    if (this->{{attribute_variable.attribute_name}}_is_set) {
        proto_{{cpp_class_header}}.set_{{attribute_variable.protobuf_field}}(this->{{attribute_variable.attribute_name}});
    }
    {% endif %}
    {% endif %}
    {% endfor %}
    {% if cpp_class == "Icon": %}
    if (trigger != nullptr) {
        proto_{{cpp_class_header}}.set_allocated_trigger(trigger);
    }
    {% endif %}
    {% if cpp_class == "Category": %}
    for (const auto& [key, val] : this->children) {
        waypoint::Waypoint proto_{{cpp_class_header}}_child = val.as_protobuf();

        proto_{{cpp_class_header}}.add_children()->CopyFrom(proto_{{cpp_class_header}}_child.{{cpp_class_header}}(0));
    }
    {% endif %}
    waypoint::Waypoint output;
    output.add_{{cpp_class_header}}()->CopyFrom(proto_{{cpp_class_header}});
    return output;
}

void {{cpp_class}}::parse_protobuf(waypoint::{{cpp_class}} proto_{{cpp_class_header}}) {
    {% if cpp_class == "Icon": %}
    waypoint::Trigger trigger = proto_{{cpp_class_header}}.trigger();
    {% endif %}
    {%for attribute_variable in attribute_variables%}
    {% if (attribute_variable.is_trigger == true)%}
    {% if (attribute_variable.attribute_type == "Custom")%}
    if (trigger.has_{{attribute_variable.protobuf_field}}()) {
        this->{{attribute_variable.attribute_name}} = from_proto_{{attribute_variable.class_name}}(trigger.{{attribute_variable.protobuf_field}}());
        this->{{attribute_variable.attribute_name}}_is_set = true;
    }
    {% elif attribute_variable.class_name == "string" %}
    if (trigger.{{attribute_variable.protobuf_field}}() != "") {
        this->{{attribute_variable.attribute_name}} = trigger.{{attribute_variable.protobuf_field}}();
        this->{{attribute_variable.attribute_name}}_is_set = true;
    }
    {% elif (attribute_variable.attribute_type ==  "Enum") %}
    if (trigger.{{attribute_variable.protobuf_field}}() != 0) {
        this->{{attribute_variable.attribute_name}} = from_proto_{{attribute_variable.class_name}}(trigger.{{attribute_variable.protobuf_field}}());
        this->{{attribute_variable.attribute_name}}_is_set = true;
    }
    {% else: %}
    if (trigger.{{attribute_variable.protobuf_field}}() != 0) {
        this->{{attribute_variable.attribute_name}} = trigger.{{attribute_variable.protobuf_field}}();
        this->{{attribute_variable.attribute_name}}_is_set = true;
    }
    {% endif %}
    {% else: %}
    {% if (attribute_variable.attribute_type == "Custom" and attribute_variable.class_name == "TrailDataMapId")%}
    {% elif (attribute_variable.attribute_type ==  "Enum") %}
    if (proto_{{cpp_class_header}}.{{attribute_variable.protobuf_field}}() != 0) {
        this->{{attribute_variable.attribute_name}} = from_proto_{{attribute_variable.class_name}}(proto_{{cpp_class_header}}.{{attribute_variable.protobuf_field}}());
        this->{{attribute_variable.attribute_name}}_is_set = true;
    }
    {% elif (attribute_variable.attribute_type in ["MultiflagValue", "CompoundValue", "Custom"]) and attribute_variable.is_child == false%}
    if (proto_{{cpp_class_header}}.has_{{attribute_variable.protobuf_field}}()) {
        this->{{attribute_variable.attribute_name}} = from_proto_{{attribute_variable.class_name}}(proto_{{cpp_class_header}}.{{attribute_variable.protobuf_field}}());
        this->{{attribute_variable.attribute_name}}_is_set = true;
    }
    {% elif attribute_variable.is_child == true%}
    {% elif attribute_variable.class_name == "string" %}
    if (proto_{{cpp_class_header}}.{{attribute_variable.protobuf_field}}() != "") {
        this->{{attribute_variable.attribute_name}} = proto_{{cpp_class_header}}.{{attribute_variable.protobuf_field}}();
        this->{{attribute_variable.attribute_name}}_is_set = true;
    }
    {% else: %}
    if (proto_{{cpp_class_header}}.{{attribute_variable.protobuf_field}}() != 0) {
        this->{{attribute_variable.attribute_name}} = proto_{{cpp_class_header}}.{{attribute_variable.protobuf_field}}();
        this->{{attribute_variable.attribute_name}}_is_set = true;
    }
    {% endif %}
    {% endif %}
    {% endfor %}
}
