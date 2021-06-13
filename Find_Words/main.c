/*
 * O objetivo do trabalho é permitir procurar palavras num texto em português, codificado em utf-8, e mostrá-las em contexto.
 * Há duas fases, cada uma delas implementada por um programa autónomo:
 * A primeira para ler o ficheiro, isolar as palavras e criar um ficheiro com as palavras encontradas.
 * A segunda para ler o ficheiro produzido na primeira fase e criar um índice em memória, que permite mostrar em contexto as palavras que o utilizador queira analisar. Mostrar em contexto significa mostrar a palavra em conjunto com palavras que a precedem e lhe sucedem. O utilizador também deve poder pedir para serem listadas todas as palavras que começam por uma determinada letra, ou intervalo de letras.
 * Primeira fase:
 * O programa pede ao utilizador o nome do ficheiro de texto a processar
 * Percorre depois o ficheiro de texto, isolando cada palavra e anotando a posição (número de bytes desde o início do ficheiro da primeira letra da palavra) em que essa palavra surge no texto.
 * As palavras são constituídas apenas por letras e algarismos; todos os outros carateres devem ser ignorados e considerados separadores.
 * Só deve considerar palavras com mais de três carateres.
 * À medida que identifica uma palavra vai escrevendo num ficheiro essa palavra (preservando as maiúsculas/minúsculas, acentos e cedilhas) acompanhada da sua posição no texto.
 * O nome do ficheiro onde escreve as palavras é igual ao ficheiro que contém o texto, mas com o prefixo "idx_"
 * O ficheiro é um ficheiro de texto, com um par palavra - posição por linha, separados por um espaço. Por exemplo, 'trabalho 347' se houver uma ocorrência da palavra 'trabalho' a começar no tricentésimo quadragésimo sétimo byte do ficheiro de texto.
 * 
 * Segunda fase:
 * O programa pede ao utilizador o nome do ficheiro de texto.
 * O ficheiro com os pares palavra-posição tem um nome construído como na primeira fase.
 * O programa lê os pares palavra-posição desse ficheiro e constrói um índice, sob a forma de uma árvore binária. Como cada palavra pode surgir várias vezes no mesmo texto, em cada nó da árvore binária é guardada a raiz para uma lista ligada que contém todas as posições em que a mesma palavra surge.
 * Considera-se que se trata da mesma palavra se a única diferença forem acentos, cedilhas, ou maiúsculas/minúsculas.
 * O índice, ou seja, a árvore binária e a lista associada a cada nó, deve ser construído com recurso a memória dinâmica.
 * Por cada palavra que o utilizador escolha devem ser mostradas todas as ocorrências, dentro do seu contexto, por ordem decrescente da posição em que ocorrem no ficheiro.
 * O contexto é a frase em que a frase se encontra, bem como a frase posterior. (As frases são delimitadas pelo caráter '.').
 * O texto não deve ser lido integralmente para memória: a posição de cada palavra, contida no índice, deve ser usada para ler do ficheiro de texto, diretamente, a parte a mostrar como contexto de cada palavra.
 * O utilizador deve ainda poder pedir para serem listadas todas as palavras que comecem por uma letra, ou gama de letras. Neste caso devem ser listadas todas as ocorrências das palavras nesse intervalo, uma por linha, no formato, "palavra posição1 posição2 posição3 ... posiçãoN" com as posições ordenadas por ordem decrescente.
 * 
 * 
 * 
 * O programa começa por pedir ao ultilizador o nome do ficheiro de texto que foi lido na 
 * primeira fase do programa. De seguida apresenta um menu, tendo este 5 opções. 
 * Escolhendo a opção zero o programa sai.
 * Escolhendo a primeira opção o utilizador deve introduzir uma palavra e serão apresentadas todas as ocurrências da mesma, 
 * bem como o contexto em que esta se encontra.
 * Escolhendo a segunda opção o utilizador deve introduzir uma letra e serão apresentadas todas as palavras que começam
 * por essa letra e o número da posição em que cada uma das ocorrências dessa palavra se encontra no texto.
 * Escolhendo a terceira opção o programa apresenta mais duas opções. Na primeira o utilizador introduz um intervalo de letras e 
 * serão apresentadas todas as palavras começadas por essas letras bem como o número da posição em que cada uma das ocorrências 
 * dessa palavra se encontra no texto. Na segunda, o utilizador deve introduzir ele próprio as letras que deseja pesquisar e o resultado 
 * será o mesmo para essas letras.
 * A última opção serve apenas para mostrar a árvore binária com as palavras que foram lidas no texto.
 * 
 * O programa consiste em uma árvore binária, em que cada nó contém uma palavra bem como uma lista ligada com todas as ocurrências da 
 * palavra.
 * O ficheiro func.c contém todas as funções gerais, chamadas pela função main. O ficheiro print_words.c contém todas as funções relacionadas 
 * com a impressão das palavras escolhidas pelo utilizador. No ficheiro binary_tree.c estão as funções que modificam a árvore. Por último, 
 * no ficheiro linked_list.c estão as funções que modificam a lista ligada presente em cada nó da árvore.
 * Nos ficheiros da árvore e da lista existem também duas funções (print_tree e print_list) que são chamadas apenas se o utilizador desejar e 
 * que imprimem a árvore binária com todas as palavras guardadas do texto. 
 *
 */







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

    int option = 10;

    // o programa continua até o utilizador escolher sair
    while (true) {
        while (!menu(&option)) {
            printf("Introduza um número.\n");
        }

        if (option == 0) {
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
        if (option == 4 ) {
            print_tree(tree->tree_root, 0);
        }

    }

    return 0;
}
