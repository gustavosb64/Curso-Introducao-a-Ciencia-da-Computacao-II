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

    if (index == (list->n_elem)){
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

int AddOrderedByTime(List *list, Process e){

    AddLastElem(list, e);

    int counter = 0;
    Node *node = list->first;
    while (node->val.t0 < e.t0){
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

int AddOrderedById(List *list, Process e){

    AddLastElem(list, e);

    int counter = 0;
    Node *node = list->first;
    while (node->val.p < e.p){
        node = node->next;
        counter++;
    }

    if (node->next == NULL) return 0;
    RemoveLastElem(list, &e);

    AddMiddleElem(list, e, counter);

    return 1;
}

int AddOrderedByPriority(List *list, Process e){

    AddLastElem(list, e);

    int counter = 0;
    Node *node = list->first;
    while (node->val.r < e.r){
        node = node->next;
        counter++;
    }

    int check = 1;
    if (node->next == NULL){
        check = 0;
        return check;
    }
    RemoveLastElem(list, &e);

    while(node->val.r == e.r){
        if (node->val.p > e.p)
            break;
        counter++;
    }
    AddMiddleElem(list, e, counter);

    return check;
}

/*
void PercorrerLista(List *list){

    Node *orig_node = list->first;
    List *aux_list = CreateList();

    int counter = 1;
    int del_check = 0;
    Node *aux_node;
    Process aux_e;
    int aux_idx;

    while (orig_node != NULL && counter == orig_node->val.t0){
        AddLastElem(aux_list, orig_node->val);
        orig_node = orig_node->next;
    }

    Node *node = aux_list->first;

    while(!IsEmptyList(aux_list)){
//        printf("---%d\n",node->val.p);

        if (counter >= node->val.t0) node->val.tf -= 1;
        if (node->val.tf == 0){
            printf("%d %d\n", node->val.p, counter); 
            del_check = 1;
        }

        aux_node = node;
        if (node->next != NULL){
            aux_node = node->next;
        }
        else
            aux_node = list->first;

        if (del_check){ 
            SearchRemoveElem(aux_list, &node->val, &aux_e);
            del_check = 0;
        }
        counter++;

        node = aux_node;

        while (orig_node != NULL && counter == orig_node->val.t0){
            AddOrderedByPriority(aux_list, orig_node->val);
            orig_node = orig_node->next;
        }

    }

    FreeList(aux_list);

    return;
}
*/

void PercorrerLista(List *ProcList, List **M_ProcList){

    Node *aux_node = ProcList->first;
    Process aux_proc;

    int counter = 1;
    while(aux_node != NULL && aux_node->val.t0 == counter){
        aux_node = aux_node->next;

        RemoveFirstElem(ProcList, &aux_proc); 
        AddOrderedById(M_ProcList[aux_proc.r - 1], aux_proc);
    }
    Node *cur_pointer = M_ProcList[3]->first;
    Node *cur_pointer2; 

    Process aux_remove;

    int change_check = 0;
    int cur_r = 3;
    int cur_max_r = cur_r;
    int del_check = 0;
    while(!IsEmptyList(ProcList) ||
            !IsEmptyList(M_ProcList[0]) ||
            !IsEmptyList(M_ProcList[1]) ||
            !IsEmptyList(M_ProcList[2]) ||
            !IsEmptyList(M_ProcList[3]) )
    { 
//        printf("%d\n",counter);

        while (cur_pointer == NULL){

            if ( (--cur_r) < 0) cur_r = 3;

            cur_pointer = M_ProcList[cur_r]->first;
        }

        if (change_check == 1 && cur_max_r > cur_pointer->val.r){
            cur_pointer = M_ProcList[cur_max_r]->first;
            cur_r = cur_max_r;
            change_check = 0;
        }
        /*
        printf("---max: %d cur: %d\n",cur_max_r, cur_r);
        */
//        printf("counter: %d id: %d tf: %d cur_r: %d\n",counter, cur_pointer->val.p, cur_pointer->val.tf, cur_r+1);

        cur_pointer->val.tf -= 1;
        if (cur_pointer->val.tf == 0){
            printf("%d %d\n", cur_pointer->val.p, counter); 
            del_check = 1;
            cur_pointer2 = cur_pointer; 
        }

        /*
        if (cur_pointer->val.p == 407){
            printf("counter: %d tf: %d\n",counter, cur_pointer->val.tf);
        }
        */

        counter++;

        cur_max_r = cur_r;
        while(aux_node != NULL && aux_node->val.t0 == counter){
            change_check = 1;

            if (cur_max_r < aux_node->val.r - 1){
                cur_max_r = aux_node->val.r - 1;
            }

            aux_node = aux_node->next;

            RemoveFirstElem(ProcList, &aux_proc); 
            AddOrderedById(M_ProcList[aux_proc.r - 1], aux_proc);
        }
        
        cur_pointer = cur_pointer->next;
        /*
        if (cur_pointer->val.p == 407){
//            printf("cur_r: %d cur_max: %d\n",cur_r, cur_max_r);
        }

        if (cur_max_r <= cur_r){
            cur_pointer = cur_pointer->next;
        }
        else{
        if (cur_max_r > cur_r){
            cur_pointer = M_ProcList[cur_max_r]->first;
            cur_r = cur_max_r;
        }
        */

        if (del_check == 1){
            SearchRemoveElem(M_ProcList[cur_r], &cur_pointer2->val, &aux_remove);
            del_check = 0;
        }
        
    }

    for (int i=0; i<4; i++){
        PrintList(M_ProcList[i]);
    }

    return;
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

int GetFirstElem(List *list, Process *e){

    if(IsEmptyList(list)) return 1;

    *e = list->first->val;
    return 0;
}

Node* SearchElemList(List *list, Process e, int *error, int *index){

    if(IsEmptyList(list)){
        *error = 1;
        return NULL;
    }

    Node *dest_node;
    dest_node = list->first;
    *index = 0;

    while (dest_node != NULL){
        if (dest_node->val.p == e.p) return dest_node;
        dest_node = dest_node->next;
        *index = *index+1;
    }
    
    *error = 2;
    return NULL;
}

int RemoveFirstElemR(List *list){

    if(IsEmptyList(list)) return 1;

    Node *aux_node = list->first->next;

    if (aux_node != NULL)
        aux_node->prev = NULL; 

    free(list->first);
    list->first = aux_node;

    list->n_elem--;

    return 0;
}

int RemoveOddEven(List *list, Process *e){
    
    if(IsEmptyList(list)) return 1;

    if((list->n_elem)%2) RemoveFirstElem(list, e);
    else RemoveLastElem(list, e);

    return 0;
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
