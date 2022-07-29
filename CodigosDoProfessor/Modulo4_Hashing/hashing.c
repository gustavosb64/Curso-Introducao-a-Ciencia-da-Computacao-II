#include "hashing.h" 

#/* cria tabela de tamanho m */
int* create_hash_table(int m) {
	int* t = malloc(sizeof(int)*m);
	for (int i = 0; i < m; i++) t[i] = FREE;
	return t;
}

void destroy_hash_table(int** t) {
	free(*t);
	*t = NULL;
}

int insert(int* t, int key, int m) {
	if (key < 0) return -1; // apenas chaves positivas

	double A = (sqrt(5)-1)/2.0;

	// posicao e numero de colisoes
	int pos, c = 0;

	// trata colisao com enderecamento aberto
	// por sondagem linear
	do {
		// calcula funcao hash
		//pos = hash_division(key, m, c);
		pos = hash_multi(key, m, c, A);

		// verifica se houve colisao
		if (t[pos] != FREE && t[pos] != DEL) {
			c++;
			printf("-colisao %d (%d)\n", c, t[pos]);
		}
	} while (t[pos] != FREE && t[pos] != DEL);

	// insere chave na posicao
	t[pos] = key;
}

/* busca elemento key na tabela t de tamanho m */
int search(int* t, int key, int m) {

	if (key < 0) return -1; // apenas chaves positivas

	double A = (sqrt(5)-1)/2.0;

	// numero de colisoes
	int c = 0;
	int pos;

	do {
		// calcula funcao hash
		//pos = hash_division(key, m, c);
		pos = hash_multi(key, m, c, A);

		// posicao esta livre, finaliza sem sucesso
		if (t[pos] == FREE) break;

		// houve colisao, incrementa contador
		if (t[pos] != key) c++;

		// buscou toda a tabela sem sucesso
		// se for verdadeiro, entao cai no caso O(m) / linear
		if (c >= m) break;

	} while (t[pos] != key);

	// verifica se a posicao possui a chave
	if (t[pos] == key) return pos;
	else return FREE;
}

/* exclui elemento key da tabela t de tamanho m */
int remove_hash(int* t, int key, int m) {
	int pos = search(t, key, m);
	if (pos < 0) return pos;
	t[pos] = DEL;
	return 1;
}

void print_table(int*t, int m) {
	for (int i = 0; i < m; i++) {
		printf("%d ", t[i]);
	}
	printf("\n");
}

int hash_division(int key, int m, int c) {
	return (int)((key+c)%m);
}

int hash_multi(int key, int m, int c, double A) {
	double val = (key+c)*A;
	val = val - ((int)val);
	return (int)(val*m);
}

