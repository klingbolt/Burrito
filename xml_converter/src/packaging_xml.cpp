#include "packaging_xml.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <utility>

#include "hash_helpers.hpp"
#include "rapid_helpers.hpp"
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "state_structs/xml_reader_state.hpp"
#include "string_helper.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// DESERIALIZE //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

static unsigned int UNKNOWN_CATEGORY_COUNTER = 0;
static OptionalString parse_marker_categories(
    rapidxml::xml_node<>* node,
    map<string, Category>* marker_categories,
    Category* parent,
    vector<XMLError*>* errors,
    XMLReaderState* state,
    int depth = 0) {
    OptionalString name = {
        "",  // value
        false,  // is_null
    };
    if (get_node_name(node) == "MarkerCategory") {
        rapidxml::xml_attribute<>* name_attribute = find_attribute(node, "name");
        if (name_attribute == 0) {
            // TODO: This error should really be for the entire node not just the name
            errors->push_back(new XMLNodeNameError("Category attribute 'name' is missing so it cannot be properly referenced", node));

            // TODO: Maybe fall back on display name slugification.
            name = {
                "UNKNOWN_CATEGORY_" + to_string(UNKNOWN_CATEGORY_COUNTER),
                false,
            };
            UNKNOWN_CATEGORY_COUNTER++;
        }
        else {
            name = {
                lowercase(get_attribute_value(name_attribute)),
                false,
            };
        }

        if (name.value == "") {
            errors->push_back(new XMLNodeNameError("Category attribute 'name' is an empty string so it cannot be properly referenced", node));
            // TODO: Maybe fall back on display name slugification.
            name = {
                "UNKNOWN_CATEGORY_" + to_string(UNKNOWN_CATEGORY_COUNTER),
                false,
            };
            UNKNOWN_CATEGORY_COUNTER++;
        }

        // Build the new category
        Category* category;

        // Create and initialize a new category if this one does not exist
        auto existing_category_search = marker_categories->find(name.value);
        if (existing_category_search == marker_categories->end()) {
            category = &(*marker_categories)[name.value];
            category->parent = parent;
        }
        else {
            category = &existing_category_search->second;
            if (category->parent != parent) {
                errors->push_back(new XMLNodeNameError("Category somehow has a different parent then it used to. This might be a bug in xml_converter", node));
            }
        }

        category->init_from_xml(node, errors, state);

        // If this category does not have an id then create a new one for it
        // based on the hashes of its name and its parents names.
        if (!category->menu_id_is_set) {
            Hash128 new_id;
            new_id.update(name.value);

            Category* next_node = parent;
            while (next_node != nullptr) {
                new_id.update(next_node->name);
                next_node = next_node->parent;
            }
            category->menu_id = new_id.unique_id();
            category->menu_id_is_set = true;
        }

        for (rapidxml::xml_node<>* child_node = node->first_node(); child_node; child_node = child_node->next_sibling()) {
            parse_marker_categories(child_node, &(category->children), category, errors, state, depth + 1);
        }
        return name;
    }
    else {
        errors->push_back(new XMLNodeNameError("Unknown MarkerCategory Tag", node));
        name = {
            "",
            true,
        };
        return name;
    }
}

////////////////////////////////////////////////////////////////////////////////
// get_categories
//
// Gets the hirearchy of categories that this node references as its "type" so
// that the defaults of those categories can be used when creating the new node.
////////////////////////////////////////////////////////////////////////////////
static vector<Category*> get_categories(
    rapidxml::xml_node<>* node,
    map<string, Category>* marker_categories,
    vector<XMLError*>* errors) {
    vector<Category*> categories;

    rapidxml::xml_attribute<>* attribute = find_attribute(node, "type");

    if (attribute == 0) {
        // TODO: This error should really be for the entire node not just the name
        errors->push_back(new XMLNodeNameError("No Attribute Named Type", node));
        return categories;
    }

    vector<string> split_categories = split(get_attribute_value(attribute), ".");
    if (split_categories.size() == 0) {
        errors->push_back(new XMLAttributeValueError("Empty Type", attribute));
        return categories;
    }

    for (unsigned int i = 0; i < split_categories.size(); i++) {
        string category_name = lowercase(split_categories[i]);

        auto category = marker_categories->find(category_name);
        if (category == marker_categories->end()) {
            errors->push_back(new XMLAttributeValueError("Category Not Found \"" + category_name + "\"", attribute));
            return categories;
        }

        categories.push_back(&category->second);
        marker_categories = &category->second.children;
    }

    return categories;
}

static bool is_zero(Attribute::TrailData::XYZ point) {
    return point.x == 0 && point.y == 0 && point.z == 0;
}

