#include <stdio.h>

void main(){

    int n = 30;
    int i=0;
    while (n > 0){
        printf("%d %d\n",n,i++);
        n = n/4;
    }

    printf("%d\n", 8/4);
    printf("%d\n", 7/4);
    printf("%d\n", 6/4);
    printf("%d\n", 5/4);
    printf("%d\n", 4/4);
    printf("%d\n", 3/4);
    printf("%d\n", 2/4);
    printf("%d\n", 1/4);

    return;
}
