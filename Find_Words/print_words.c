#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"
#include "binary_tree.h"
#include "linked_list.h"



bool add_occurrence(tree_node* aux_node, long pos) {
    if (!add_list_node(aux_node->list, pos)) { 
        fprintf(stderr, "Erro ao adicionar ocorrência.\n");
        return false;
    }

    return true;
}


// Escrever contexto da palavra (frase da palavra e frase posterior)
static void print_context(list_node* node, char file_name[]) {
    FILE* file;

    // como já foi feita a verificação do nome do ficheiro quando foi feita 
    // a sua leitura, não e necessário fazer essa verificação de novo
    file = fopen(file_name, "r");
    fseek(file, node->position, SEEK_SET);

    while (true) {
        fseek(file, -2, SEEK_CUR);
        if (fgetc(file) == '.' || ftell(file) == 1) 
            break;
    }

    int dot_count = 0;
    while (dot_count < 2) {
        char chr = (char) fgetc(file);
        if (chr == EOF) {
            break;
        }
        if (chr == '.') {
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




// Escrever todas as ocorrências de uma palavra
bool show_word_occurrences(tree_node* node, char file_name[]) {
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


// Escrever o número das ocurrências da palavra dada
static void print_occurrence_numbers(tree_node* node) {
    list_node* i = node->list->list_root;
    while (i != NULL) {
        printf("%ld ", i->position);
        i = node->list->list_root->next_node;
    }
    printf("\n");
}


// Escrever todas as palavras de uma letra
bool print_words_by_letter(binary_tree* tree, char letter) {
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
        print_occurrence_numbers(node);
    }
    return true;
}
