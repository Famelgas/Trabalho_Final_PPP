#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"
#include "binary_tree.h"
#include "linked_list.h"



// Escrever contexto da palavra (frase da palavra e frase posterior)
static void print_context(list_node* node, char file_name[]) {
    FILE* file;

    // como já foi feita a verificação do nome do ficheiro quando foi feita 
    // a sua leitura, não e necessário fazer essa verificação de novo
    file = fopen(file_name, "r");
    fseek(file, node->position, SEEK_SET);

    while (true) {
        fseek(file, -2, SEEK_CUR);
        if (ftell(file) == 0 || fgetc(file) == '.') 
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
    
    while (i != NULL) {
        print_context(i, file_name);
        i = i->next_node;
    }

    return true;
}


// Escrever o número das ocurrências da palavra dada
static void print_occurrence_numbers(tree_node* node) {
    list_node* i = node->list->list_root;
    while (i != NULL) {
        printf("%ld ", i->position);
        i = i->next_node;
    }
    printf("\n");
}


// Escrever todas as palavras de uma letra
void print_words_by_letter(tree_node* tree_root, char letter) {
    if (tree_root->word[0]== letter) {
        printf("%s ", tree_root->word);
        print_occurrence_numbers(tree_root);
    }
    
    if (tree_root->left != NULL) {
        print_words_by_letter(tree_root->left, letter);
    }

    if (tree_root->right != NULL) {
        print_words_by_letter(tree_root->right, letter);
    }
      
}
