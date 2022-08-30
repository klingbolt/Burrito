#include "species_filter_gen.hpp"

#include <string>
#include <vector>

#include "../rapid_helpers.hpp"
#include "../rapidxml-1.13/rapidxml.hpp"

SpeciesFilter parse_species_filter(rapidxml::xml_attribute<>* input, vector<XMLError*> *errors){
    SpeciesFilter species_filter;
    vector<string> flag_values;
    flag_values = split(get_attribute_value(input), ",");  
    species_filter.asura = false;  
    species_filter.charr = false;  
    species_filter.human = false;  
    species_filter.norn = false;  
    species_filter.sylvari = false;
   
    for (string flag_value : flag_values) {
        string normalized_flag_value = normalize(flag_value);
        if (normalized_flag_value == "asura") {
            species_filter.asura = true; 
        }
        else if (normalized_flag_value == "charr") {
            species_filter.charr = true; 
        }
        else if (normalized_flag_value == "human") {
            species_filter.human = true; 
        }
        else if (normalized_flag_value == "norn") {
            species_filter.norn = true; 
        }
        else if (normalized_flag_value == "sylvari") {
            species_filter.sylvari = true; 
        }
        else {
            errors->push_back(new XMLAttributeValueError("Invalid Filter for SpeciesFilter. Found " + flag_value, input));
            continue;
        }
    }
    return species_filter;
}

string stringify_species_filter(SpeciesFilter attribute_value){
    string output = "";
    if (attribute_value.asura == true){
        output = output + "asura";
    }
    if (attribute_value.charr == true){
        output = output + "charr";
    }
    if (attribute_value.human == true){
        output = output + "human";
    }
    if (attribute_value.norn == true){
        output = output + "norn";
    }
    if (attribute_value.sylvari == true){
        output = output + "sylvari";
    }
    return output;
}