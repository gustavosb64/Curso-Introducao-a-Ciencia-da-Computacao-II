#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H


/*
 * Estrutura contendo os dados dos processos, que são elementos da lista
*/
typedef struct process Process;

/*
 * Estrutura para os nós da lista
*/
typedef struct node Node;

/*
 * Estrutura para a lista
*/
typedef struct list List;

/* 
 * Lê todos os processos passados pelo stdin e os armazena em ProcList
*/
void ReadAllProcesses(List *ProcList);

/*
 * Checa se há processos em ProcList, apontados por node_procList, a serem inseridos 
 * em alguma lista de M_ProcList, conferindo se o tempo atual (counter) é igual ao 
 * tempo de entrada de algum nó (node_procList.t0)
*/
int NewProcessess(List *ProcList, List **M_ProcList, Node **node_procList, int counter, int *cur_max_r);

/*
 * Função que escalona os processos e os imprime na tela
*/
void EscalonarProcessos(List *ProcList);

/*
 * A PARTIR DAQUI, TODAS AS FUNÇÕES SE REFEREM AO TAD LIST
 *
 * Cria uma lista vazia, com ponteiros first e last apontando para NULL
*/
List* CreateList();

/*
 * Checa se a lista enviada por parâmetro está vazia
*/
int IsEmptyList(List *list);

/*
 * Checa se processo e, passado por parâmetro, está na lista list
*/
int InList(List *list, Process e);

/*
 * Adiciona o processo e ao início da lista
*/
int AddFirstElem(List *list, Process e);

/*
 * Adiciona o processo e ao final da lista
*/
int AddLastElem(List *list, Process e);

/*
 * Adiciona o processo e à lista no índice index, passado por parâmetro
*/
int AddMiddleElem(List *list, Process e, int index);

/*
 * Adiciona o processo e à lista, ordenando por tempo de entrada (e.t0)
*/
int AddOrderedByTime(List *list, Process e);

/*
 * Adiciona o processo e à lista, ordenando por ID (e.p), usando nó sentinela
*/
int AddOrderedById(List *list, Process e);

/*
 * Remove primeiro elemento da lista e o armazena em (*e), usando nó sentinela
*/
int RemoveFirstElem(List *list, Process *e);

/*
 * Remove último elemento da lista e o armazena em (*e)
*/
int RemoveLastElem(List *list, Process *e);

/*
 * Remove nó node da lista list, independente da posição que ocupe 
*/
int RemoveMiddleElem(List *list, Node *node);

/*
 * Imprime a lista list em stdout
*/
int PrintList(List *list);

/*
 * Libera memória alocada pela lista list
*/
int FreeList(List *list);


#endif