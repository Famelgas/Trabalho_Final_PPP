#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "lib-utf8.h"
#include "func.h"

const char NOT_LETTERS[] = {" \n\f\r\t\v,.!_-()?:;"};

static bool read_name(char* file_name) {
    printf("Introduza o nome do ficheiro que quer ler:\n");
    if (fgets_u8(file_name, MAX_FILE_NAME + 1,stdin) == NULL) {
        fprintf(stderr, "Erro, nome não válido.\n");
        return false;
    }

    size_t length;
    length = strlen (file_name);
    if (file_name[length - 1] == '\n')
        file_name[length - 1] = '\0';
    
    return true;
}

static bool write_new_word(char str[], char pos[], FILE* new_file, FILE* file) {

    
    strcat(str, " ");
    strcat(str, pos);
    strcat(str, "\n");

    
    if (fputs(str, new_file) == EOF) {
        fprintf(stderr, "Erro de escrita no ficheiro de saída.\n");
        return false;
    }
    
    return true;
}


bool read_file(char file_name[], char new_file_name[]) {
    FILE* file, * new_file;

    if (!read_name(file_name)) {
        return false;
    }
    
    
    file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro, ficheiro não encontrado.\n");
        return false;
    }
    
    strcpy(new_file_name, "idx_");
    strcat(new_file_name, file_name);
    new_file = fopen(new_file_name, "w");

    char chr;
    char str[50];
    while ((chr = fgetc(file)) != EOF) {
        size_t i = 0;
        long position = 0;
        bool new_word = false;
        do {
            if (NOT_LETTERS[i] == chr) {
                new_word = true;
                break;
            }
            ++i;
        } while (i < strlen(NOT_LETTERS)); 
        
        if (new_word) {
            if (strlen(str) >= 3) {
                char pos[15];
                position = ftell(file);
                position -= (int) strlen(str);
                // fazer conversao do numero (posicao) para string
                sprintf(pos, "%d", (int) position);
                write_new_word(str, pos, new_file, file);
                strcpy(str, "\0");
            }
            else {
                strcpy(str, "\0");
            }

        }
        
        if (!new_word) {
            strcat(str, &chr);
        }
        
    }

    fclose(new_file);
    fclose(file);
    return true;
}
