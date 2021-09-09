/* Título: CAMPO MINADO
 * Nome: Gustavo Siqueira Barbosa
 * NºUSP: 10728122
 * Código do curso: SCC0201
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct field{
    int elem;       //número de dicas; -1 caso seja uma bomba
    int hidden;     //quando 1, manter oculto; quando 0, não (utilizado na opção3) 
}Field;

/* Função de leitura de linha
 *  Lê da entrada recebida (stream) uma string até encontrar algum terminador de linha (ou de arquivo) e a retorna
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
*/
void print_board(){
    
    char *board_name = readline(stdin);
    FILE *File_board = fopen(board_name, "r");

    char *line;
    do{
        line = readline(File_board);
        printf("%s",line);
        if (!feof(File_board)) printf("\n");
        free(line);
    }while (!feof(File_board));

    free(board_name);
    fclose(File_board);

    return;
}

/* Pega nome do arquivo a ser lido da stdin e o abre em modo leitura
 * Retorna uma matriz Field** contendo os dados do campo
 * Valores de cada campo do tipo Field:
 *  elem:
 *   -1  = bomba
 *    0 >= campo vazio
 *  hidden:
 *    1 = oculto (padrão)
 *    0 = não oculto
*/
Field** get_board_with_hits(int *n_columns, int *n_lines){

    char *board_name = readline(stdin);
    FILE *File_board = fopen(board_name, "r");
    free(board_name);

    //int **list_field = (int **) malloc(1 * sizeof(int *));
    Field **list_field = (Field **) malloc(1 * sizeof(Field *));
    list_field[0] = (Field *) malloc(1 * sizeof(Field));

    char c;
    int j=0;

    /* A primeira linha é lida separadamente para se pegar o número de colunas.
     * Desta forma, torna-se menos custoso os reallocs posteriores */
    do{

        c = (char) fgetc(File_board);

        if (c == '.'){
            list_field[0][j].elem = 0;
            list_field[0][j].hidden = 1;
            list_field[0] = (Field *) realloc(list_field[0], (j+2)*sizeof(Field));
        }
        else if (c == '*'){
            list_field[0][j].elem = -1;
            list_field[0][j].hidden = 1;
            list_field[0] = (Field *) realloc(list_field[0], (j+2)*sizeof(Field));
        }

        j++;
    
    }while (c != '\n' && !feof(File_board));
    *n_columns = j-1;

    //Lendo o restante das linhas
    int i = 1;
    do{

        list_field = (Field **) realloc(list_field, (i+1)*sizeof(Field *)); 
        list_field[i] = (Field *) malloc((*n_columns) * sizeof(Field));

        j = 0;

        do{

            c = (char) fgetc(File_board);

            if (c == '.'){
                list_field[i][j].elem = 0;
                list_field[i][j].hidden = 1;
            }
            else if (c == '*'){
                list_field[i][j].elem = -1;
                list_field[i][j].hidden = 1;
            }

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
              O campo apenas é incrementado quando for >= 0, isto é, quando estiver vazio*/
            if (list_field[l][k].elem == -1){

                //Verificações em linha acima
                if (l > 0){
                    if (k > 0){
                        if (list_field[l-1][k-1].elem >= 0) list_field[l-1][k-1].elem += 1;
                    }

                    if (list_field[l-1][k].elem >= 0) list_field[l-1][k].elem += 1;

                    if (k < *n_columns-1){
                        if (list_field[l-1][k+1].elem >= 0) list_field[l-1][k+1].elem += 1;
                    }
                }

                //Verificações em linha abaixo
                if (l < *n_lines-1){
                    if (k > 0){
                        if (list_field[l+1][k-1].elem >= 0) list_field[l+1][k-1].elem += 1;
                    }

                    if (list_field[l+1][k].elem >= 0) list_field[l+1][k].elem += 1;

                    if (k < *n_columns-1){
                        if (list_field[l+1][k+1].elem >= 0) list_field[l+1][k+1].elem += 1;
                    }
                }

                //Verificações na linha atual
                if (k > 0 && list_field[l][k-1].elem >= 0) list_field[l][k-1].elem += 1;
                if (k < (*n_columns - 1) && list_field[l][k+1].elem >= 0) list_field[l][k+1].elem += 1;

            }
        }

    }

    fclose(File_board);

    return list_field;
}

