#include "profession_filter_gen.hpp"

#include <string>
#include <vector>

#include "../rapid_helpers.hpp"
#include "../rapidxml-1.13/rapidxml.hpp"

ProfessionFilter parse_profession_filter(rapidxml::xml_attribute<>* input, vector<XMLError*> *errors){
    ProfessionFilter profession_filter;
    vector<string> flag_values;
    flag_values = split(get_attribute_value(input), ",");  
    profession_filter.guardian = false;  
    profession_filter.warrior = false;  
    profession_filter.engineer = false;  
    profession_filter.ranger = false;  
    profession_filter.thief = false;  
    profession_filter.elementalist = false;  
    profession_filter.mesmer = false;  
    profession_filter.necromancer = false;  
    profession_filter.revenant = false;
   
    for (string flag_value : flag_values) {
        string normalized_flag_value = normalize(flag_value);
        if (normalized_flag_value == "guardian") {
            profession_filter.guardian = true; 
        }
        else if (normalized_flag_value == "warrior") {
            profession_filter.warrior = true; 
        }
        else if (normalized_flag_value == "engineer") {
            profession_filter.engineer = true; 
        }
        else if (normalized_flag_value == "ranger") {
            profession_filter.ranger = true; 
        }
        else if (normalized_flag_value == "thief") {
            profession_filter.thief = true; 
        }
        else if (normalized_flag_value == "elementalist") {
            profession_filter.elementalist = true; 
        }
        else if (normalized_flag_value == "mesmer") {
            profession_filter.mesmer = true; 
        }
        else if (normalized_flag_value == "necromancer") {
            profession_filter.necromancer = true; 
        }
        else if (normalized_flag_value == "revenant") {
            profession_filter.revenant = true; 
        }
        else {
            errors->push_back(new XMLAttributeValueError("Invalid Filter for ProfessionFilter. Found " + flag_value, input));
            continue;
        }
    }
    return profession_filter;
}

string stringify_profession_filter(ProfessionFilter attribute_value){
    string output = "";
    if (attribute_value.guardian == true){
        output = output + "guardian";
    }
    if (attribute_value.warrior == true){
        output = output + "warrior";
    }
    if (attribute_value.engineer == true){
        output = output + "engineer";
    }
    if (attribute_value.ranger == true){
        output = output + "ranger";
    }
    if (attribute_value.thief == true){
        output = output + "thief";
    }
    if (attribute_value.elementalist == true){
        output = output + "elementalist";
    }
    if (attribute_value.mesmer == true){
        output = output + "mesmer";
    }
    if (attribute_value.necromancer == true){
        output = output + "necromancer";
    }
    if (attribute_value.revenant == true){
        output = output + "revenant";
    }
    return output;
}