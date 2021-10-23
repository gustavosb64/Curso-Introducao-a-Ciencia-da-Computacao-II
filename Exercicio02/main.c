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

    for (int i = lin; i < lin+n; i++){
        for (int j = col; j < col+n; j++){
            if (matrix[i][j] != elem) return False;
        }
    }

    return True;
}

void pre_order_print(int **matrix, int lin, int col, int n){
    
//    printf("lin: %d col: %d n: %d\n",lin,col,n);
    
    if(areEqual(matrix, lin, col, n)){
        printf("%d ",matrix[lin][col]);
        return;
    }

    printf("-1 ");

    pre_order_print(matrix, lin, col, (int)(n/2));
    pre_order_print(matrix, lin, col+(int)(n/2), (int)(n/2));
    pre_order_print(matrix, lin+(int)(n/2), col, (int)(n/2));
    pre_order_print(matrix, lin+(int)(n/2), col+(int)(n/2), (int)(n/2));

    return;

}

int main(int argc, char *argv[]){

    int n;
    scanf(" %d ", &n);
    getc(stdin); //como a matriz sempre é quadrada neste problema, não li o segundo valor

//    printf("%d\n",n);

    int **matrix = (int **) malloc(n * sizeof(int*));
    for (int i=0; i<n; i++){
        matrix[i] = (int *) malloc(n * sizeof(int));
        for (int j=0; j<n; j++){
            scanf(" %d",&matrix[i][j]);
        }
    }

    /*
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    */

    pre_order_print(matrix, 0, 0, n);

/*
    printf("%d\n",areEqual(matrix, 0, 0, n));

    printf("%d\n",areEqual(matrix, 0, 0, n/2));
    printf("%d\n",areEqual(matrix, 0,(n/2), n/2));
    printf("%d\n",areEqual(matrix, (n/2), 0, n/2));
    printf("%d\n",areEqual(matrix, (n/2), (n/2), n/2));

    printf("%d\n",areEqual(matrix, 0, 0, n/4));
    printf("%d\n",areEqual(matrix, 0,(n/4), n/4));
    printf("%d\n",areEqual(matrix, (n/4), 0, n/4));
    printf("%d\n",areEqual(matrix, (n/4), (n/4), n/4));
*/

    for(int i=0; i<n; i++){
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
