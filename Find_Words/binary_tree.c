#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "func.h"
#include "binary_tree.h"
#include "linked_list.h"


void initialize_binary_tree(binary_tree* tree) {
    tree->tree_route = NULL;
}


static tree_node* add_node(tree_node* tree_route, tree_node* node, char str[], int pos) {
    if (tree_route == NULL) {
        tree_route = node;
        return tree_route;
    }
    if (strcmp(tree_route->word, str) > 0) {
        if (tree_route->left == NULL) {
            tree_route->left = node;
            return tree_route;
        }
        return add_node(tree_route->left, node, str, pos);
    }
    if (strcmp(tree_route->word, str) < 0 && tree_route->right == NULL) {
        tree_route->right = node;
        return tree_route;
    }
    return add_node(tree_route->right, node, str, pos);
}


bool add_tree_node(tree_node* tree_route, tree_node* aux_node, char str[], int pos) {
    tree_node* node;
    node = malloc(sizeof(node));
    if (node = NULL) {
        fprintf(stderr, "Erro na criação de um novo nó.\n");
        return false;
    }

    node->right = NULL;
    node->left = NULL;
    strcpy(node->word, str);
    initialize_linked_list(node->list);
    add_list_node(node, pos);
    if (!add_list_node(node, pos)) {
        fprintf(stderr, "Erro ao adicionar ocurrência no novo nó.\n");
        return false;
    }

    add_node(tree_route, node, str, pos);

    return true;
}


tree_node* find_tree_node(tree_node* tree_route, char str[]) {
    if (tree_route == NULL) {
        return NULL;
    }
    if (strcmp(tree_route->word, str) == 0) 
        return tree_route;
    else if (strcmp(tree_route->word, str) > 0)
        return find_tree_node(tree_route->left, str);
    return find_tree_node(tree_route->right, str);
}


bool add_occurrence(tree_node* aux_node, tree_node* route, int pos) {
    if (!add_list_node(aux_node, pos)) { 
        fprintf(stderr, "Erro ao adicionar ocorrência.\n");
        return false;
    }

    return true;
}

// Escrever todas as ocorrências de uma palavra
bool print_word_occurrences(tree_node* node, char file_name[]) {
    list_node* i = node->list->list_route;
    do {
        print_context(i, file_name);
        i = node->list->list_route->next_node;
    } while (i != node->list->list_route);

    return true;
}


static tree_node* find_letter(tree_node* tree_route, char letter) {
    if (tree_route == NULL) {
        return NULL;
    }
    if (strcmp(tree_route->word[0], letter) == 0) {
        return tree_route;
    }
    else if (strcmp(tree_route->word[0], letter) > 0)
        return find_tree_node(tree_route->left, letter);
    return find_tree_node(tree_route->right, letter);
}

// Escrever todas as palavras de uma letra
bool print_words_letter(binary_tree* tree, char letter) {
    tree_node* node = tree->tree_route;
    tree_node* next_node = tree->tree_route;

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
                        