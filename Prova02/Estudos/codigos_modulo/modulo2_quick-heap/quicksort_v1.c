#include <stdio.h>

void quicksort(char* v, int ini, int fim) {

	// 1- caso base (vetores de tamanho 0 ou 1)
	if (fim <= ini) return;
	
	// 2- particao ao redor de um *pivo*
	// - seleciona um pivo [--- l1 ---] <= p < [--- l2 ---]
	// - percorre o inicio do vetor para garantir <= pivo
	// - percorre o fim do vetor para garantir > pivo

	// qualquer estrategia de escolha
	// desde de antes do codigo abaixo eu troque
	// o pivo selecionado com o que estiver no ini

	int p = ini;
	int i = ini+1; // percorre l1 <= p ++
	int j = fim;   // percorre l2 > p  --

	while (i <= j) {
		while (i < fim && v[i] <= v[p]) i++; 
		while (v[j] > v[p]) j--; // pivo demarca o inicio

		// i e j sao candidatos a troca
		if (j > i) {
			char tmp = v[i];
			v[i] = v[j];
			v[j] = tmp;
		}
	}
	// posicionar o vetor na sua posicao já ordenada
	// a posicao do pivo será a *j*
	p = j;
	char tmp = v[p];
	v[p] = v[ini];
	v[ini] = tmp;

	// 3- chamadas recursivas
	quicksort(v, ini, p-1);
	quicksort(v, p+1, fim);
}

int main (void) {

	char A[8] = {'E', 'Y', 'A', 'D', 'B', 'F', 'C', '\0'};

	printf("%s\n", A);
	
	quicksort(A, 0, 6);
	
	printf("%s\n", A);

	return 0;
}
