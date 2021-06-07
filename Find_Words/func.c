#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "lib-utf8.h"
#include "func.h"
#include "functions_header.h"


const char ALPHABET[MAX_NUMBER_LETTERS] = {"abcdefghijklmnopqrstuvwxyz"};


static int* read_number(int* option) {
    char int_str[10];
    if (fgets(int_str, 11, stdin) == NULL) {
        fprintf(stderr, "Erro, input de número inválido.\n");
        return NULL;
    }

    for (int i = 0; i < strlen(int_str); ++i) {
        if (!isdigit(int_str[i])) {
            fprintf(stderr, "Erro, input de número inválido.\n");
            return NULL;
        }
    }

    * option = (int) strtol(int_str, NULL, 10);

    return option;
}


static char* read_word(char* word) {
    printf("Introduza a palavra (a palavra tem que ter pelo menos três caracteres, números ou letras).\n");
    if (fgets_u8(word, MAX_WORD_SIZE + 1,stdin) == NULL)
        return NULL;

    if (strlen(word) < 3)
        return NULL;

    char buffer[MAX_WORD_SIZE];
    strcpy(buffer, word);
    strtobase_u8(word, buffer);

    return word;
}


static char* read_name(char file_name[]) {
    printf("Introduza o nome do ficheiro que quer ler:\n");
    if (fgets_u8(file_name, MAX_FILE_NAME + 1,stdin) == NULL) {
        fprintf(stderr, "Erro, nome não válido.\n");
        return NULL;
    }

    size_t length;
    length = strlen (file_name);
    if (file_name[length - 1] == '\n')
        file_name[length - 1] = '\0';
    
    return file_name;
}


static void separate_string(char* str[], char* new_str, int* pos) {
    char int_str[10] = "";
    char new_str_utf8[MAX_WORD_SIZE] = "";
    for (int i = 0; i < strlen(* str); ++i) {
        if (!isdigit(* str[i])) {
            strcat(new_str_utf8, str[i]);
        }
        else {
            strcat(int_str, str[i]);
        }
    }
    strtobase_u8(new_str, new_str_utf8);
    * pos = (int) strtol(int_str, NULL, 10);
}


bool read_file(binary_tree* tree, char file_name[]) {
    FILE* file;
    

    if (read_name(file_name) == NULL) {
        return false;
    }

    initialize_binary_tree(tree);

    file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro, ficheiro não encontrado.\n");
        return false;
    }


    char chr;
    while ((chr = fgetc(file)) != EOF) {
        tree_node* aux_node;
        char str[MAX_WORD_SIZE + 10] = "";

        while (chr != '\n') {
            strcat(str, &chr);
        }
        
        int pos;
        char new_str[MAX_WORD_SIZE] = "";
        
        separate_string(&str, new_str, &pos);

        aux_node = find_tree_node(tree->tree_route, new_str);
        if (aux_node != NULL) {
            if (!add_occurrence(aux_node, tree->tree_route, pos)) {
                fprintf(stderr, "Erro ao adicionar nova ocorrência.\n");
                return false;
            }

        }
        if (aux_node == NULL) {
            if (!add_tree_node(tree->tree_route, aux_node,  new_str, pos)) { 
                fprintf(stderr, "Erro na escrita da palavra.\n");
                return false;
            }

        }

    }

    
    fclose(file);

    return true;
}


bool menu(int* option) {
    printf("Escolha a opção:\n");
    printf("0 - Sair do programa\n"
            "1 - Encontrar todas as ocurrências de uma palavra e o seu contexto\n"
            "2 - Mostrar todas as palavras começadas por uma letra\n"
            "3 - Mostrar todas as palavras numa gama de letras\n");
    
    if (read_number(option) == NULL) {
        fprintf(stderr,"Erro na leitura da opção\n");
        return false;
    }
    return true;
    
}

// Econtrar todas as ocorrências de uma palavra
bool find_occurrences(binary_tree* tree, char file_name[]) {
    tree_node* node;

    char word[MAX_WORD_SIZE];
    if (read_word(word)) {
        fprintf(stderr, "Erro, palavra inválida.\n");
        return false;
    }



    node = find_tree_node(tree->tree_route, word);
    if (node == NULL) {
        fprintf(stderr, "Erro, palavra não encontrada.\n");
        return false;
    }

    print_word_occurrences(node, file_name);

    return true;
}

// Econtrar todas as palavras de uma letra
bool find_words_letter(binary_tree* tree, char file_name[]) {
    char letter;
    char chr_temp;

    printf("Introduza a letra pretendida: \n");
    fgets_c_u8(&chr_temp, 1, stdin);
    strtobase_u8(&letter, &chr_temp);
    if (!print_words_letter(tree, letter)) {
        fpritnf(stderr, "Erro, letra não encontrada.\n");
        return false;
    }

    return true;
}

// Econtrar todas as palavras de um grupo de letras
bool find_words_group(binary_tree* tree, char file_name[]) {
    int option;
    char letters[MAX_NUMBER_LETTERS] = "";
    char buffer[3] = "";

    printf("Escolha a opção que pretende:\n"
            "1 - Intervalo de letras;\n"
            "2 - Introduzir todas as letras pretendidas.\n");
    read_number(&option);
    if (option == 1) {
        printf("Introduza o intervalo da seguindo o exemplo (Ex: a-j):\n");
        fgets_u8(buffer, 3, stdin);
        
        
        bool in = false;
        for (int i = 0; i < MAX_NUMBER_LETTERS; ++i) {
            if (ALPHABET[i] == buffer[0]) {
                in = true;
            }
            if (ALPHABET[i] == buffer[2]) {
                strcat(letters, ALPHABET[i]);
                in = false;
                break;
            }
            if (in == true) {
                strcat(letters, ALPHABET[i]);
            }
        }
        
        for (size_t i = 0; i < strlen(letters); ++i) {
            if (!print_words_letter(tree, letters[i])) {
                fprintf("Erro, letra %s não encontrada.\n", letters[i]);
                return false;
            }
        
        }



    }




    if (option == 2) {
        pritnf("Escreva todas as letras que deseja seguinto o exemplo (Ex: adjs):");
        fgets_u8(letters, MAX_NUMBER_LETTERS, stdin);

        for (size_t i = 0; i < strlen(letters); ++i) {
            if (!print_words_letter(tree, letters[i])) {
                fprintf("Erro, letra %s não encontrada.\n", letters[i]);
                return false;
            }
        
        }

    }

}




