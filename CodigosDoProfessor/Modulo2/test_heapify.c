#include <stdio.h>
#include <stdlib.h>
#include "busca_e_ordenacao.h"

int main (int argc, char* argv[]) {

	if (argc < 2) {
		printf("Informe tamanho do vetor\n");
		return 1;
	}
	int n = atoi(argv[1]);

	int* vet = gera_vetor(n, 1, (int)(n*3));
	vet[0] = -1;
	if (n <= 20) imprime_vetor(vet, n+1);
	printf("Build Maxheap...\n");	
	// primeira posicao é ignorada
	build_maxheap(vet, n-1);
	if (n <= 20) imprime_vetor(vet, n);

	free(vet);

	return 0;
}
