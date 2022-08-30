#include "{{attribute_name}}_gen.hpp"

#include <string>
#include <vector>
#include <typeinfo>

#include "../rapid_helpers.hpp"
#include "../rapidxml-1.13/rapidxml.hpp"

{{class_name}} parse_{{attribute_name}}(rapidxml::xml_attribute<>* input, vector<XMLError*> *){
    {{class_name}} {{attribute_name}};
    vector<string> compound_values;
    string attributename;
{%- for attribute_variable in attribute_variables: %}
    {{attribute_name}}.{{attribute_variable.attribute_name}} = 0;
{%- endfor %} 
    attributename = get_attribute_name(input); 
    compound_values = split(get_attribute_value(input), ",");
    if (compound_values.size() == 3){
{%-for n, attribute_variable in enumerate(attribute_variables)%}    
        {{attribute_name}}.{{attribute_variables[n].attribute_name}} = std::stof(compound_values[{{n}}]); 
{%- endfor %} 
    }
    return {{attribute_name}};
}
{%-if attribute_variables[0].xml_export == "Parent"%}
string stringify_{{attribute_name}}({{class_name}} attribute_value){
    string output;
    {%-for n, attribute_variable in enumerate(attribute_variables)%}
        {%-if n == 0:%}
    output = to_string(attribute_value.{{attribute_variables[n].attribute_name}});
        {%- else %}
    output = output + "," + to_string(attribute_value.{{attribute_variables[n].attribute_name}});
        {%- endif %}
    {%- endfor %} 
    return output;
}
{%- endif %}
