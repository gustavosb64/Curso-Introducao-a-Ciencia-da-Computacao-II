#include <stdio.h>
#include <stdlib.h>

int *gera_vetor(int n){

    int *v = (int *) malloc(n * sizeof(int));
    for (int i=0; i<n; i++)
        v[i] = rand()%100;

    return v;
}

// caso patologio = ordenado
int pivo_inicio(int i, int f) {
	return i; // retorna inicio
}

// caso patologico = ordenado até o centro e depois
//                   ordenado de forma invertida
int pivo_central(int i, int f) {
	return (int) ((i+f)/2.0); // retorna posicao central
}

// caso patologico = pivo aleatorio
// 		    é um valor proximo do min ou max
int pivo_aleatorio(int i, int f) {
	return (int)(rand()%(f-i))+i ; // retorna posicao aleatoria [i,f]
}

void quicksort(int *v, int ini, int fim){
    printf("asdf");

    //caso base
    if (ini >= fim) return;

    /* qualquer estratégia de escolha funciona desde que antes do código abaixo
     * sejam trocados o pivo com o que estiver no ini */

    int p = (int) (ini+fim)/(2.0);
    /*partição ao redor do pivot
    p = ini;
    int i = ini+1;
    int j = fim;
    */

    //trocar o pivot com a primeira posicao
    int tmp = v[p];
    v[p] = v[ini];
    v[ini] = tmp;

    p = ini;
    int i = ini+1;
    int j = fim;

    while(i <= j){

        while(i <= fim && v[i] <= v[p]) i++;
        while(v[i] > v[p]) j--;

        if (j > i){
            tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
        }

    }
    
    //posicionar o pivot na posicao correta
    tmp = v[p];
    v[p] = v[j];
    v[j] = tmp;
    p = j;

    //chamadas recursivas
    quicksort(v, ini, p-1);
    quicksort(v, p+1,fim);
    
    return;
}

void main(){

    int n = 10;
    int *v = gera_vetor(n);
    
    for (int i=0; i<n; i++){
        printf("%d ",v[i]);
    }
    printf("\n");

    quicksort(v, 0, n-1);

    for (int i=0; i<n; i++){
        printf("%d ",v[i]);
    }
    printf("\n");

    return;

}
