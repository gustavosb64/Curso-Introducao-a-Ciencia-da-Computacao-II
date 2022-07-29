#include <stdio.h>
#include <stdlib.h>

//stores the number in num and its respective quantity in the list
typedef struct node{
    int num;
    int quantity;
    struct node *next;
}Node;

typedef struct numList{
    Node *first;
}NumList;

Node* CreateNewNode(int num){
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->num = num;
    new_node->quantity = 1;
    new_node->next = NULL;

    return new_node;
}

void AddNum(NumList **number_list, int num){

    //in case number_list has not been initialized yet
    if ((*number_list) == NULL){

        (*number_list) = (NumList *) malloc(sizeof(NumList));
        Node *new_node = CreateNewNode(num);
        (*number_list)->first = new_node;

        return;
    }

    //checks number_list->first before the loop, so aux_node can be used after new_node is created if needed
    Node *aux_node = (*number_list)->first;

    if (aux_node->num == num){
        aux_node->quantity++;
        return;
    }  
    while(aux_node->next != NULL){
        aux_node = aux_node->next; 

        //if num is already in the list, its quantity is incremented
        if (aux_node->num == num){
            aux_node->quantity++;
            return;
        }  
    }

    //if num is not in the list yet, new_node is created and added to the end of the list
    Node *new_node = CreateNewNode(num);
    aux_node->next = new_node;

    return;
}

void PrintNumList(NumList *number_list){

    Node *aux_node = number_list->first;

    while(aux_node != NULL){
        printf("%d (%d)\n",aux_node->num, aux_node->quantity);
        aux_node = aux_node->next;
    }

    return;
}

void FreeNumList(NumList *number_list){

    Node *aux_node = number_list->first;
    Node *next_node = NULL;

    while(aux_node != NULL){
        next_node = aux_node->next;
        free(aux_node);
        aux_node = next_node;
    }

    free(number_list);

    return;
}

int main (int argc, char *argv[]){

    int num;
    NumList *number_list = NULL;

    while(!feof(stdin)){
        scanf(" %d", &num);
        AddNum(&number_list, num);
    }

    PrintNumList(number_list);
    FreeNumList(number_list);

    return 0;
}
