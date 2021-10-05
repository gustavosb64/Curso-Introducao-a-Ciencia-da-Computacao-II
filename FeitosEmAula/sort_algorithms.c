#include <stdio.h>
#include <stdlib.h>

int* insertion_sort(int *V, int size){
    int key, i;

    for (int j=1; j<size; j++){
        key = V[j];

        for (i = j-1; i >=0 && V[i] > key; i--)
            V[i+1] = V[i];

        V[i+1] = key;
    }

    return V;
}

int* merge(int *v, int left, int middle, int right){

    int *aux_v = (int *) malloc( (right+1) * sizeof(int));

    int k=0, i=0, j=middle+1;
    while(i <= middle && j <= right){

        if (v[i] < v[j]){
            aux_v[k] = v[i++];
        }
        else{
            aux_v[k] = v[j++];
        }

        k++;
    }

    /*
    printf("k: %d\ti: %d\t j: %d\n",k,i,j);
    printf("l: %d\tm: %d\tr: %d\n",left,middle,right);
    printf("\n");
    */

    while(i <= middle){
        aux_v[k++] = v[i++];
    }
    while(j <= right){
        aux_v[k++] = v[j++];
    }

    return aux_v;

}

int* merge_sort(int *v, int left, int right){
    
    if (left < right){

        int middle;

        middle = (int) ( (right - left)/2 ) + left;
    
        //calling merge_sort() for left block then for right block 
        merge_sort(v, left, middle); 
        merge_sort(v, middle+1, right); 

        return merge(v, left, middle, right);
    }

}

int main(){

    //TESTING INSERTION_SORT()
    int *v = (int *) malloc(6 * sizeof(int));

    v[0] = 2;
    v[1] = 7;
    v[2] = 20;
    v[3] = 13;
    v[4] = 9;
    v[5] = 16;

    for (int i=0; i<6; i++){
        printf("%d ",v[i]);
    }
    printf("\n");
    /*

    v = insertion_sort(v, 5);

    for (int i=0; i<5; i++){
        printf("%d ",v[i]);
    }
    printf("\n");
    */

    //TESTING MERGE_SORT()
    int *aux_v = merge_sort(v, 0, 5); 

//    int *aux_v = merge(v, 0, 1, 3);

    for (int i=0; i<6; i++){
        printf("%d ",aux_v[i]);
    }
    printf("\n");
    /*
    */

    return 0;
}
