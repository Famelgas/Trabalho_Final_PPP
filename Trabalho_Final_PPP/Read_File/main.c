/*
 * Este programa apenas lê o ficheiro de texto dado e coloca todas as palavras do texto
 * num índice que mais tarde será lido pelo segundo programa.
 * O enunciado e a explicação da segunda parte do programa encontram se ambos no comentário 
 * do ficheiro main.c da segunda fase do trabalho, na pasta Find_Words.
 * O texto enviado junto com os ficheiros e apenas o texto usado para testar os programas, 
 * sendo assim pode ser alterado pelo texto desejado.
 * 
 *  
 */


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
