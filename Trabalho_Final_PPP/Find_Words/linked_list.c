#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "linked_list.h"


linked_list* initialize_linked_list() {
    linked_list* list = malloc(sizeof(linked_list)); 
    list->list_root = NULL;
    return list;
}


static list_node* initialize_node(long pos) {
    list_node* node = malloc(sizeof(list_node));
    if (node == NULL) {
        fprintf(stderr, "Erro, não ha espaço para a criação de um novo nó.\n");
        return false;
    }

    // criação do novo nó
    node->position = pos;
    node->next_node = NULL;
    node->previous_node = NULL;
    
    return node;
}


bool add_list_node(linked_list* node, long pos) {
    list_node* aux = initialize_node(pos);
    // adiciona-se sempre o novo nó na primeira posição da lista para facilitar
    // a escrita das ocurrências por ordem decrescente
    if (node->list_root == NULL) {
        node->list_root = aux;
    }
    else {
        aux->next_node = node->list_root;
        node->list_root->previous_node = aux;
    }
        node->list_root = aux;
    

    return true;
}


void print_list(list_node* list_root) {
    list_node* node = list_root;
    while (node != NULL) {
        printf("%ld ", node->position);
        node = node->next_node;
    }
}

