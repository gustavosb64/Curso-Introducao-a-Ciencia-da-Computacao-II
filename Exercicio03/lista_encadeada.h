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

int AddFirstElem(List *list, elem e);

int UpdateArrayNode(List *list, Node **array_letters);

int AddMiddleElemByRefNode(List *list, Node *ref_node, elem e);

int RemoveLastElem(List *list, elem *e);

int RemoveFirstElem(List *list, elem *e);

elem GetFirstElem(List *list);

elem RemoveFirstElemR(List *list);

int RemoveOddEven(List *list, elem *e);

int InList(List *list, elem e);

int IsArrayUpToDate(Node **array_letters);

void SearchElemList(List *list, Node **array_letters, elem e);

int SearchRemoveElem(List *list, elem *e, elem *dest_e);

int IndexRemoveElem(List *list, elem *e, int index);

int RemoveMiddleElem(Node *node, elem *e);

int TestPrint(Node **array_letters, int i);

int PrintFirstThree(List *list);

int PrintList(List *list, Node **array_letters);

int FreeList(List *list);


#endif