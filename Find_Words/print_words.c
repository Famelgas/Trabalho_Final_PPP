#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"
#include "binary_tree.h"
#include "linked_list.h"


tree_node* find_tree_node(tree_node* tree_root, char str[]) {
    if (tree_root == NULL) 
        return NULL;
    
    if (strcmp(tree_root->word, str) == 0) 
        return tree_root;

    else if (strcmp(tree_root->word, str) > 0)
        return find_tree_node(tree_root->left, str);
    
    return find_tree_node(tree_root->right, str);
}


bool add_occurrence(tree_node* aux_node, tree_node* route, int pos) {
    if (!add_list_node(aux_node->list, pos)) { 
        fprintf(stderr, "Erro ao adicionar ocorrência.\n");
        return false;
    }

    return true;
}

// Escrever todas as ocorrências de uma palavra
bool print_word_occurrences(tree_node* node, char file_name[]) {
    list_node* i = node->list->list_root;
    do {
        print_context(i, file_name);
        i = node->list->list_root->next_node;
    } while (i != node->list->list_root);

    return true;
}


static tree_node* find_letter(tree_node* tree_root, char letter) {
    if (tree_root == NULL) 
        return NULL;
    
    if (tree_root->word[0]== letter) 
        return tree_root;
    
    else if (tree_root->word[0] > letter)
        return find_letter(tree_root->left, letter);
    
    return find_letter(tree_root->right, letter);
}

// Escrever todas as palavras de uma letra
bool print_words_letter(binary_tree* tree, char letter) {
    tree_node* node = tree->tree_root;
    tree_node* next_node = tree->tree_root;

    while (node != NULL) {
        node = find_letter(next_node, letter);
        if (node->left->word[0] == letter) {
            next_node = node->left;
        }
        else if (node->right->word[0] == letter) {
            next_node = node->right;
        }
        printf("%s ", node->word);
        print_letter_occurrences(node);
    }
    return true;
}
