#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "func.h"
#include "binary_tree.h"
#include "linked_list.h"
#include "func.h"


binary_tree* initialize_binary_tree() {
    binary_tree* tree = malloc(sizeof(binary_tree));
    tree->tree_root = NULL;
    return tree;
}


static tree_node* add_node(tree_node* tree_root, tree_node* node, char str[], int pos) {
    if (tree_root == NULL) {
        tree_root = node;
        return tree_root;
    }
    if (strcmp(tree_root->word, str) > 0) {
        if (tree_root->left == NULL) {
            tree_root->left = node;
            return tree_root;
        }
        return add_node(tree_root->left, node, str, pos);
    }
    if (strcmp(tree_root->word, str) < 0 && tree_root->right == NULL) {
        tree_root->right = node;
        return tree_root;
    }
    return add_node(tree_root->right, node, str, pos);
}


bool add_tree_node(tree_node* tree_root, tree_node* aux_node, char str[], int pos) {
    tree_node* node;
    node = malloc(sizeof(node));
    if (node == NULL) {
        fprintf(stderr, "Erro na criação de um novo nó.\n");
        return false;
    }

    node->right = NULL;
    node->left = NULL;
    strcpy(node->word, str);
    node->list = initialize_linked_list();
    if (!add_list_node(node->list, pos)) {
        fprintf(stderr, "Erro ao adicionar ocurrência no novo nó.\n");
        return false;
    }

    add_node(tree_root, node, str, pos);

    return true;
}


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
                        