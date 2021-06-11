#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "lib-utf8.h"
#include "func.h"
#include "print_words.h"
#include "binary_tree.h"


const char ALPHABET[MAX_NUMBER_LETTERS] = {"abcdefghijklmnopqrstuvwxyz"};


static bool read_number(int* option) {
    char int_str[10] = "";
    if (fgets(int_str, 10, stdin) == NULL) {
        fprintf(stderr, "Erro, input de número inválido.\n");
        return false;
    }

    * option = (int) strtol(int_str, NULL, 10);

    return true;
}


static char* read_word(char word[]) {
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


static void separate_string(char* str, long* pos) {
    const char delims[] = " \t\f\v\r\n";

    str = strtok(str, delims);
    * pos = (int) strtol(strtok(NULL, delims), NULL, 10);

}


bool read_file(binary_tree* tree, char file_name[]) {
    FILE* file;

    if (read_name(file_name) == NULL) {
        return false;
    }


    file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro, ficheiro não encontrado.\n");
        return false;
    }


    // line - palavra mais numero de ocorrência
    char line[MAX_WORD_SIZE + 10];
    while ((fgets(line, MAX_WORD_SIZE + 10, file)) != NULL) {
        tree_node* aux_node;
        long pos;
        
        // line - passa a ser apenas a palavra
        separate_string(line, &pos);

        aux_node = find_tree_node(tree->tree_root, line);
        if (aux_node != NULL) {
            if (!add_occurrence(aux_node, tree->tree_root, pos)) {
                fprintf(stderr, "Erro ao adicionar nova ocorrência.\n");
                return false;
            }
        }
        if (aux_node == NULL) {
            if (!add_tree_node(tree, line, pos)) { 
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
    
    if (!read_number(option)) {
        fprintf(stderr,"Erro na leitura da opção\n");
        return false;
    }
    return true;
    
}

// Econtrar todas as ocorrências de uma palavra
bool find_occurrences(binary_tree* tree, char file_name[]) {
    tree_node* node;

    char word[MAX_WORD_SIZE] = "";
    if (read_word(word) == NULL) {
        fprintf(stderr, "Erro, palavra inválida.\n");
        return false;
    }



    node = find_tree_node(tree->tree_root, word);
    if (node == NULL) {
        fprintf(stderr, "Erro, palavra não encontrada.\n");
        return false;
    }

    show_word_occurrences(node, file_name);

    return true;
}

// Econtrar todas as palavras de uma letra
bool find_words_by_letter(binary_tree* tree, char file_name[]) {
    char letter;
    char chr_temp;

    printf("Introduza a letra pretendida: \n");
    fgets_c_u8(&chr_temp, 1, stdin);
    strtobase_u8(&letter, &chr_temp);
    if (!print_words_by_letter(tree, letter)) {
        fprintf(stderr, "Erro, letra não encontrada.\n");
        return false;
    }

    return true;
}

// Econtrar todas as palavras de um grupo de letras
bool find_words_by_group(binary_tree* tree, char file_name[]) {
    int option;
    char letters[MAX_NUMBER_LETTERS] = "";
    char buffer[3] = "";
    char buffer_base[3] = "";

    printf("Escolha a opção que pretende:\n"
            "1 - Intervalo de letras;\n"
            "2 - Introduzir todas as letras pretendidas.\n");
    read_number(&option);
    if (option == 1) {
        printf("Introduza o intervalo da seguindo o exemplo (Ex: a-j):\n");
        fgets_u8(buffer, 3, stdin);
        strtobase_u8(buffer_base, buffer);
        

        int null = 0;
        for (char c = buffer_base[0]; c <= buffer_base[2]; ++c, ++null) {
            letters[null] = c;
        }
    }

    if (option == 2) {
        printf("Escreva todas as letras que deseja seguinto o exemplo (Ex: adjs):");
        fgets_u8(letters, MAX_NUMBER_LETTERS, stdin);
    }

    for (size_t i = 0; i < strlen(letters); ++i) {
        if (!print_words_by_letter(tree, letters[i])) {
            fprintf(stderr, "Erro, letra %c não encontrada.\n", letters[i]);
            return false;
        }
    
    }

    return true;
}
