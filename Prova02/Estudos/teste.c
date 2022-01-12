#include<stdio.h>

void teste(int n){
    int m = n;

    int i,j;
    for (i = n; i > 0; i = i/2){
        for (j = i; j < m; j++){

            //'a' operações
        }
    }

    while(m > 0){
        printf("%d\n",m);
        //'a' operações
        m = m*0.25;
    }
    printf("%d\n",m);

}


void teste_for(int n, int m, int i){

    if (i <= 0) return;

    for (int j = i; j < m; j++){
        //'a' operações
    }

    return teste_for(n, m, i/2);
}

void teste_while(int n, int m){

    if (m <= 0) return;

    //'a' operações

    return teste_while(n, m/4);
}

void teste_original(int n){
    int m = n;

    teste_for(n, m, n);
    teste_while(n, m);

    return;
}

void main(){

    int n = 10;
    teste(n);

    return;
}
