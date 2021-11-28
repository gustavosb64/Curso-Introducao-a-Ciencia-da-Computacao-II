#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H


typedef char* elem;

typedef struct node Node;

typedef struct list List;

typedef struct arrayNode Arraynode;

List* CreateList();

Node** CreateArrayNode(List *list);

int IsEmptyList(List *list);

int AddLastElem(List *list, elem e);

int UpdateArrayNode(List *list, Node **array_letters);

int AddMiddleElemByRefNode(List *list, Node *ref_node, elem e);

int IsArrayUpToDate(Node **array_letters);

void SearchElemList(List *list, Node **array_letters, elem e);

int PrintFirstThree(List *list);

int PrintList(List *list, Node **array_letters);

int FreeList(List *list);


#endif