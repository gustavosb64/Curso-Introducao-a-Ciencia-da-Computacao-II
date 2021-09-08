/* Título: CAMPO MINADO
 * Nome: Gustavo Siqueira Barbosa
 * NºUSP: 10728122
 * Código do curso: SCC0201
*/
#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"

/* Função de leitura de linha
 *  Lê da entrada recebida (stream) uma string até encontrar algum terminador de linha (ou de arquivo) e a retorna
 *      Parâmetros: FILE*
 *      Retorno: char*
*/
#define READLINE_BUFFER 4096
char *readline(FILE *stream) {
    char *string = 0;
    int pos = 0; 

	do{

        if (pos % READLINE_BUFFER == 0) 
            string = (char *) realloc(string, (pos / READLINE_BUFFER + 1) * READLINE_BUFFER);

        string[pos] = (char) fgetc(stream);

    }while(string[pos++] != '\n' && string[pos-1] != '\r' && !feof(stream));

    string[pos-1] = 0;
    string = (char *) realloc(string, pos);

    return string;
}

/* OPÇÃO 1: Função de leitura. 
 *  Recebe da entrada padrão o nome do arquivo que contém o tabuleiro a ser lido.
 *  Lê o arquivo e imprime o tabuleiro na saída padrão linha a linha.
 *      Parâmetros: nenhum;
 *      Retorno: void;
*/
void print_board(){
    
    char *board_name = readline(stdin);
    FILE *File_board = fopen(board_name, "r");

    char *line;
    do{
        line = readline(File_board);
        printf("%s\n",line);
        free(line);
    }while (!feof(File_board));

    free(board_name);
    fclose(File_board);

    return;
}

/* Lê de campo de File_board e retorna uma matriz int** contendo os dados do campo
 * -1 = bomba
 *  0 = campo vazio
 *  Parâmetros:
 *      *File_board: arquivo a ser lido
 *      *n_columns: número de colunas da tabela
 *      *n_lines: número de linhas da tabela
 *  Retorno:
 *      int **list_field;
*/
int** get_board_with_hits(FILE *File_board, int *n_columns, int *n_lines){

    int **list_field = (int **) malloc(1 * sizeof(int *));
    list_field[0] = (int *) malloc(1 * sizeof(int));

    char c;
    int j=0;

    /* A primeira linha é lida separadamente para se pegar o número de colunas.
     * Desta forma, torna-se menos custoso os reallocs posteriores */
    do{

        c = (char) fgetc(File_board);

        if (c == '.'){
            list_field[0][j] = 0;
            list_field[0] = (int *) realloc(list_field[0], (j+2)*sizeof(int));
        }
        else if (c == '*'){
            list_field[0][j] = -1;
            list_field[0] = (int *) realloc(list_field[0], (j+2)*sizeof(int));
        }

        j++;
    
    }while (c != '\n' && !feof(File_board));
    *n_columns = j-1;

    //Lendo o restante das linhas
    int i = 1;
    do{

        list_field = (int **) realloc(list_field, (i+1)*sizeof(int *)); 
        list_field[i] = (int *) malloc((*n_columns) * sizeof(int));

        j = 0;

        do{

            c = (char) fgetc(File_board);

            if (c == '.')
                list_field[i][j] = 0;
            else if (c == '*')
                list_field[i][j] = -1;

            j++;

        }while (c != '\n' && !feof(File_board));

        i++;

    }while (!feof(File_board));
    *n_lines = i-1;
    free(list_field[(*n_lines)]); //última linha não é utilizada

    //Analisando presença de bombas 
    for (int l = 0; l < *n_lines; l++){

        for (int k = 0; k < *n_columns; k++){

            /*Quando uma bomba é encontrada, verifica-se sua vizinhança e incrementa o que for necessário
              O campo apenas é incrementado quando for >= 0, isto é, quando não for uma bomba */
            if (list_field[l][k] == -1){

                //Verificações em linha acima
                if (l > 0){
                    if (k > 0){
                        if (list_field[l-1][k-1] >= 0) list_field[l-1][k-1] += 1;
                    }

                    if (list_field[l-1][k] >= 0) list_field[l-1][k] += 1;

                    if (k < *n_columns-1){
                        if (list_field[l-1][k+1] >= 0) list_field[l-1][k+1] += 1;
                    }
                }

                //Verificações em linha abaixo
                if (l < *n_lines-1){
                    if (k > 0){
                        if (list_field[l+1][k-1] >= 0) list_field[l+1][k-1] += 1;
                    }

                    if (list_field[l+1][k] >= 0) list_field[l+1][k] += 1;

                    if (k < *n_columns-1){
                        if (list_field[l+1][k+1] >= 0) list_field[l+1][k+1] += 1;
                    }
                }

                //Verificações na linha atual
                if (k >= 0 && list_field[l][k-1] >= 0) list_field[l][k-1] += 1;
                if (k >= *n_columns-1 && list_field[l][k+1] >= 0) list_field[l][k+1] += 1;

            }
        }

    }

    return list_field;
}

/* Imprime o campo minado com as posições das bombas e as dicas
 *  Parâmetros:
 *      [Nada]
 *  Retorno:
 *      void
*/
void print_board_with_hints(){

    char *board_name = readline(stdin);
    FILE *File_board = fopen(board_name, "r");
    free(board_name);

    int n_lines, n_columns;
    int **list_field = get_board_with_hits(File_board, &n_columns, &n_lines);

    //Imprimir na tela
    for (int l=0; l < n_lines; l++){
        for (int k=0; k < n_columns; k++){
            if (list_field[l][k] == 0) printf(".");
            else if (list_field[l][k] < 0) printf("*");
            else printf("%d",list_field[l][k]);
        }
        printf("\n");
    }

    //Liberando memória
    for (int l=0; l < n_lines; l++){
        free(list_field[l]);
    }
    free(list_field);
    fclose(File_board);

    return;
}

int main(int argc, char *argv[]){

    int op;
    scanf(" %d", &op);
    getc(stdin);

    switch(op){

        case 1:
            print_board();
            break;

        case 2:
            print_board_with_hints();
            break;

        default:
            break;
    }

    return 0;
}
