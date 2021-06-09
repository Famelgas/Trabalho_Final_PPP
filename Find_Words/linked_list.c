#include <stdio.h>
#include <stdlib.h>
#include "functions_header.h"
#include "structs_header.h"


linked_list* initialize_linked_list() {
    linked_list* list = malloc(sizeof(linked_list)); 
    list->list_root = NULL;
    list->list_end = NULL;
    return list;
}


static linked_list* initialize_node(int pos) {
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

// Escrever contexto da palavra (frase da palavra e frase posterior)
void print_context(list_node* node, char file_name[]) {
    FILE* file;

    // como já foi feita a verificação do nome do ficheiro quando foi feita 
    // a sua leitura, não e necessário fazer essa verificação de novo
    file = fopen(file_name, "r");
    fseek(file, node->position, SEEK_SET);

    while (true) {
        fseek(file_name, -1, SEEK_CUR);
        if (fgetc(file) == '.') 
            break;
    }

    int dot_count = 0;
    while (dot_count < 2 && fgetc(file) != EOF) {
        char chr;
        if ((chr = fgetc(file)) == '.') {
            ++dot_count;
            printf("%c", chr);
        }
        else {
            printf("%c", chr);
        }
    }
    printf("\n");

    fclose(file);
}

// Escrever o número das ocurrências da palavra dada
void print_letter_occurrences(tree_node* node) {
    list_node* i = node->list->list_root;
    do {
        printf("%d ", i->position);
        i = node->list->list_root->next_node;
    } while (i != node->list->list_root);
    printf("\n");
}

