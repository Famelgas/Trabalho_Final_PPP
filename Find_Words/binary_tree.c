#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "linked_list.h"
#include "func.h"


binary_tree* initialize_binary_tree() {
    binary_tree* tree = malloc(sizeof(binary_tree));
    tree->tree_root = NULL;
    return tree;
}


static void add_node(tree_node* tree_root, tree_node* node) {
    if (tree_root == NULL) {
        tree_root = node;
        return tree_root;
    }
    if (strcmp(tree_root->word, node->word) > 0) {
        if (tree_root->left == NULL) {
            tree_root->left = node;
            return;
        }
        return add_node(tree_root->left, node->word);
    }
    if (strcmp(tree_root->word, node->word) < 0 && tree_root->right == NULL) {
        tree_root->right = node;
        return;
    }
    return add_node(tree_root->right, node->word);
}


bool add_tree_node(binary_tree* tree, char str[], long pos) {
    tree_node* node = malloc(sizeof(tree_node));
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

    add_node(tree->tree_root, node);

    return true;
}


tree_node* find_tree_node(binary_tree* tree, char word[]) {
    if (tree->tree_root == NULL) 
        return NULL;
    
    if (strcmp(tree->tree_root->word, word) == 0) 
        return tree->tree_root;

    else if (strcmp(tree->tree_root->word, word) > 0)
        return find_tree_node(tree->tree_root->left, word);
    
    return find_tree_node(tree->tree_root->right, word);
}
