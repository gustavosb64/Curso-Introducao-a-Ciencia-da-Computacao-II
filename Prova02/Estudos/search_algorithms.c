#include<stdio.h>
#include<stdlib.h>

#define FAIL -404

/* 
 * c - comparacoes 
 * b - chamada da funcao 
 * a - aritmeticas
*/


//Function for an ITERATIVE sequential search
int sequential_search_iterative(int *v, int key, int N){

    for(int i=0; i<N; i++)
        if (v[i] == key) return i;
    
    return FAIL;
}

//Function for a RECURSIVE sequential search (NOT RECOMMENDED)
int sequential_search_recursive(int *v, int key, int N, int i){

    /* 1 - caso base 
     *   1.1 fim do vetor
     *   1.2 encontrar a chave */
    if (i >= N) return FAIL;    //c ( f(0) )     
    if (v[i] == key) return i;  //c 

    // 2 - passo recursivo
    return sequential_search_recursive(v, key, N, i+1); //a+b

    //TOTAL: f(N) = N*(2c + a + b) + f(0)
    //       f(N) = N*(2c + a + b) + c

}

//Function for a ITERATIVE binary search
int binary_search_iterative(int *v, int key, int start, int end){
    //0 - caso base (sem sucesso)

    while (start <= end){
        int c = (int) ( (start + end) / (2.0));

        if (v[c] == key) return c;

        if (key < v[c]) end = c-1;

        if (key > v[c]) start = c+1;
    }

    return FAIL;

}

//Function for a RECURSIVE binary search (NOT RECOMMENDED)
int binary_search_recursive(int *v, int key, int start, int end){

    if (start > end) return FAIL; //c

    int c = (int) ( (start + end) / (2.0)); // 2a
    
    if (v[c] == key) return c;  //c
    
    if (k < v[c]) //c
        return binary_search_recursive(v, key, start, c-1); //b + a

    if (k > v[c]) //c
        return binary_search_recursive(v, key, c+1, end);   //b + a

    /*
     * PIOR CASO:
     *  f(N) = c + 2a + c + c + c + b+a + f(N/2)
     *  f(N) = 3a + b + 4c + f(N/2)
     * CASO(s) BASE(s):
     *  f(0) = c
     *  Como não dá para trabalhar com o f(0) nesse caso, podemos usar de 
     *  caso base o:
     *
     *    f(1) = 3a + b + 5c
     *
     * FORMA FECHADA:
     *  F(N) = 3a + b + 4c + f(N/2) = 3a + b + 4c + 3a + b + 4c + f(N/4) + ...
     *  F(N) = k(3a + b + 4c) + f(N/2^k)
     *    Usando f(1) como caso base:
     *      (N/2^k) = 1 ==> k = log2(N)
     *
     *  F(N) = log2(N)*(3a + b + c) + f(1)
     *  F(N) = log2(N)*(3a + b + c) + 3a + b + 5c
     *  OBS: Pode não aparecer exatamente como o acima. O importante é haver o log2(N)
    */
}
