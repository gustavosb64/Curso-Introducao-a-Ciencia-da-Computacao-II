#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"

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

void read_file(List *list, Node **array_letters){

    char *filename = readline(stdin);
    FILE *input_file = fopen(filename, "r");
   
    char *string; 
    int arr_idx;
    do{
        string = readline(input_file);
//        AddLastElem(list, string);
        arr_idx = string[0] - 97; 
//        printf("arr_idx: %d\n",arr_idx);
//        printf("address arr : %p\n",array_letters[arr_idx]);
        AddMiddleElemByRefNode(list, array_letters[arr_idx], string);
//        printf("address arr : %p\n\n",array_letters[arr_idx]);

    }while(!feof(input_file));

//    TestPrint(array_letters, 2);

    PrintFirstThree(list);

    free(filename);
    fclose(input_file);
    return;
}

int main (int argc, char *argv[]){

    List *list = CreateList();
    Node **array_letters = CreateArrayNode(list);

    int option;
//    int status = 0; //quando igual a 0, não está atualizado
    while(scanf(" %d ", &option)){

        switch(option){

            case 1:
                read_file(list, array_letters);
//                getc(stdin);

                break;

            case 2:
                UpdateArrayNode(list, array_letters);
//                TestPrint(array_letters);
                break;

            case 3:
                char *string = readline(stdin);
                SearchElemList(list, array_letters, string);
                free(string);
                break;

            case 0:
                /*
                printf("---------\n");
                PrintList(list, array_letters);
                */
                FreeList(list);
                free(array_letters);
                return 0;

        }
    }

    /*
    UpdateArrayNode(list, array_letters);
    read_file(list, array_letters);
//    TestPrint(array_letters, 0);
    SearchElemList(list, array_letters, "angry");
    UpdateArrayNode(list, array_letters);
//    TestPrint(array_letters, 0);

    SearchElemList(list, array_letters, "angry");
    SearchElemList(list, array_letters, "cacaca");
    */

    printf("---------\n");
    PrintList(list, array_letters);

    FreeList(list);
    free(array_letters);

    return 0;
}
