// /home/filipe/DEI/PPP/Trabalho_Final_Procura_de_Palavras/Read_File/idx_text.txt

#include <stdio.h>
#include "func.h"
#include "binary_tree.h"

int main() {
    binary_tree* tree = initialize_binary_tree();
    char file_name[MAX_FILE_NAME];

    if (!read_file(tree, file_name)) {
        fprintf(stderr, "Erro na leitura do ficheiro.\n");
        return 1;
    }

    print_tree(tree->tree_root, 0);

    int option;
    while (!menu(&option)) {
        printf("Introduza um número.\n");
    }

    if (!option) {
        // sair
        return 0;
    }

    if (option == 1) {
        find_occurrences(tree, file_name);
    }
    if (option == 2) {
        // dá-se apenas uma letra e são apresentadas todas as palavras dessa letra
        find_words_by_letter(tree, file_name);
    }
    if (option == 3) {
        // dá-se duas letras diferentes e são apresentadas toodas as palavras de
        // de todas as letras nesse intervalo
        find_words_by_group(tree, file_name);
    }

    

    return 0;
}
