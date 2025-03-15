#include "string.hpp"

#include <iosfwd>
#include <string>
#include <vector>

#include "../rapid_helpers.hpp"
#include "../rapidxml-1.13/rapidxml.hpp"
#include "../string_helper.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// xml_attribute_to_string
//
// Parses a string from the value of a rapidxml::xml_attribute.
////////////////////////////////////////////////////////////////////////////////
void Attribute::String::from_xml_attribute(
    rapidxml::xml_attribute<>* input,
    std::vector<XMLError*>*,
    XMLReaderState*,
    string* value,
    bool* is_set
) {
    *value = get_attribute_value(input);
    *is_set = true;
}

////////////////////////////////////////////////////////////////////////////////
// string_to_xml_attribute
//
// Converts a string into a fully qualified xml attribute string.
////////////////////////////////////////////////////////////////////////////////
void Attribute::String::to_xml_attribute(
    XMLWriterState*,
    const string* value,
    std::function<void(std::string)> setter
) {
    setter(*value);
}

////////////////////////////////////////////////////////////////////////////////
// proto_to_string
//
// Parses a string from a proto field.
////////////////////////////////////////////////////////////////////////////////
void Attribute::String::from_proto_field(
    string input,
    ProtoReaderState*,
    string* value,
    bool* is_set
) {
    *value = input;
    *is_set = true;
}

////////////////////////////////////////////////////////////////////////////////
// string_to_proto
//
// Writes a string to a proto using the provided setter function.
////////////////////////////////////////////////////////////////////////////////
void Attribute::String::to_proto_field(
    std::string value,
    ProtoWriterState*,
    std::function<void(std::string)> setter
) {
    setter(value);
}

void Attribute::NameAndDisplayname::from_proto_field(
    std::string input,
    ProtoReaderState*,
    std::string* display_name,
    bool* is_display_name_set,
    std::string* name,
    bool* is_name_set
) {
    *display_name = input;
    *is_display_name_set = true;
    *name = normalize(input);
    *is_name_set = true;
}

void Attribute::NameAndDisplayname::to_proto_field(
    std::string value,
    ProtoWriterState*,
    std::function<void(std::string)> setter,
    const std::string* name,
    const bool* is_name_set
) {
    setter(value);
}
