#include <stdio.h>
#include <stdlib.h>

int funcao(int x) {
    int primo = 1;
    int soma = 0;
    for (int y = x-1; y > 1; y--) {
        if (x % y == 0) {
            primo = 0;
        }
        for (int a = 0; a <= 10000; a++) {
            if (a % y == 0) soma+= a;
        }
    }
    return primo;
}

for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    int p = funcao(x);
    if (p == 1) printf("%d Primo\n", x);
    else printf("%d Nao primo\n", x);
}

/*
 * for (int y = x-1; y > 1; y--) {
 * int soma = 0;
*/
// funcao(n, n-1, 1, 0)
int funcao(int x, int y, int primo, int soma) {

    if (y <= 1) return primo;

    if (x % y == 0) {
        primo = 0;
    }
    for (int a = 0; a <= 10000; a++) {
        if (a % y == 0) soma+= a;
    }

    return funcao(x, y-1, primo, soma);
}

/*
 * for (int i = 0; i < n; i++) {
*/
void func(n, i){

    if (i >= n) return; //c
    
    scanf("%d", &x);    //a
    int p = funcao(x);  //a
    if (p == 1) printf("%d Primo\n", x); //c
    else printf("%d Nao primo\n", x);

    func(n, i+1);
}

