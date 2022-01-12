#include <stdio.h>
#include <stdlib.h>

int *gera_vetor(int n){

    int *v = (int *) malloc(n * sizeof(int));
    for (int i=0; i<n; i++)
        v[i] = rand()%100;

    return v;
}

void imprime_vetor(int *v,int n){

    for (int i=0; i<n; i++){
        printf("%d ",v[i]);
    }
    printf("\n");

    return;
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

void quicksort(int *v, int ini, int fim, int (*eep)()){

    //caso base
    if (ini >= fim) return;

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
    int tmp = v[p];
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
    tmp = v[p];
    v[p] = v[j];
    v[j] = tmp;
    p = j;

    //chamadas recursivas
    quicksort(v, ini, p-1, eep);
    quicksort(v, p+1,fim, eep);
    
    return;
}

int main (int argc, char* argv[]) {

	if (argc < 2) {
		printf("Informe tamanho do vetor\n");
		return 1;
	}
	int n = atoi(argv[1]);

	int* vet = gera_vetor(n);
	if (n <= 20) imprime_vetor(vet, n);
	printf("Quicksort...\n");	
	quicksort(vet, 0, n-1, pivo_aleatorio);
	if (n <= 20) imprime_vetor(vet, n);

	free(vet);

	vet = gera_vetor(n);
	if (n <= 20) imprime_vetor(vet, n);
	
	printf("Mergesort...\n");	
//	mergesort(vet, 0, n-1);
	if (n <= 20) imprime_vetor(vet, n);

/*	printf("Tempo de execução:\n");
	printf("Quicksort = %lf s.\n", qs_time);
	printf("Mergesort = %lf s.\n", ms_time);
*/


	return 0;
}
