#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"

struct process{
    int p;
    int t0;
    int tf;
    int r;
};

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

void ReadAllProcesses(List *ProcList){

    int p, t0, tf, r;

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

        //Os processos lidos são armazenados ordenados por tempo de entrada
        AddOrderedByTime(ProcList, process);

    }while(!feof(stdin)); 

    return;
}

int NewProcessess(List *ProcList, List **M_ProcList, Node **node_procList, int counter, int *cur_max_r){

    if ((*node_procList) == NULL || (*node_procList)->val.t0 != counter)
        return 0;

    Process aux_proc;
    while((*node_procList) != NULL && (*node_procList)->val.t0 == counter){

        if ((*cur_max_r) < (*node_procList)->val.r - 1){
            (*cur_max_r) = (*node_procList)->val.r - 1;
        }

        (*node_procList) = (*node_procList)->next;

        //Os processos são removidos da lista original e armazenados na respectiva
        //lista de prioridade, ordenados pelo ID
        RemoveFirstElem(ProcList, &aux_proc); 
        AddOrderedById(M_ProcList[aux_proc.r - 1], aux_proc);
    }

    return 1;
}

void EscalonarProcessos(List *ProcList){

    //São utilizadas 4 listas, cada uma referente a uma prioridade, armazenadas em uma matriz
    List **M_ProcList = (List **) malloc(4 * sizeof(List**));
    for (int i=0; i < 4; i++)
        M_ProcList[i] = CreateList();

    Node *node_procList = ProcList->first; //nó utilizado para percorrer a lista de processos original

    int change_check = 0; //sinaliza quando se deve apontar para prioridade maior após nova entrada
    int del_check = 0;    //sinaliza quando um nó deve ser deletado após as operações necessárias

    int cur_r = 3;          //armazena o nível de prioridade atual
    int cur_max_r = cur_r;  //armazena o maior nível de prioridade das entradas em determinado tempo

    int counter = 1;

    //Iniciando listas de M_ProcList com os valores de entrada no tempo 1
    NewProcessess(ProcList, M_ProcList, &node_procList, counter, &cur_max_r);

    Node *cur_pointer = M_ProcList[3]->first; //ponteiro utilizado para percorrer as 4 listas durante o escalonamento
    Node *aux_pointer;                        //ponteiro auxiliar

    while(!IsEmptyList(ProcList) ||
            !IsEmptyList(M_ProcList[0]) ||
            !IsEmptyList(M_ProcList[1]) ||
            !IsEmptyList(M_ProcList[2]) ||
            !IsEmptyList(M_ProcList[3]) )
    { 

        //Caso o ponteiro atual seja nulo, significa que a lista de 
        //prioridade está vazia. Ir para prioridade mais baixa
        while (cur_pointer == NULL){

            if ( (--cur_r) < 0) cur_r = 3;

            cur_pointer = M_ProcList[cur_r]->first;
        }

        //Muda para prioridade superior caso precise com nova entrada
        if (change_check == 1 && cur_max_r > cur_r ){
            cur_pointer = M_ProcList[cur_max_r]->first;
            cur_r = cur_max_r;
        }

        //Ao terminar de executar, del_check é marcado e o processo é deletado da lista posteriormente
        cur_pointer->val.tf -= 1;
        if (cur_pointer->val.tf == 0){
            printf("%d %d\n", cur_pointer->val.p, counter); 
            del_check = 1;
            aux_pointer = cur_pointer;  //armazena o cur_pointer para deletá-lo 
        }

        counter++;

        //Checa se há entradas com t0 iguais ao tempo atual
        cur_max_r = 0;
        if (NewProcessess(ProcList, M_ProcList, &node_procList, counter, &cur_max_r))
            change_check = 1;
        else
            change_check = 0;
        
        cur_pointer = cur_pointer->next;

        //Deleta o nó em aux_pointer, caso necessário
        if (del_check == 1){
            RemoveMiddleElem(M_ProcList[cur_r], aux_pointer);
            del_check = 0;
        }
        
    }

    //Libera memória das listas de processos
    for(int i=0; i<4; i++)
        FreeList(M_ProcList[i]);
    free(M_ProcList);

    return;
}

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

int RemoveMiddleElem(List *list, Node *node){

    if(list == NULL || node == NULL) return 1;

    Process aux_proc;

    if (node->prev == NULL){
        RemoveFirstElem(list, &aux_proc);
        return 0;
    }
    if (node->next == NULL){
        RemoveLastElem(list, &aux_proc);
        return 0;
    }

    node->prev->next = node->next;    
    node->next->prev = node->prev;
    
    node->next = NULL;
    node->prev = NULL;

    free(node); 

    list->n_elem--;

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
