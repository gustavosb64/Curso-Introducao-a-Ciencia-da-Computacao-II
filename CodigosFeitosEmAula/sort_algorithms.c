#include <stdio.h>
#include <stdlib.h>

int* insertion_sort(int *V, int size){
    int key, i;

    for (int j=1; j<size; j++){
        key = V[j];

        for (i = j-1; i >=0 && V[i] > key; i--)
            V[i+1] = V[i];

        V[i+1] = key;
    }

    return V;
}

int* merge(int *v, int left, int middle, int right){

    int *aux_v = (int *) malloc( (right+1) * sizeof(int));

    int k=0, i=0, j=middle+1;
    while(i <= middle && j <= right){

        if (v[i] < v[j]){
            aux_v[k] = v[i++];
        }
        else{
            aux_v[k] = v[j++];
        }

        k++;
    }

    /*
    printf("k: %d\ti: %d\t j: %d\n",k,i,j);
    printf("l: %d\tm: %d\tr: %d\n",left,middle,right);
    printf("\n");
    */

    while(i <= middle){
        aux_v[k++] = v[i++];
    }
    while(j <= right){
        aux_v[k++] = v[j++];
    }

    return aux_v;

}

int* merge_sort(int *v, int left, int right){
    
    if (left < right){

        int middle;

        middle = (int) ( (right - left)/2 ) + left;
    
        //calling merge_sort() for left block then for right block 
        merge_sort(v, left, middle); 
        merge_sort(v, middle+1, right); 

        return merge(v, left, middle, right);
    }

}

//caso patológico: ordenado
int pivot_inicio(int ini, int fim){
    return ini;
}

//caso patológico: ordenado até o centro, inversamente ordenado depois
//caso ótimo: totalmente ordenado
int pivot_central(int ini, int fim){
    return (int) (ini+fim)/2;
}

//caso patológico: pivot aleatório é um valor próximo do min ou max
int pivot_aleatorio(int ini, int fim){
    return (int)(rand()%(fim-ini))+ini;
}

/*
int pivo_medianade3(int i, int f, int* v){

    int c = (int) (ini+fim)/2;
    int pos[3] = {i, c, f};
    int l[3] = {v[i], v[f], v[c]};

    insertion_sort(l, 3);

    for (p=0; p<2; p++)
        if (v[1] == v[pos[p]]) break;

    return pos[p];
}
*/

//quicksort é inplace, ou seja, não usa memória auxiliar, como o mergesort
//outra coisa que faz do quicksort melhor que o mergesort, é o fato de que ele
//não realiza exatamente n/2 operações a cada passagem, mas (n-1)/2
void quicksort(char *v, int ini, int fim, int (*eep)()){

    //caso base
    if (fim <= ini) return;

    /* qualquer estratégia de escolha funciona desde que antes do código abaixo
     * sejam trocados o pivo com o que estiver no ini */

    int p;
    /*partição ao redor do pivot
    p = ini;
    int i = ini+1;
    int j = fim;
    */

    p = eep(ini, fim);

    //trocar o pivot com a primeira posicao
    int tmp = p;
    v[p] = v[ini];
    v[ini] = tmp;

    p = ini;
    int i = ini+1;
    int j = fim;

    while(i <= j){

        while(i < fim && v[i] <= v[p]) i++;
        while(v[i] > v[p]) j--;

        if (j > i){
            char tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
        }

    }
    
    //posicionar o pivot na posicao correta
    p = j;
    char tmp = v[p];
    v[p] = v[ini];
    v[ini] = tmp;

    //chamadas recursivas
    quicksort(v, ini, p-1);
    quicksort(v, p+1,fim);
    
    return;

}

int main(){

    //TESTING INSERTION_SORT()
    int *v = (int *) malloc(6 * sizeof(int));

    v[0] = 2;
    v[1] = 7;
    v[2] = 20;
    v[3] = 13;
    v[4] = 9;
    v[5] = 16;

    for (int i=0; i<6; i++){
        printf("%d ",v[i]);
    }
    printf("\n");
    /*

    v = insertion_sort(v, 5);

    for (int i=0; i<5; i++){
        printf("%d ",v[i]);
    }
    printf("\n");
    */

    //TESTING MERGE_SORT()
    int *aux_v = merge_sort(v, 0, 5); 

//    int *aux_v = merge(v, 0, 1, 3);

    for (int i=0; i<6; i++){
        printf("%d ",aux_v[i]);
    }
    printf("\n");
    /*
    */

    return 0;
}
