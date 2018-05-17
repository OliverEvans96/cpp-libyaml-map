#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <yaml.h>
#include <assert.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef map<string, vector<string> > StrVecMap;

// Read a YAML file into a map of string vectors.
// Does not support nested YAML mappings.
StrVecMap parse_yaml(const char* filename) {
    FILE *config_file;
    yaml_parser_t parser;
    yaml_document_t document;
    yaml_node_t *node, *node1, *key, *value;
    yaml_node_item_t *item;
    yaml_node_pair_t *pair;
    string str;
    vector<string> vec;
    StrVecMap yaml_map;

    config_file = fopen(filename, "rb");

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, config_file);
    yaml_parser_load(&parser, &document);

    node = yaml_document_get_root_node(&document);
    assert(node->type == YAML_MAPPING_NODE);

    // Mapping
    for(pair=node->data.mapping.pairs.start; pair<node->data.mapping.pairs.top; pair++) { 
        key = yaml_document_get_node(&document, pair->key);
        value = yaml_document_get_node(&document, pair->value);
        // Scalar
        if(value->type == YAML_SCALAR_NODE) {
            vec.push_back((char*)value->data.scalar.value);
        }
        // Sequence
        else if(value->type == YAML_SEQUENCE_NODE) {
            for(item=value->data.sequence.items.start; 
                    item<value->data.sequence.items.top; item++) {
                node1 = yaml_document_get_node(&document, *item);
                vec.push_back((char*)node1->data.scalar.value);
            }
        }
        yaml_map[(char*)key->data.scalar.value] = vec;
        vec.clear();
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
    fclose(config_file);

    return yaml_map;
}

void print_yaml_map(StrVecMap yaml_map) {
    string key, val;
    vector<string> vec;
    StrVecMap::iterator map_it;
    vector<string>::iterator vec_it;

    for(map_it=yaml_map.begin(); map_it != yaml_map.end(); map_it++) {
        key = map_it -> first;
        vec = map_it -> second;
        printf("%s: [", key.data());
        for(vec_it=vec.begin(); vec_it != vec.end(); vec_it++) {
           val = *vec_it;
           printf("\"%s\", ", val.data());
        }
        printf("]\n");
    }
}

int main() {
    StrVecMap yaml_map;

    yaml_map = parse_yaml("config.yaml");
    print_yaml_map(yaml_map);

    return 0;
}

