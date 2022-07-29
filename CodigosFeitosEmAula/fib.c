#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int fib_rec(int n){

    if (n == 1) return 1;
    if (n == 0) return 0;

    return fib_rec(n-1) + fib_rec(n-2);
}

long long int fib_it(int n){

    long long int F = 0;
    long long int Ft = 1;

    for (int i=2; i <= n; i++){
        F += Ft;
        Ft = F - Ft;
    }

    return F;

}

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);

    clock_t start = clock();
    long long int res_it = fib_it(n);
    clock_t end = clock();
    printf("\nfib_it: %ld\ttime: %lf sec\n", res_it, (double)(end - start)/CLOCKS_PER_SEC);

    start = clock();
    long long int res_rec = fib_rec(n);
    end = clock();
    printf("fib_rec: %ld\ttime: %lf sec\n", res_rec, (double)(end - start)/CLOCKS_PER_SEC);

    return 0;
}
