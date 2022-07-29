
//Como a matriz encontra-se parcialmente ordenada, preferi utilizar um insertion sort
int** insertion_sort(int **V, int size, int start, int line){
    int key, i;

    for (int j = start+1; j<size; j++){
        key = V[line][j];

        //Como dentro deste for há uma comparação além da utilizada para manter o laço, decidi contar uma comparação nesta linha
        for (i = j-1; i >=start && V[line][i] > key; i--) // c * (size-start+1) = c * (m-start+1)
            V[line][i+1] = V[line][i]; //(m-start+1) * (j 

        V[line][i+1] = key; // (size - (start+1)) * a
    }

    func1(V, size, start, line, j){

        if (j >= size) return V; //comparação não contada por ser pertencente ao for

        //Como dentro deste for há uma comparação além da utilizada para manter o 
        // laço, decidi contar uma comparação nesta linha
        for (int i = j-1; i >=start && V[line][i] > key; i--) //c
        

        for (int i = j-1; i >=start; i++)
            V[line][i+1] = V[line][i];  // (i-start+1)*a = (j-start)*a

        V[line][i+1] = key; // a

        return func1(V, size, start, line, j+1);

    }

    return V;
}



int main (int argc, char* argv[]){

	int i, j;

    //Como apenas metade do vetor é analisada, a operação foi reduzida para (m^2)/2
	for (i=0; i<m; i++)
		for (j=i; j<m; j++)
			matriz = insertion_sort(matriz, m, j, i); //(m^2 / 2) chamadas de insertion_sort

	for (i=0; i<m; i++){
		for (j=0; j<m; j++){
			printf("%i ", matriz[i][j]);
		}
		printf("\n");
	}

	return 0;
}
