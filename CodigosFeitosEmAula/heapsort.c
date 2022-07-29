#include <stdio.h>
#include <stdlib.h>

#define FAIL -1
#define DEBUG 0

void heapsort(int *v, int N){

    if (N < 1) return;

    build_maxheap(v, N);
    
    while (N >= 2){
        int maior = v[1];

        v[1] = v[N];
        v[N] = maior;

        max_heapify(v, 1, --N);
    }

    return;
}

//garantir que um nó esteja em condição de heap
void max_heapify(int *v, int p, int N){

    //comecando em um nó p
    int f = p*2;

    //se f > N, então o nó é uma folha
    if (f > N) return;

    //verifica condicao de maxheap com relacao aos filhos
    if (v[f] > v[p] || (f+1 <= N && v[f+1] > v[p]) ){

        if( (f+1 <= N) && v[f+1] > v[f] )
            f = f+1;

        int tmp = v[p];
        v[p] = v[f];
        v[f] = tmp;

        max_heapify(v, f, N);
    }


}

void build_maxheap(int *v, int N){

    int m = (int) n/2;
    for (int p = m; p >= 1; p--){
        max_heapify(v, p, N);
    }

    return;
}

int main(int argc, char *argv[]){


    return 0;
}