////////////////////////////////////////////////////////////////////////////////
// parse_pois
//
// Parse the <POIs> xml block into an in-memory array of Markers.
////////////////////////////////////////////////////////////////////////////////
static vector<Parseable*> parse_pois(rapidxml::xml_node<>* root_node, map<string, Category>* marker_categories, vector<XMLError*>* errors, XMLReaderState* state) {
    vector<Parseable*> markers;

    // A new error array to ignore the parsing erorrs that would have already
    // been caught when the attributes were parsed in the category.
    vector<XMLError*> ignored_errors;

    for (rapidxml::xml_node<>* node = root_node->first_node(); node; node = node->next_sibling()) {
        if (get_node_name(node) == "POI") {
            vector<Category*> categories = get_categories(node, marker_categories, errors);

            Icon* icon = new Icon();

            for (size_t category_index = 0; category_index < categories.size(); category_index++) {
                for (size_t i = 0; i < categories[category_index]->icon_attributes.size(); i++) {
                    icon->init_xml_attribute(
                        categories[category_index]->icon_attributes[i],
                        &ignored_errors,
                        state);
                }
            }

            icon->init_from_xml(node, errors, state);
            markers.push_back(icon);
        }
        else if (get_node_name(node) == "Trail") {
            vector<Category*> categories = get_categories(node, marker_categories, errors);

            Trail* trail = new Trail();

            for (size_t category_index = 0; category_index < categories.size(); category_index++) {
                for (size_t i = 0; i < categories[category_index]->trail_attributes.size(); i++) {
                    trail->init_xml_attribute(
                        categories[category_index]->trail_attributes[i],
                        &ignored_errors,
                        state);
                }
            }

            trail->init_from_xml(node, errors, state);


            vector<Attribute::TrailData::XYZ> trail_data = trail->trail_data.points;

            auto sequence_start = trail_data.begin();
            for (auto i = trail_data.begin(); i != trail_data.end(); i++) {
                if (is_zero(*i)) {
                    if (sequence_start != i) {
                        Trail* partial_trail = new Trail(*trail);
                        partial_trail->trail_data.points = vector<Attribute::TrailData::XYZ>(sequence_start, i);
                        markers.push_back(partial_trail);
                    }
                    sequence_start = i + 1;
                }
            }

            // If we had any early splits then we need to truncate the remaining data.
            if (sequence_start != trail_data.begin()) {
                // If there is no data remaining to trunkate, because we had trailing zeros, then dont add an empty trail.
                if (sequence_start != trail_data.end()) {
                    trail->trail_data.points = vector<Attribute::TrailData::XYZ>(sequence_start, trail_data.end());
                    markers.push_back(trail);
                }
            }
            else {
                markers.push_back(trail);
            }

        }
        else {
            errors->push_back(new XMLNodeNameError("Unknown POIs node name", node));
        }
    }
    return markers;
}

////////////////////////////////////////////////////////////////////////////////
// parse_xml_file
//
// A function which parses a single XML file into their corrisponding classes.
////////////////////////////////////////////////////////////////////////////////
set<string> parse_xml_file(
    const MarkerPackFile& xml_filepath,
    map<string, Category>* marker_categories,
    vector<Parseable*>* parsed_pois) {
    vector<XMLError*> errors;

    unique_ptr<basic_istream<char>> infile = open_file_for_read(xml_filepath);

    rapidxml::file<> xml_file(*infile);

    string tmp_get_path = xml_filepath.tmp_get_path();

    rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_non_destructive | rapidxml::parse_no_data_nodes>(xml_file.data(), tmp_get_path.c_str());

    rapidxml::xml_node<>* root_node = doc.first_node();
    // Validate the Root Node
    if (get_node_name(root_node) != "OverlayData") {
        errors.push_back(new XMLNodeNameError("Root node should be of type OverlayData", root_node));
    }
    if (root_node->first_attribute() != nullptr) {
        cout << "Root Node has attributes when it should have none in " << xml_filepath.tmp_get_path() << endl;
    }

    XMLReaderState state;
    state.marker_pack_root_directory = xml_filepath.base;

    set<string> category_names;
    for (rapidxml::xml_node<>* node = root_node->first_node(); node; node = node->next_sibling()) {
        if (get_node_name(node) == "MarkerCategory") {
            OptionalString name = parse_marker_categories(node, marker_categories, nullptr, &errors, &state);
            if (name.is_null == false) {
                category_names.insert(name.value);
            }
        }
        else if (get_node_name(node) == "POIs") {
            vector<Parseable*> temp_vector = parse_pois(node, marker_categories, &errors, &state);
            move(temp_vector.begin(), temp_vector.end(), back_inserter(*parsed_pois));
        }
        else {
            errors.push_back(new XMLNodeNameError("Unknown top-level node name", node));
        }
    }

    for (XMLError* error : errors) {
        error->print_error();
    }
    return category_names;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// SERIALIZE ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void write_xml_file(const string marker_pack_root_directory, map<string, Category>* marker_categories, vector<Parseable*>* parsed_pois) {
    ofstream outfile;
    string tab_string;
    XMLWriterState state;
    state.marker_pack_root_directory = marker_pack_root_directory;

    rapidxml::xml_document<char> doc;
    state.doc = &doc;

    // TODO: Decide if we should require, reject, or optionally have the standard xml header on output
    // auto* declaration = doc.allocate_node(rapidxml::node_declaration);
    // declaration->append_attribute(doc.allocate_attribute("version", "1.0"));
    // declaration->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
    // doc.append_node(declaration);

    rapidxml::xml_node<char>* root = doc.allocate_node(rapidxml::node_element, "OverlayData");
    doc.append_node(root);

    for (const auto& category : *marker_categories) {
        root->append_node(category.second.as_xml(&state));
    }

    rapidxml::xml_node<char>* pois = doc.allocate_node(rapidxml::node_element, "POIs");
    root->append_node(pois);
    for (const auto& parsed_poi : *parsed_pois) {
        pois->append_node(parsed_poi->as_xml(&state));
    }

    string xml_filepath = join_file_paths(marker_pack_root_directory, "xml_file.xml");
    outfile.open(xml_filepath, ios::out);
    rapidxml::print(std::ostream_iterator<char>(outfile), doc);
    outfile.close();
}
