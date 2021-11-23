#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H


typedef struct process{
    int p;
    int t0;
    int tf;
    int r;
}Process;

typedef struct node Node;

typedef struct list List;

List* CreateList();

int IsEmptyList(List *list);

int GetNumberElem(List *list);

int AddLastElem(List *list, Process e);

int AddFirstElem(List *list, Process e);

int AddMiddleElem(List *list, Process e, int index);

int AddOrderedByTime(List *list, Process e);

int AddOrderedById(List *list, Process e);

int AddOrderedByPriority(List *list, Process e);

int RemoveLastElem(List *list, Process *e);

int RemoveFirstElem(List *list, Process *e);

int InList(List *list, Process e);

int GetFirstElem(List *list, Process *e);

Node* SearchElemList(List *list, Process e, int *error, int *index);

void PercorrerLista(List *ProcList, List **M_ProcList);

int RemoveFirstElemR(List *list);

int RemoveOddEven(List *list, Process *e);

int SearchRemoveElem(List *list, Process *e, Process *dest_e);

int IndexRemoveElem(List *list, Process *e, int index);

int RemoveMiddleElem(Node *node, Process *e);

int PrintList(List *list);

int FreeList(List *list);


#endif
