#include <stdio.h>
#include <stdlib.h>

typedef struct reg {
	int key;
	float value;
	char *bla;
} Reg;

typedef struct node {
	Reg elem;
	struct node *next;
} Node;

typedef struct bucket {
	Node *begin;
	Node *end;
} Bucket; 

void bucketsort(Reg *v, int N) {
	int i;

	// 1- encontra a maior chave, considerando
	// que as chaves sao positivas
	int max = v[0].key;
	for (i = 1; i < N; i++) {
		if (v[i].key > max) max = v[i].key;
	}

	// 2- criar um vetor auxiliar contendo listas (buckets)
	//    cada bucket possui um ponteiro para o inicio e outro
	//    para o fim da lista
	Bucket *B = (Bucket *) calloc((max+1), sizeof(Bucket));	

	// 3 - preenche os buckets com as chaves do vetor
	//     de entrada
	for (i = 0; i < N; i++) {
		int key = v[i].key; // chave
		// cria novo no
		Node *newnode = malloc(sizeof(Node));
		newnode->elem = v[i];
		newnode->next = NULL;

		if (B[key].begin == NULL) {
			// fila esta vazia
			B[key].begin = newnode;
		} else {
			// fila nao vazia
			// ultimo elemento aponta para o novo no
			(B[key].end)->next = newnode;
		}
		// novo no passa a ser o ultimo elemento
		B[key].end = newnode;
	}

	// 4 - percorre cada bucket, removendo os elementos
	//     do inicio da fila e inserindo na posicao correta
	int j; // percorre buckets
	i = 0; // percorre vetor de entrada
	for (j = 0; j < max+1; j++) {
		// para cada bucket (fila)
		Node *pos;
		pos = B[j].begin;
		while (pos != NULL) {
			// copia elemento no inicio da lista
			v[i] = pos->elem;
			i++;
			// deleta o elemento e vai para o proximo
			Node *del = pos;
			pos = pos->next;
			B[j].begin = pos;
			free(del);
		}
	}
	free(B);
}

int main(int argc, char*argv[]) {

	Reg A[] = {{2,8.3,NULL}, {1,1.3,NULL}, {5, 9.9, NULL}, {0, 1.3, NULL}, {2, 10.3, NULL}};
 int N = 5;

	bucketsort(A, N);

	int i;
	for (i = 0; i < N; i++) {
		printf("(%d, %f) ", A[i].key, A[i].value);
	}
	printf("\n\n");

	return 0;
}
