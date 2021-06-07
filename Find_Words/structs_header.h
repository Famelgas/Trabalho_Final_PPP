#ifndef STRUCTS_HEADER_H
#define STRUCTS_HEADER_H


#define MAX_WORD_SIZE 50

// árvore binária
typedef struct tree_node {
    char word[MAX_WORD_SIZE];
    linked_list* list;
    struct tree_node* left;
    struct tree_node* right; 
} tree_node;

typedef struct {
    tree_node* tree_route;
} binary_tree;


// lista ligada
#define MAX_NUM_OCCURRENCES 500

typedef struct list_node {
    int position;
    struct list_node* next_node;
    struct list_node* previous_node; 
} list_node;

typedef struct {
    list_node* list_route;
    list_node* list_end;
} linked_list;


#endif
