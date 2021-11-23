/* 
 * Título: SIMULADOR DE ESCALONADOR DE PROCESSOS
 * Nome: Gustavo Siqueira Barbosa
 * NºUSP: 10728122
 * Código do curso: SCC0201
*/

#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"

#define BUFFER 4096

int main(int argc, char *argv[]){

    int p, t0, tf, r;

    //São utilizadas 4 listas, cada uma referente a uma prioridade,
    //armazenadas em uma matriz
    List **M_ProcList = (List **) malloc(4 * sizeof(List**));
    for (int i=0; i < 4; i++)
        M_ProcList[i] = CreateList();

    List *ProcList = CreateList();

    Process process; 
    do{

        scanf("%d %d %d %d ",&p,&t0,&tf,&r);

        process.p = p;
        process.t0 = t0;
        process.tf = tf;
        process.r = r;

        //Caso p já esteja na lista, busca o próximo ID válido
        while (InList(ProcList, process) == 1)
            process.p += 1;

        AddOrderedByTime(ProcList, process);
//        AddOrderedById(ProcList, process);

        /*
        while (InList(M_ProcList[process.r - 1], process) == 1)
            process.p += 1;

//        AddLastElem(M_ProcList[process.r - 1], process);
        AddOrderedElem(M_ProcList[process.r - 1], process);
        */

    }while(!feof(stdin)); 

    PrintList(ProcList);
    printf("-----------------\n");

    PercorrerLista(ProcList, M_ProcList);

    /*
    while(!IsEmptyList(ProcList) ||
            !IsEmptyList(M_ProcList[0]) ||
            !IsEmptyList(M_ProcList[1]) ||
            !IsEmptyList(M_ProcList[2]) ||
            !IsEmptyList(M_ProcList[4]) )
    { 

    }
    */
    
    /*
    for(int i=0; i<4; i++)
        PrintList(M_ProcList[i]);
    */

    //Liberando memória
    FreeList(ProcList);
    for(int i=0; i<4; i++)
    FreeList(M_ProcList[i]);
    free(M_ProcList);

    return 0;
}

/*
void print(Process *ProcList, int count){

    for (int i=0; i<count; i++){
        Process proc = ProcList[i];
        printf("%d %d %d %d\n", proc.p, proc.t0, proc.tf, proc.r);
    }

    return;
}

int inArray(Process *ProcList, Process proc, int count){

    for (int i=0; i<=count; i++)
        if (ProcList[i].p == proc.p) return 1;

    return 0;
}
*/
