#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct maze{
    char **maze;
    int n_lines;
    int n_columns;
    int end_x;
    int end_y;
    int n_people;
    int n_paths;
}Maze;

#define BUFFER 4096
char *readline(FILE *stream) {
    char *string = 0;
    int pos = 0; 

	do{
        if (pos % BUFFER == 0) {
            string = (char *) realloc(string, (pos / BUFFER + 1) * BUFFER);
        }
        string[pos] = (char) fgetc(stream);

    }while(string[pos++] != '\n' && string[pos-1] != '\r' && !feof(stream));

    string[pos-1] = 0;
    string = (char *) realloc(string, pos);

    return string;
}

char *read_maze_line(FILE *stream, Maze *sMaze){
    char *maze_line = (char *) calloc( ((*sMaze).n_columns+1), sizeof(char));
    char c;

    for(int i=0; i <= (*sMaze).n_columns; i++){
        c = (char) fgetc(stream);
        if (c == '#'){
            (*sMaze).n_people += 1;
            maze_line[i] = c;
        }
        else if (c == '.'){
            (*sMaze).n_paths += 1;
            maze_line[i] = c;
        }
    }

    return maze_line;
}

//while end_found == 0, the path is not completed yet. It returns the amount of visited paths
int walk_maze(Maze sMaze, int pos_x, int pos_y, int *end_found){

    sMaze.maze[pos_x][pos_y] = '*';
    int n_visited = 0;

    //if pos(x,y) is the end, end_found becomes 1, and no more paths are searched during return
    if (pos_x == sMaze.end_x && pos_y == sMaze.end_y){
        *end_found = 1;
        return 1;
    }

    //Up
    if (sMaze.maze[pos_x-1][pos_y] == '.' && *end_found == 0)
        n_visited += walk_maze(sMaze, pos_x-1, pos_y, end_found);

    //Right
    if (sMaze.maze[pos_x][pos_y+1] == '.' && *end_found == 0 )
        n_visited += walk_maze(sMaze, pos_x, pos_y+1, end_found);

    //Down
    if (sMaze.maze[pos_x+1][pos_y] == '.' && *end_found == 0 )
        n_visited += walk_maze(sMaze, pos_x+1, pos_y, end_found);

    //Left
    if (sMaze.maze[pos_x][pos_y-1] == '.' && *end_found == 0 )
        n_visited += walk_maze(sMaze, pos_x, pos_y-1, end_found);

    return (n_visited + 1);
}

void Print(Maze sMaze, int visitados){

    int npessoas = sMaze.n_people;
    int caminhos = sMaze.n_paths;
    double exploracao = (visitados*100/caminhos);

    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", npessoas);
    printf("----Numero total de caminhos validos:   %d\n", caminhos);
    printf("----Numero total de caminhos visitados: %d\n", visitados);
    printf("----Exploracao total do labirinto: %.1lf%%\n", exploracao); 

    return;
}

int main(int argc, char *argv[]){

    //Opening file
    char *filename = readline(stdin);
    FILE *fMaze = fopen(filename, "r");
    if (fMaze == NULL) exit(0);

    //reading initial data
    Maze sMaze;
    int start_x, start_y;
    fscanf(fMaze, " %d %d", &sMaze.n_lines, &sMaze.n_columns);
    fscanf(fMaze, " %d %d", &start_x, &start_y);
    getc(fMaze); //reads remanescent '\n' from fMaze

    sMaze.maze = (char **) malloc(sMaze.n_lines * sizeof(char *));
    sMaze.n_people = 0;
    sMaze.n_paths = 0;
    for (int i=0; i < sMaze.n_lines; i++){

        sMaze.maze[i] = read_maze_line(fMaze, &sMaze);

        if (sMaze.maze[i][0] == '.'){
            sMaze.end_x = i;
            sMaze.end_y = 0;
        }
        else if (sMaze.maze[i][sMaze.n_columns-1] == '.'){
            sMaze.end_x = i;
            sMaze.end_y = sMaze.n_columns-1;
        }

    }

    int end_found = 0;
    int n_visited = walk_maze(sMaze, start_x, start_y, &end_found);
    for (int i=0; i < sMaze.n_lines; i++){
        printf("%s\n",sMaze.maze[i]);
    }

    Print(sMaze, n_visited);

    free(filename);
    fclose(fMaze);
    for (int i=0; i<sMaze.n_lines; i++)
        free(sMaze.maze[i]);
    free(sMaze.maze);

    return 0;
}
