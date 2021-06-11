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


static tree_node* add_node(tree_node* tree_root, tree_node* node, char str[], long pos) {
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


bool add_tree_node(tree_node* tree_root, tree_node* aux_node, char str[], long pos) {
    tree_node* node;
    node = malloc(sizeof(tree_node));
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
