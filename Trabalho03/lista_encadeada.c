#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"

struct node{
    Process val;
    struct node *next;
    struct node *prev;
};

struct list{
    Node *first;
    Node *last;
    int n_elem;
};

List* CreateList(){
    List *list = (List *) malloc(sizeof(List)); 
    if (list == NULL){
        printf("CreateList FAILED: Memory is full.\n");
        return NULL;
    }
    
    list->first = NULL; 
    list->last = list->first; 

    list->n_elem = 0; 

    return list;
}

int IsEmptyList(List *list){
    if (!list->n_elem) return 1;
    else return 0;
}

int GetNumberElem(List *list){

    return list->n_elem;
}

int AddLastElem(List *list, Process e){

    Node *aux_node = (Node *) malloc(sizeof(Node));
    if (aux_node == NULL) return 1;

    if (IsEmptyList(list)){
        list->first = aux_node;
        list->first->prev = NULL;
    }
    else {
        list->last->next = aux_node; 
        aux_node->prev = list->last;
    }

    list->last = aux_node;

    list->last->val = e;
    list->last->next = NULL;

    list->n_elem++;

    return 0;
}

int AddFirstElem(List *list, Process e){
    Node *aux_node = (Node *) malloc(sizeof(Node));
    if (aux_node == NULL) return 1;

    if (IsEmptyList(list)){
        list->first = aux_node;
        list->first->prev = NULL;
    }
    else {
        list->first->prev = aux_node; 
        aux_node->next = list->first;
    }

    list->first = aux_node;

    list->first->val = e;
    list->first->prev = NULL;

    list->n_elem++;
    return 0;
}

int AddMiddleElem(List *list, Process e, int index){

    if (index == 0){
        if (AddFirstElem(list, e)) return 1;
        return 0;
    }

    if (index == (list->n_elem - 1)){
        if (AddLastElem(list, e)) return 1;
        return 0;
    }

    Node *node = (Node *) malloc(sizeof(Node));
    if (node == NULL) return 1;

    Node *aux = list->first;
    int i=1;
    while (i < index){
        aux = aux->next;
        i++;
    }

    node->next = aux->next;
    aux->next = node;
    node->prev = aux;

    node->val = e;

    return 0;
}

int AddOrderedElem(List *list, Process e){

    AddLastElem(list, e);

    int counter = 0;
    Node *node = list->first;
    while (node->val.p < e.p){
        node = node->next;
        counter++;
    }

    int check = 1;
    if (node->next == NULL){
        check = 0;
        return check;
    }
    RemoveLastElem(list, &e);

    AddMiddleElem(list, e, counter);

    return check;
}

int RemoveLastElem(List *list, Process *e){

    if(IsEmptyList(list)) return 1;

    *e = list->last->val;
    
    Node *aux_node = list->last->prev;

    if (aux_node != NULL)
        aux_node->next = NULL; 

    free(list->last);
    list->last = aux_node;

    list->n_elem--;

    return 0;
}

int RemoveFirstElem(List *list, Process *e){

    if(IsEmptyList(list)) return 1;

    *e = list->first->val;
    
    Node *aux_node = list->first->next;

    if (aux_node != NULL)
        aux_node->prev = NULL; 

    free(list->first);
    list->first = aux_node;

    list->n_elem--;

    return 0;
}

int InList(List *list, Process e){

    if(IsEmptyList(list)) return -1;

    AddLastElem(list, e);

    Node *node = list->first;
    while (node->val.p != e.p)
        node = node->next;

    int check = 1;
    if (node->next == NULL) check = 0;
    
    RemoveLastElem(list, &e);

    return check;
}

/*
Process* GetFirstElem(List *list){

    if(IsEmptyList(list)) return 1;

    return list->first->val;
}

int RemoveFirstElemR(List *list){

    if(IsEmptyList(list)) return 1;

    int e = list->first->val;
    
    Node *aux_node = list->first->next;

    if (aux_node != NULL)
        aux_node->prev = NULL; 

    free(list->first);
    list->first = aux_node;

    list->n_elem--;

    return e;
}

int RemoveOddEven(List *list, Process *e){
    
    if(IsEmptyList(list)) return 1;

    if((list->n_elem)%2) RemoveFirstElem(list, e);
    else RemoveLastElem(list, e);

    return 0;
}

int InList(List *list, Process e){

    if(IsEmptyList(list)) return -1;

    AddLastElem(list, e);

    Node *node = list->first;
    while (node->val != e)
        node = node->next;

    int check = 1;
    if (node->next == NULL) check = 0;
    
    RemoveLastElem(list, &e);

    return check;
}


int SearchRemoveElem(List *list, Process *e, Process *dest_e){

    if(IsEmptyList(list)) return 1;

    Node *dest_node;
    int error = 0;
    int index = 0;

    dest_node = SearchElemList(list, *e, &error, &index);
    switch (error){
        case 1: 
            return 1;
        case 2:
            printf("Element not found!\n");
            free(dest_node);
            return 0;
    }

    if (index == 0){
        if (RemoveFirstElem(list, dest_e)) return 1;
    }
    else if (index == (list->n_elem-1)){
        if (RemoveLastElem(list, dest_e)) return 1;
    }
    else{
        RemoveMiddleElem(dest_node, dest_e);
        list->n_elem--;
    }

    return 0;
}

int IndexRemoveElem(List *list, Process *e, int index){

    if(IsEmptyList(list)) return 1;
    if (index > list->n_elem) return 2;
    if (index < 0) return 3;
    
    if (index == 0){
        if (RemoveFirstElem(list, e)) return 1;
        return 0;
    }

    if (index == (list->n_elem - 1)){
        if (RemoveLastElem(list, e)) return 1;
        return 0;
    }

    Node *aux = list->first;
    int i=1;
    while (i <= index){
        aux = aux->next;
        i++;
    }
   
    RemoveMiddleElem(aux, e);
    list->n_elem--;

    return 0;
}

int RemoveMiddleElem(Node *node, Process *e){

    if(node == NULL) return 1;
    if (node->prev == NULL) return 2;
    if (node->next == NULL) return 3;

    node->prev->next = node->next;    
    node->next->prev = node->prev;
    
    node->next = NULL;
    node->prev = NULL;
    *e = node->val;

    free(node); 

    return 0;
}
*/

int PrintList(List *list){

    if(IsEmptyList(list)) return 1;
    
    Node *aux_node = list->first;
    
    while(aux_node!=NULL){
        printf("%d ",aux_node->val.p);
        printf("%d ",aux_node->val.t0);
        printf("%d ",aux_node->val.tf);
        printf("%d\n",aux_node->val.r);
        aux_node = aux_node->next;
    }

    return 0;
}

int FreeList(List *list){
    
    if(IsEmptyList(list)){
        free(list->first); 
        free(list);
        return 1;
    }

    Node *aux_node = list->first;
    Node *aux_node2;
    while(aux_node!=NULL){
        aux_node2 = aux_node;
        aux_node = aux_node->next;
        free(aux_node2);
    }
    free(aux_node);
    free(list);

    return 0;
}
