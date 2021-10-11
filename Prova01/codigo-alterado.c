/*
 * Aluno: Gustavo Siqueira Barbosa
 * Número USP: 10728122
*/

#include <stdio.h>
#include <stdlib.h>

void imprimeVetor(int* vetor, int tamanho){
	int i;
	printf("Vetor: ");
	for (i=0; i<tamanho; i++) printf("%i ", vetor[i]);
	printf("\n");
}

int** alloc_matrix(int m) {
	int **mat = malloc(sizeof(int*)*m);
	srand(m);
	
	int in = 0;
	// aloca matriz ordenada
	for (int i = 0; i < m; i++) {
		mat[i] = malloc(sizeof(int)*m);
	    	for (int j = 0; j < m; j++) {
			if (i == j) in+= (rand()%3)+1;
			else in += rand()%3;
			mat[i][j] = in;
		}
	}
	// desordena matriz triangular superior
	for (int i = 0; i < m-2; i++) {
	    	for (int j = i+1; j < m-1; j++) {
			int swaps = (int)((m-j)/2.0)+1;
			for (int t = 1; t <= swaps; t++) {
				int a = (rand()%(m-j))+j;
				int b = (rand()%(m-j))+j;
				int tmp = mat[i][a];
				mat[i][a] = mat[i][b];
				mat[i][b] = tmp;
			}
		}

	}
	return mat;
}

//Como a matriz encontra-se parcialmente ordenada, preferi utilizar um insertion sort
//Passei a matriz diretamente. Mandei como parâmetro a linha em questão, que se mantém fixa
//durante a execução de cada chamada do insertion_sort.
int** insertion_sort(int **V, int size, int start, int line){
    int key, i;

    //o inicio do vetor (start) é alterado a cada chamada da função
    for (int j=start+1; j<size; j++){
        key = V[line][j];

        for (i = j-1; i >=start && V[line][i] > key; i--)
            V[line][i+1] = V[line][i];

        V[line][i+1] = key;
    }

    return V;
}

int main (int argc, char* argv[]){
	int m;
	scanf("%d", &m);
	
	int** matriz = alloc_matrix(m);
	
	int i, j;

    //Colocando o j = i, diminui-se a complexidade para a metade.
	for (i=0; i<m; i++)
		for (j=i; j<m; j++)
			matriz = insertion_sort(matriz, m, j, i);			

	for (i=0; i<m; i++){
		for (j=0; j<m; j++){
			printf("%i ", matriz[i][j]);
		}
		printf("\n");
	}

	free(matriz);

	return 0;
}
