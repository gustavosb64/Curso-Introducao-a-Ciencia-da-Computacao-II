#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

/*
 * lin e col são os índices onde a checagem da matriz se iniciará.
 * n armazena quantos na linha e na coluna serão analisados.
 * Como a matriz é quadrada, apenas estes valores bastam.
*/
int areEqual(int **matrix, int lin, int col, int n){

    int elem = matrix[lin][col];

    for (int i = lin; i < lin+n; i++)
        for (int j = col; j < col+n; j++)
            if (matrix[i][j] != elem) return False;

    return True;
}

void pre_order_print(int **matrix, int lin, int col, int n){
    
    //checa se os valores no quadrante são iguais
    if(areEqual(matrix, lin, col, n)){
        printf("%d ",matrix[lin][col]);
        return;
    }

    //Caso não sejam iguais, imprime -1 e percorre seus subquadrantes recursivamente
    
    printf("-1 ");

    pre_order_print(matrix, lin, col, (int)(n/2));
    pre_order_print(matrix, lin, col+(int)(n/2), (int)(n/2));
    pre_order_print(matrix, lin+(int)(n/2), col, (int)(n/2));
    pre_order_print(matrix, lin+(int)(n/2), col+(int)(n/2), (int)(n/2));

    return;

}

int main(int argc, char *argv[]){

    int n;
    scanf(" %d %d", &n, &n); //como a matriz é quadrada, armazenei os valores em apenas uma variável

    int **matrix = (int **) malloc(n * sizeof(int*));
    for (int i=0; i<n; i++){
        matrix[i] = (int *) malloc(n * sizeof(int));
        for (int j=0; j<n; j++){
            scanf(" %d",&matrix[i][j]);
        }
    }

    pre_order_print(matrix, 0, 0, n);

    for(int i=0; i<n; i++){
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
