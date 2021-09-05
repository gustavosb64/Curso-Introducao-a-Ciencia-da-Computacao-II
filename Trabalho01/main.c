/* Título: CAMPO MINADO
 * Nome: Gustavo Siqueira Barbosa
 * NºUSP: 10728122
 * Código do curso: SCC0201
*/
#include <stdio.h>
#include <stdlib.h>

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

void print_board_with_hints(){

    char *board_name = readline(stdin);
    FILE *File_board = fopen(board_name, "r");

    printf("checkpoint: void_board_with_hints()\n");     

    free(board_name);
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
