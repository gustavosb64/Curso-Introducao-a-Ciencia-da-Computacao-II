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

List* CreateList(){
    List *list = (List *) malloc(sizeof(List)); 
    if (list == NULL){
        printf("CreateList FAILED: Memory is full.\n");
        return NULL;
    }
    
    list->first = NULL; 
    list->last = list->first; 
    list->n_elem = 0; 

    /* A lista não se inicia vazia. Armazena 26 nós como separadores de cada uma 
     * das 26 letras do alfabeto, sendo que cada nó possui val apontando para NULL*/
    for(int i=0; i<26; i++)
        AddLastElem(list, NULL);

    return list;
}

Node** CreateArrayNode(List *list){

    //O vetor de índices armazena ponteiros para cada uma das palavras de cada letra
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

int UpdateArrayNode(List *list, Node **array_letters){

    int counter = 0; //conta quantas seções do alfabeto diferentes foram utilizadas
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

    //Caso ref_node->val == NULL, então a letra não foi preenchida ainda
    //Desta forma, o novo elemento é colocado logo após ref_node
    if ((ref_node)->val == NULL){

        node->next = ref_node->next;
        node->prev = ref_node;
        ref_node->next = node;
        ref_node = node;

        list->n_elem++;

        return 0;
    }

    //Caso o nó anterior ao ref_node não tenha val == NULL, é porque ainda
    //não se alcançou a última posição da lista referente à letra em questão
    while (ref_node->prev->val != NULL)
        ref_node = ref_node->prev;

    node->next = ref_node;
    node->prev = ref_node->prev;
    ref_node->prev->next = node;
    ref_node->prev = node;

    list->n_elem++;

    return 0;
}

int IsArrayUpToDate(Node **array_letters){

    for (int i=1; i<26; i++){

        //Se o array_letters[i] apontar para o marcador enquanto há elementos na letra,
        //o vetor não está atualizado
        if (array_letters[i]->val == NULL){
            if (array_letters[i]->next != NULL && array_letters[i]->next->val != NULL)
                return 0;
        }
        else{ 
            //Se o array_letters[i] não apontar para o primeiro elemento da respectiva
            //letra, o vetor não está atualizado
            if (array_letters[i]->prev->val != NULL)
                return 0;
            
        }

    }

    return 1;
}

void SearchElemList(List *list, Node **array_letters, elem e){

    //Caso list->n_elem <= 26, não há elementos além dos marcadores de seção
    if(list->n_elem <= 26 || !IsArrayUpToDate(array_letters)){
        printf("Vetor de indices nao atualizado.\n");
        return;
    }

    int key = e[0]-97; //refere-se ao índice do vetor referente à primeira letra de e
    Node *aux_node = array_letters[key];

    int counter = 0; //conta quantas palavras foram analisadas até encontrar elemento e
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
