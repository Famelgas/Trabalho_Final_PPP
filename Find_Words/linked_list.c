#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "linked_list.h"


linked_list* initialize_linked_list() {
    linked_list* list = malloc(sizeof(linked_list)); 
    list->list_root = NULL;
    list->list_end = NULL;
    return list;
}


static list_node* initialize_node(int pos) {
    list_node* aux = malloc(sizeof(list_node));
    if (aux == NULL) {
        fprintf(stderr, "Erro, não ha espaço para a criação de um novo nó.\n");
        return false;
    }

    // criação do novo nó
    aux->position = pos;
    aux->next_node = NULL;
    aux->previous_node = NULL;
    
    return aux;
}


bool add_list_node(linked_list* node, int pos) {
    list_node* aux = initialize_node(pos);
    // adiciona-se sempre o novo nó na primeira posição da lista para facilitar
    // a escrita das ocurrências por ordem decrescente
    if (node->list_root == NULL) {
        node->list_end = aux;
    }
    else {
        aux->next_node = node->list_root;
        node->list_root->previous_node = aux;
    }
        node->list_root = aux;
    

    return true;
}



