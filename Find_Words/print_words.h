#ifndef PRINT_WORDS_H
#define PRINT_WORDS_H

#include "binary_tree.h"


bool add_occurrence(tree_node* aux_node, tree_node* route, int pos);

tree_node* find_tree_node(tree_node* route, char str[]);

bool print_word_occurrences(tree_node* node, char file_name[]);

bool print_words_letter(binary_tree* tree, char letter);


#endif
