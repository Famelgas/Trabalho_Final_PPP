#ifndef FUNCTIONS_HEADER_H
#define FUNCTIONS_HEADER_H

#include <stdbool.h>


#define MAX_NUM_OCCURRENCES 500

typedef struct list_node {
    long position;
    struct list_node* next_node;
    struct list_node* previous_node; 
} list_node;

typedef struct {
    list_node* list_root;
} linked_list;


linked_list* initialize_linked_list();

bool add_list_node(linked_list* node, long pos);

void print_list(list_node* list_root);

#endif
