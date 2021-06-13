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

void find_words_by_letter(binary_tree* tree, char file_name[]);

void find_words_by_group(binary_tree* tree, char file_name[]);



#endif