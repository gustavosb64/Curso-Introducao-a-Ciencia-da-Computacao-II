#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_encadeada.h"

struct node{
    elem val;
    struct node *next;
    struct node *prev;
};

struct list{
    Node *first;
    Node *last;
    int n_elem;
};

struct arrayNode{
    char key;
    Node *node;
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

    for(int i=0; i<26; i++)
        AddLastElem(list, NULL);

    return list;
}

Node** CreateArrayNode(List *list){

    Node **array_letters = (Node **) malloc(26 * sizeof(Node*));
    Node *aux_node = list->first;

    int i=0;
    while(aux_node != NULL){
        array_letters[i++] = aux_node;
        aux_node = aux_node->next;
    }

    return array_letters;
}

int IsEmptyList(List *list){
    if (list->n_elem == 0) return 1;
    else return 0;
}

int AddLastElem(List *list, elem e){
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

int AddFirstElem(List *list, elem e){
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

int UpdateArrayNode(List *list, Node **array_letters){

    int counter = 0;
    for (int i=0; i<26; i++){

        if (array_letters[i]->val == NULL){
            if (array_letters[i]->next != NULL && array_letters[i]->next->val != NULL){
                counter++;
                array_letters[i] = array_letters[i]->next;
            }
        }
        else{
            counter++;
            if (array_letters[i]->prev != NULL){
                while(array_letters[i]->prev->val != NULL){
                    array_letters[i] = array_letters[i]->prev;
                }

            }

        }

    }

    printf("%d\n",counter);

    return 0;
}

int AddMiddleElemByRefNode(List *list, Node *ref_node, elem e){

    if (ref_node == NULL) return 1;

    Node *node = (Node *) malloc(sizeof(Node));
    if (node == NULL) return 1;

    node->val = e;

    if ((ref_node)->val == NULL){

        node->next = ref_node->next;
        node->prev = ref_node;
        ref_node->next = node;
        ref_node = node;

        list->n_elem++;

        return 0;
    }

    while (ref_node->prev->val != NULL)
        ref_node = ref_node->prev;

    node->next = ref_node;
    node->prev = ref_node->prev;
    ref_node->prev->next = node;
    ref_node->prev = node;

    list->n_elem++;

    return 0;
}

int RemoveLastElem(List *list, elem *e){

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

int RemoveFirstElem(List *list, elem *e){

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

elem GetFirstElem(List *list){

    if(IsEmptyList(list)) return NULL;

    elem e = list->first->val;
    return e;
}

elem RemoveFirstElemR(List *list){

    if(IsEmptyList(list)) return NULL;

    elem e = list->first->val;
    
    Node *aux_node = list->first->next;

    if (aux_node != NULL)
        aux_node->prev = NULL; 

    free(list->first);
    list->first = aux_node;

    list->n_elem--;

    return e;
}

int RemoveOddEven(List *list, elem *e){
    
    if(IsEmptyList(list)) return 1;

    if((list->n_elem)%2) RemoveFirstElem(list, e);
    else RemoveLastElem(list, e);

    return 0;
}

int InList(List *list, elem e){

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

int IsArrayUpToDate(Node **array_letters){

    for (int i=1; i<26; i++){

        if (array_letters[i]->val == NULL){
            if (array_letters[i]->next != NULL && array_letters[i]->next->val != NULL){
                return 0;
            }
        }
        else{ 
            if (array_letters[i]->prev->val != NULL){
                return 0;
            }
        }

    }

    return 1;
}

void SearchElemList(List *list, Node **array_letters, elem e){

    if(list->n_elem <= 26 || !IsArrayUpToDate(array_letters)){
        printf("Vetor de indices nao atualizado.\n");
        return;
    }

    int key = e[0]-97;
    Node *aux_node = array_letters[key];

    int counter = 0;
    while(aux_node != NULL && aux_node->val != NULL && aux_node->val[0] == e[0]){
        
        if (!strcmp(aux_node->val, e)){
            printf("%d\n",counter);
            return;
        }

        aux_node = aux_node->next;
        counter++;
    }

    printf("Palavra nao existe na lista.\n");
    
    return;
}

/*
int SearchRemoveElem(List *list, elem *e, elem *dest_e){

    if(IsEmptyList(list)) return 1;

    Node *dest_node;
    int error = 0;
    int index = 0;

//    dest_node = SearchElemList(list, *e, &error, &index);
    switch (error){
        case 1: 
            return 1;
        case 2:
            printf("Element not found!\n");
//            free(dest_node);
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
*/

int IndexRemoveElem(List *list, elem *e, int index){

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

int RemoveMiddleElem(Node *node, elem *e){

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

int TestPrint(Node **array_letters, int i){

    if (array_letters[i]->val != NULL){
        printf("TestPrint: address arr : %p\n",array_letters[i]);
        printf("%s\n",array_letters[i]->val);
    }
    else printf("@ -1\n");

    return 0;
}

int PrintFirstThree(List *list){

    if(IsEmptyList(list)) return 1;
    
    Node *aux_node = list->first;
    
    int i=1;
    while(aux_node!=NULL && i <= 3){
        if (aux_node->val != NULL){
            printf("%s\n",aux_node->val);
            i++;
        }
        aux_node = aux_node->next;
    }

    return 0;
}

int PrintList(List *list, Node **array_letters){

    if(IsEmptyList(list)) return 1;
    
    Node *aux_node = list->first;
    
    int i = 97;
    while(aux_node!=NULL){
        if (aux_node->val != NULL){
//            printf("PrintList: address arr : %p %p ",array_letters[i-97], aux_node);
            printf("%s\n",aux_node->val);
        }
        else{
            printf("#%c %d\n",i, (i-97));
            i++;
        }
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
        free(aux_node->val);
        aux_node2 = aux_node;
        aux_node = aux_node->next;
        free(aux_node2);
    }
    free(aux_node);
    free(list);

    return 0;
}
