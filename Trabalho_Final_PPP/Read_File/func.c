#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "lib-utf8.h"
#include "func.h"


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
    char str[50] = "";
    while (true) {
        char chr_temp = fgetc(file);
        long position = 0;
        bool new_word = false;

        char buffer[2] = "\0";
        char buffer_base[2] = "\0";
        buffer[0] = chr_temp;
        strtobase_u8(buffer_base, buffer);
        chr = buffer_base[0];

        if (!isalnum(chr)) {
            new_word = true;
        }

        if (new_word) {
            if (strlen(str) >= 3) {
                char pos[15];
                position = ftell(file) - strlen(str);
                // fazer conversao do numero (posicao) para string
                sprintf(pos, "%ld", position);
                write_new_word(str, pos, new_file, file);
            }
            strcpy(str, "\0");
            new_word = false;
        }
        else {
            char buffer_cat[2] = "\0";
            buffer_cat[0] = chr;
            strcat(str, buffer_cat);
        }
        
        if (chr == EOF) {
            break;
        }
    }

    fclose(new_file);
    fclose(file);
    return true;
}