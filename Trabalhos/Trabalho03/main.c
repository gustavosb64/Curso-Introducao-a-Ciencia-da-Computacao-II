/* 
 * Título: SIMULADOR DE ESCALONADOR DE PROCESSOS
 * Nome: Gustavo Siqueira Barbosa
 * NºUSP: 10728122
 * Código do curso: SCC0201
*/

#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"

int main(int argc, char *argv[]){

    List *ProcList = CreateList();

    //Lê todos os processos do stdin e armazena em ProcList
    ReadAllProcesses(ProcList);

    //Escalona os processos lidos e armazenados em ProcList
    EscalonarProcessos(ProcList);

    //Liberando memória
    FreeList(ProcList);

    return 0;
}
