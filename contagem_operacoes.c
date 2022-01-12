// A -> G
void algoritmo1(int *values, int N) {

    /*
     * a = aritméticas e atribuições
     * b = comparações e operações lógicas
    */
    int i, j = 0; // 1a
    int tmp;
    for (i = 0; i < N; i++){          // a + b ; (N-1)*a + (N-1)*b 

        for (j = 0; j < N; j++){       // a + b ; (N-1)*a + (N-1)*b 

            if (values[j] > values[j+1]){ // N^2 * (b + a)

                tmp = values[j+1];        // N^2 * (2 * a)
                values[j+1] = values[j];  // N^2 * (2 * a)
                values[j] = tmp;          // N^2 * a

            }
        }
    }         

    /*
     * 2*(a + b + (N-1)*a + (N-1)*b) + 2*(N^2 * (2 * a)) + N^2 * a + N^2 * (b + a)
     *  _________________________________________________
     * |                                                 |
     * | f(n) = N^2*(4a + b) + (N-1)*(2a + 2b) + 2*(a+b) |
     * |_________________________________________________|
    */
}

//* Se a primeira letra do seu nome é entre M e Z analise o algoritmo 3
char*** algoritmo3(int N) {

    /*
     * a = aritméticas e atribuições
     * b = comparações e operações lógicas
    */

    char*** c = malloc(N * sizeof(char**)); // 3a
    
    for (int i = 0; i < N; i++) { // a+c ; (N-1)*(a+c)

        c[i] = calloc(N, sizeof(char*)); // N*(N*a)

        for (int j = 0; j < N; j++) { // N * ( a+c ; (N-1)*(a+c) ) 
                 c[i][j] = (i+1)+j*2; // 4a
        }
    }

    /*
     * 3a + (a+c + (N-1)*(a+c)) + N*( a+c + (N-1)*(a+c) + a+c + (N-1)*(a+c) + N*( 4a ))
     * 3a + a + c + (N-1)*(a+c) + N(a+c) + N*(N-1)*(a+c) + N*a + N*c + N*(N-1)*(a+c) + N*N*4a
     *
     *
    */

    return c;
}
