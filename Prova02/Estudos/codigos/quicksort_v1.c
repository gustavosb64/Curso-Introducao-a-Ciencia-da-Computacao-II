#include <stdio.h>

void quicksort(char* v, int ini, int fim) {

	if (fim <= ini) return;
	
	int p = ini;
	int i = ini+1; 
	int j = fim;   

	while (i <= j) {
		while (i < fim && v[i] <= v[p]) i++; 
		while (v[j] > v[p]) j--; 

		if (j > i) {
			char tmp = v[i];
			v[i] = v[j];
			v[j] = tmp;
		}
	}

	p = j;
	char tmp = v[p];
	v[p] = v[ini];
	v[ini] = tmp;

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
