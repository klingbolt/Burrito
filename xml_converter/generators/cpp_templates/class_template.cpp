#include "{{cpp_class_header}}.hpp"

using namespace std;

string {{cpp_class}}::classname() {
    return "{{xml_class_name}}";
}
{%- if cpp_class == "Category": %}
void Category::init_from_xml(rapidxml::xml_node<>* node, vector<XMLError*> *errors) {
    for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
        bool is_icon_value = false;
        bool is_trail_value = false;

        for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
            is_icon_value |= this->default_icon.init_xml_attribute(attribute, errors);
            is_trail_value |= this->default_trail.init_xml_attribute(attribute, errors);
        }

        if (init_xml_attribute(attribute, errors)) {}
        else if (is_icon_value || is_trail_value) {}
        else {
            errors->push_back(new XMLAttributeNameError("Unknown " + this->classname() + " attribute ", attribute));    
        }
    }
}
{%- endif %}
bool {{cpp_class}}::init_xml_attribute(rapidxml::xml_attribute<>* attribute, vector<XMLError*> *errors) {
    string attributename; 
    attributename = normalize_type_name(get_attribute_name(attribute));
{%-for n, attribute_variable in enumerate(attribute_variables)%}    
    {%-for i, value in enumerate(attribute_variable[3])%}
        {%-if i == 0 and n == 0:%} 
    if (attributename == "{{value}}") {
        this->{{attribute_variables[n][0]}} = parse_{{attribute_variables[n][2]}}(attribute, errors);
    }
    {%- else: %}
    else if (attributename == "{{value}}") {
        this->{{attribute_variables[n][0]}} = parse_{{attribute_variables[n][2]}}(attribute, errors);
    }
        {%- endif %}
    {%- endfor %}
{%- endfor %}
    {%- if cpp_class == "Category": %}
    else if (attributename == "POI") {
        this->default_icon.init_xml_attribute(attribute, errors);
    }
    else if (attributename == "Trail"){
        this->default_trail.init_xml_attribute(attribute, errors);
    }
    {%- endif %}
    else {
        return false;
    }
    return true;
}