#ifndef PRINT_WORDS_H
#define PRINT_WORDS_H

#include "binary_tree.h"


bool add_occurrence(tree_node* aux_node, long pos);

bool show_word_occurrences(tree_node* node, char file_name[]);

void print_words_by_letter(tree_node* tree_root, char letter);


#endif