/* Imprime o campo minado com as posições das bombas e as dicas 
*/
void print_board_with_hints(Field **list_field, int n_columns, int n_lines){

    //Imprimir na tela
    for (int l=0; l < n_lines; l++){
        for (int k=0; k < n_columns; k++){
            if (list_field[l][k].elem == 0) printf(".");
            else if (list_field[l][k].elem < 0) printf("*");
            else printf("%d",list_field[l][k].elem);
        }
        printf("\n");
    }

    //Liberando memória
    for (int l=0; l < n_lines; l++){
        free(list_field[l]);
    }
    free(list_field);

    return;
}

/* Função recursiva que caminha pelo tabuleiro a fim de retirar o status de oculto dos campos vazios por onde passa.
 * Quando encontra um campo vazio contendo uma dica, o revela e retorna, sem continar seu caminho.
 * Ao passar por um campo vazio com 0 dicas, checa todos os 8 campos adjacentes a ele.
 * A função é chamada recursivamente até acabarem todos os caminhos possíveis.
*/
Field** walk_through_board(Field **list_field, int x, int y, int n_columns, int n_lines){
    
    //caso o campo encontrado seja uma bomba ou tenha uma dica, retornar
    if (list_field[x][y].elem != 0){

        if (list_field[x][y].elem > 0)
            list_field[x][y].hidden = 0;

        return list_field;
    }

    //assim que se passa pelo campo, o mesmo deixa de ser oculto
    list_field[x][y].hidden = 0;

    //caminhando para cima
    if (x > 0){

        //mesma coluna
        if (list_field[x-1][y].hidden != 0)
            list_field = walk_through_board(list_field, x-1, y, n_columns, n_lines);
        
        //coluna anterior
        if (y > 0 && list_field[x-1][y-1].hidden != 0)
            list_field = walk_through_board(list_field, x-1, y-1, n_columns, n_lines);

        //coluna seguinte
        if (y < (n_columns-1) && list_field[x-1][y+1].hidden != 0)
            list_field = walk_through_board(list_field, x-1, y+1, n_columns, n_lines);

    }

    //caminhando para baixo
    if (x < (n_lines-1) ){

        //mesma coluna
        if (list_field[x+1][y].hidden != 0)
            list_field = walk_through_board(list_field, x+1, y, n_columns, n_lines);
        
        //coluna anterior
        if (y > 0 && list_field[x+1][y-1].hidden != 0)
            list_field = walk_through_board(list_field, x+1, y-1, n_columns, n_lines);

        //coluna seguinte
        if (y < (n_columns-1) && list_field[x+1][y+1].hidden != 0)
            list_field = walk_through_board(list_field, x+1, y+1, n_columns, n_lines);

    }

    //mantendo-se na mesma linha
    if (y > 0 && list_field[x][y-1].hidden != 0)
        list_field = walk_through_board(list_field, x, y-1, n_columns, n_lines);
    if (y < (n_columns-1) && list_field[x][y+1].hidden != 0)
        list_field = walk_through_board(list_field, x, y+1, n_columns, n_lines);

    return list_field;

}

/* OPÇÃO 3: 
 *  Lê duas entradas de coordenadas do stdin e realiza as análises necessárias:
 *      Revela apenas o campo em questão, caso seja 
*/
void user_control(Field **list_field, int n_columns, int n_lines){
    int x, y;
    scanf(" %d %d", &x, &y);

    //Caso as coordenadas indiquem um campo com bomba
    if (list_field[x][y].elem == -1){

        print_board_with_hints(list_field, n_columns, n_lines); 

        return;
    }

    //Caso as coordenads indiquem um campo vazio (com ou sem dica)
    list_field = walk_through_board(list_field, x, y, n_columns, n_lines);
    
    //Imprime tabuleiro com os campos desconhecidos marcados com 'X'
    for (int l=0; l < n_lines; l++){
        for (int k=0; k < n_columns; k++){
            if (list_field[l][k].hidden) printf("X");
            else if (list_field[l][k].elem == 0) printf(".");
            else if (list_field[l][k].elem < 0) printf("*");
            else printf("%d",list_field[l][k].elem);
        }
        printf("\n");
    }

    //Liberando memória
    for (int l=0; l < n_lines; l++){
        free(list_field[l]);
    }
    free(list_field);

    return;
}

int main(int argc, char *argv[]){

    int op;
    scanf(" %d", &op);
    getc(stdin);

    int n_lines, n_columns;
    Field **list_field;
    switch(op){

        case 1:
            print_board();
            break;

        case 2:
            list_field = get_board_with_hits(&n_columns, &n_lines); 
            print_board_with_hints(list_field, n_columns, n_lines);

            break;

        case 3:
            list_field = get_board_with_hits(&n_columns, &n_lines); 
            user_control(list_field, n_columns, n_lines);
            break;

        default:
            break;
    }

    return 0;
}
