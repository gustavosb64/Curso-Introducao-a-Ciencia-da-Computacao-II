#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H


typedef char* elem;

/*
 * Estrutura para os nós da lista
*/
typedef struct node Node;

/*
 * Estrutura para a lista
*/
typedef struct list List;

/*
 * Cria uma lista contendo 26 nós. Cada nó armazena, na variável referente a elem,
 * o valor NULL, e servem para estabelecerem separadores entre cada seção do 
 * alfabeto da lista
*/
List* CreateList();

/*
 * Cria um vetor de índices da lista encadeada. Cada índice do vetor corresponde a 
 * uma letra do alfabeto, e cada campo armazena um ponteiro para o primeiro elemento 
 * da lista com a respectiva letra
*/
Node** CreateArrayNode(List *list);

/*
 * Checa se a lista enviada por parâmetro está vazia
*/
int IsEmptyList(List *list);

/*
 * Adiciona o processo e ao final da lista
*/
int AddLastElem(List *list, elem e);

/*
 * Atualiza o vetor de índices, para que apontem para a primeira palavra de cada
 * letra
*/
int UpdateArrayNode(List *list, Node **array_letters);

/*
 * Adiciona um elemento à lista através de um nó de referência (obtido pelo vetor
 * de índices)
*/
int AddMiddleElemByRefNode(List *list, Node *ref_node, elem e);

/*
 * Checa se o o vetor de índices está atualizado
*/
int IsArrayUpToDate(Node **array_letters);

/*
 * Procura o elemento e na lista com o auxílio do vetor de índices
*/
void SearchElemList(List *list, Node **array_letters, elem e);

/*
 * Imprime os três primeiros elementos da lista em stdout
*/
int PrintFirstThree(List *list);

/*
 * Imprime a lista list em stdout
*/
int PrintList(List *list, Node **array_letters);

/*
 * Libera memória alocada pela lista list
*/
int FreeList(List *list);


#endif