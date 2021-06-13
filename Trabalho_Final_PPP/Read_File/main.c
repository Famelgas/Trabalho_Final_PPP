#include <stdio.h>
#include <string.h>
#include "func.h"



int main() {
    char file_name[MAX_FILE_NAME + 1];
    char new_file_name[MAX_FILE_NAME + 5];


    if (!read_file(file_name, new_file_name)) {
        fprintf(stderr, "Erro leitura do ficheiro.\n");
        return 1;
    }


    return 0;
}
