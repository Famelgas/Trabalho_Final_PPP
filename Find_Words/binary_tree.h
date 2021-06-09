#ifndef STRUCTS_HEADER_H
#define STRUCTS_HEADER_H


#define MAX_WORD_SIZE 50

typedef struct tree_node {
    char word[MAX_WORD_SIZE];
    linked_list* list;
    struct tree_node* left;
    struct tree_node* right; 
} tree_node;

typedef struct {
    tree_node* tree_root;
} binary_tree;



binary_tree* initialize_binary_tree();

bool add_tree_node(tree_node* tree_root, tree_node* aux_node, char str[], int pos);

bool add_occurrence(tree_node* aux_node, tree_node* route, int pos);

tree_node* find_tree_node(tree_node* route, char str[]);

bool print_word_occurrences(tree_node* node, char file_name[]);

bool print_words_letter(binary_tree* tree, char letter);


#endif
