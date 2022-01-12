/* 
 *	Counting sort original
 *	Counting sort com registros <- 
 *
 *	* limitacoes:
 *		- natural para inteiros
 *		- faz mais sentido quando há repetição das chaves
 *		- faz mais sentido quando o intervalo das chaves (K): K <= N
 *
 *	O(k,n)
 *
 *
 *	Moacir A Ponti - 2021
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct rec {
	int chave;
	float valor;
	char letra;
} Registro;


void countingsort(int* v, int N) {
	// criar vetor auxiliar para fazer a contagem das chaves
	// realiza a contagem
	// percorre o vetor de contagem copiando para o vetor original

	// ex.
	// valores a ordenar (chaves): entre 0 e 6
	//
	//  0 1 2 3 4 5 6
	// [0,0,0,0,0,0,0]
	//
	// v = [6, 6, 0, 1, 2, 2, 0, 3, 0]
	//
	//  x x x x x x x
	//  0 1 2 3 4 5 6
	// [3,1,2,1,0,0,2]
	//
	//      x  x  x  x  x  x  x
	// v = [0, 0, 0, 1, 2, 2, 3, 6, 6]
	//
	// e se as chaves forem entre 100 e 108?
	//
	// 100               108
	//   0 1 2 3 4 5 6 7 8
	// [ 0,0,0,0,0,0,0,0,0]
	

	// aritmetica -a
	// atribuicao -b
	// comparacao -c


	// 0 - encontrar chaves min e max
	int max, min;
	max = min = v[0];
	for (int i=1; i < N; i++) {
		if (v[i] > max) max = v[i]; // c+b
		if (v[i] < min) min = v[i]; // c+b
	}
	// (2c+2b)N 

	// 1 - cria vetor de contagem
	int tam_c = max-min+1; // 108-100 = 8 +1 = 9
	int *C = (int*) calloc(tam_c, sizeof(int));
	// Kb 
	
	// 2 - conta a frequencia de cada chave
	for (int i = 0; i < N; i++) {
		int pos_chave = v[i]-min;  // a
		C[pos_chave]++;            // a
	}
	// 2aN

	// 3 - recria o vetor usando as frequencias
	// para cada chave no vetor de contagem
	int i = 0;
	for (int j = 0; j < tam_c; j++) {
		while (C[j] > 0) {    // c
			v[i] = j+min; // a
			C[j]--;       // a
			i++;          // a
		}
	}
	// (K+N)(c+3a)
	//
	// total = 2cN+2bN+Kb+2aN+cN+3aN+
	//       = 5aN + 2bN + 3cN + K3a + Kb + Kc
	//       = 10N + 5K

	// T(N,K) = 10N + 5K
	//
	// O(g(N))?
	//
	// é O(N+K)?
	//
	// 10N + 5K <= c(N+K)
	//
	//
	//  0 1 2 3 4 5 6 7 8
	// [0,0,2,1,0,0,2,0,1]
	//
	//                         i
	// v = [100, 100, 100, 101,
	
	free(C);
}


void countingsort_reg(Registro* v, int N){

	int max, min, i, j;

	// 0 - Encontrar maximo e minimo
	//     Fazer cópia do vetor original
	Registro *cop = (Registro *)malloc(N*sizeof(Registro));
	
	// no mesmo loop encontra min-max e faz copia
	max = min = v[0].chave;
	for (int i = 0; i < N; i++) {
		if (v[i].chave > max) max = v[i].chave;
		if (v[i].chave < min) min = v[i].chave;
		cop[i] = v[i];
	}

	// 1 - cria vetor de contagem
	int tam_c = max-min+1;
	int *C = (int*) calloc(tam_c, sizeof(int));
	// 2 - conta a frequencia de cada chave
	for (int i = 0; i < N; i++) {
		int pos_chave = v[i].chave-min;  // a
		C[pos_chave]++;            // a
	}

	// v
	// [(4, X); (1, A); (3, C); (4, C); (1, M)]
	//
	// C
	// chave= 1 2 3 4
	// pos  = 0 1 2 3 
	//       [2,0,1,2]
	//
	// contagem acumlada
	//       [0,2,2,3]

	// 3- percorre o vetor de contagem e produz uma contagem acumulada
	//    histograma de frequencia cumulativa (histograma cumulativo)
	int total = 0;
	for (j = 0; j< tam_c; j++) {
		int cont = C[j]; // atual
		C[j] = total; // todos anteriores
		total = total + cont; // acumula no total
	}

	// 4 - reposiciona os registros em sua posicao ordenada usando
	//     como base o histograma cumulativo
	//        0 1 2 3
	//        1 2 3 4 <- chaves
	//    C =[2,2,3,5]
	//
	//        0       1       2       3       4
	//   v = [(1, A); (1, M); (3, C); (4, X); (4, C)]
	//
	// cop = [(4, X); (1, A); (3, C); (4, C); (1, M)]
	//          x      x      x       x        x
	for (i = 0; i < N; i++) {
		// acha a posicao correta do registro i
		int pos = C[cop[i].chave-min];
	
		// copiar para o vetor original
		v[pos] = cop[i];

		// incrementa o histograma cumulativo
		// para que a proxima posicao da chave encontrada
		// nao sobreponha a atual
		C[cop[i].chave-min]++;
	}

	free(cop);
	free(C);
}

void countingsort_reg_letra(Registro* v, int N){

	int max, min, i, j;

	// 0 - Encontrar maximo e minimo
	//     Fazer cópia do vetor original
	Registro *cop = (Registro *)malloc(N*sizeof(Registro));
	
	// no mesmo loop encontra min-max e faz copia
	max = min = (int)v[0].letra;
	for (int i = 0; i < N; i++) {
		if ((int)v[i].letra > max) max = (int)v[i].letra;
		if ((int)v[i].letra < min) min = (int)v[i].letra;
		cop[i] = v[i];
	}

	// 1 - cria vetor de contagem
	int tam_c = max-min+1;
	int *C = (int*) calloc(tam_c, sizeof(int));
	// 2 - conta a frequencia de cada chave
	for (int i = 0; i < N; i++) {
		int pos_chave = ((int)v[i].letra)-min;  // a
		C[pos_chave]++;            // a
	}

	// v
	// [(4, X); (1, A); (3, C); (4, C); (1, M)]
	//
	// C
	// chave= 1 2 3 4
	// pos  = 0 1 2 3 
	//       [2,0,1,2]
	//
	// contagem acumlada
	//       [0,2,2,3]

	// 3- percorre o vetor de contagem e produz uma contagem acumulada
	//    histograma de frequencia cumulativa (histograma cumulativo)
	int total = 0;
	for (j = 0; j< tam_c; j++) {
		int cont = C[j]; // atual
		C[j] = total; // todos anteriores
		total = total + cont; // acumula no total
	}

	// 4 - reposiciona os registros em sua posicao ordenada usando
	//     como base o histograma cumulativo
	//        0 1 2 3
	//        1 2 3 4 <- chaves
	//    C =[2,2,3,5]
	//
	//        0       1       2       3       4
	//   v = [(1, A); (1, M); (3, C); (4, X); (4, C)]
	//
	// cop = [(4, X); (1, A); (3, C); (4, C); (1, M)]
	//          x      x      x       x        x
	for (i = 0; i < N; i++) {
		// acha a posicao correta do registro i
		int pos = C[((int)cop[i].letra)-min];
	
		// copiar para o vetor original
		v[pos] = cop[i];

		// incrementa o histograma cumulativo
		// para que a proxima posicao da chave encontrada
		// nao sobreponha a atual
		C[((int)cop[i].letra)-min]++;
	}

	free(cop);
	free(C);
}



int main (int argc, char* argv[]) {


	int N = atoi(argv[1]);
	int minc = atoi(argv[2]);

	int *v = (int*) malloc(sizeof(int)*N);
	int i = 0;
	printf("Vetor a ordenar: ");
	for (i = 0; i < N; i++) {
		if (i == 0) v[i] = N*10000;
		else v[i] = (rand()%(int)(N/3.0))+minc;
		printf("%d ", v[i]);
	}

	printf("\n");

	countingsort(v, N);

	printf("Ordenado: ");
	for (i = 0; i < N; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");

	Registro *r = (Registro *) malloc(sizeof(Registro)*N);
	for (i = 0; i < N; i++) {
		r[i].chave = (rand()%(int)(N/3.0))+minc;
		r[i].valor = (float)i+1;
		r[i].letra = (char)(rand()%(90-65+1))+65;
		printf("(%d; %.1f %c) ", r[i].chave, r[i].valor, r[i].letra);
	}
	printf("\n");

	countingsort_reg_letra(r, N);
	countingsort_reg(r, N);

	for (i = 0; i < N; i++) {
		printf("(%d; %.1f %c) ", r[i].chave, r[i].valor, r[i].letra);
	}
	printf("\n");

	free(r);
	free(v);
	return 0;

}
