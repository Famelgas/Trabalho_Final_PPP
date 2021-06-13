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


static tree_node* initialize_tree_node(char str[], long pos) {
    tree_node* node = malloc(sizeof(tree_node));
    if (node == NULL) {
        fprintf(stderr, "Erro na criação de um novo nó.\n");
        exit(1);
    }

    node->right = NULL;
    node->left = NULL;
    strcpy(node->word, str);
    node->list = initialize_linked_list();
    if (!add_list_node(node->list, pos)) {
        fprintf(stderr, "Erro ao adicionar ocurrência no novo nó.\n");
        return NULL;
    }

    return node;
}


static void add_node(tree_node* tree_root, tree_node* node) {
    if (strcmp(tree_root->word, node->word) > 0) {
        if (tree_root->left == NULL) {
            tree_root->left = node;
            return;
        }
        add_node(tree_root->left, node);
    }
    else {
        if (tree_root->right == NULL) {
            tree_root->right = node;
            return;
        }
        add_node(tree_root->right, node);
    }
}


void add_tree_node(binary_tree* tree, char str[], long pos) {
    tree_node* node = initialize_tree_node(str, pos);    
    
    if (tree->tree_root == NULL) {
        tree->tree_root = node;
        return;
    }

    add_node(tree->tree_root, node);
}


tree_node* find_tree_node(tree_node* tree_root, char word[]) {
    if (tree_root == NULL) 
        return NULL;
    
    if (strcmp(tree_root->word, word) == 0) 
        return tree_root;

    else if (strcmp(tree_root->word, word) > 0)
        return find_tree_node(tree_root->left, word);
    
    else 
        return find_tree_node(tree_root->right, word);
}


void print_tree (tree_node* tree_root, int indent) {
    for (int i = 0; i < indent; ++i) {
        printf(" ");
    }
    printf("%s ",tree_root->word);
    print_list(tree_root->list->list_root);

    if (tree_root->left != NULL) {
        print_tree(tree_root->left, indent + 1);
    }
    if (tree_root->right != NULL) {
        print_tree(tree_root->right, indent + 1);
    }
}
