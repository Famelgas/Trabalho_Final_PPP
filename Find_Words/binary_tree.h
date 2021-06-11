#ifndef STRUCTS_HEADER_H
#define STRUCTS_HEADER_H

#include "linked_list.h"


#define MAX_WORD_SIZE 50

typedef struct tree_node {
    char word[MAX_WORD_SIZE];
    linked_list* list;
    struct tree_node* left;
    struct tree_node* right; 
} tree_node;

typedef struct {
    tree_node* tree_root;
} binary_tree;



binary_tree* initialize_binary_tree();

bool add_tree_node(binary_tree* tree, char str[], long pos);

tree_node* find_tree_node(binary_tree* tree, char str[]);


#endif
