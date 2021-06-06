#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include "binary_tree.h"

#define MAX_NUM_OCCURRENCES 500

typedef struct list_node {
    int position;
    struct list_node* next_node;
    struct list_node* previous_node; 
} list_node;

typedef struct {
    list_node* list_route;
    list_node* list_end;
} linked_list;

void initialize_linked_list(linked_list* list);

bool add_list_node(tree_node* node,int pos);

void print_context(list_node* node, char file_name[]);

void print_letter_occurrences(tree_node* node);

#endif
