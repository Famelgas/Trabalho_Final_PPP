#ifndef FUNCTIONS_HEADER_H
#define FUNCTIONS_HEADER_H

#include <stdbool.h>
#include "structs_header.h"


// árvore binária
void initialize_binary_tree(binary_tree* tree);

bool add_tree_node(tree_node* tree_route, tree_node* aux_node, char str[], int pos);

bool add_occurrence(tree_node* aux_node, tree_node* route, int pos);

tree_node* find_tree_node(tree_node* route, char str[]);

bool print_word_occurrences(tree_node* node, char file_name[]);

bool print_words_letter(binary_tree* tree, char letter);


//lista ligada
void initialize_linked_list(linked_list* list);

bool add_list_node(tree_node* node,int pos);

void print_context(list_node* node, char file_name[]);

void print_letter_occurrences(tree_node* node);

#endif
