#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"
#include "binary_tree.h"


#define MAX_FILE_NAME 100
#define MAX_NUMBER_LETTERS 27

bool read_file(binary_tree* tree, char file_name[]);

bool menu(int* option);

bool find_occurrences(binary_tree* tree, char file_name[]);

bool find_words_letter(binary_tree* tree, char file_name[]);

bool find_words_group(binary_tree* tree, char file_name[]);

void print_context(list_node* node, char file_name[]);

void print_letter_occurrences(tree_node* node);

#endif