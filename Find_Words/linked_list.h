#ifndef FUNCTIONS_HEADER_H
#define FUNCTIONS_HEADER_H

#include <stdbool.h>
#include "structs_header.h"


#define MAX_NUM_OCCURRENCES 500

typedef struct list_node {
    int position;
    struct list_node* next_node;
    struct list_node* previous_node; 
} list_node;

typedef struct {
    list_node* list_root;
    list_node* list_end;
} linked_list;


linked_list* initialize_linked_list();

bool add_list_node(linked_list* node, int pos);

void print_context(list_node* node, char file_name[]);

void print_letter_occurrences(tree_node* node);

#endif
