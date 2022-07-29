#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#include "./func.h"

CoefData* mergeIndex(CoefData v[], int left, int mid, int right){

    int n1 = mid - left + 1;
    int n2 = right - mid;
  
    CoefData v_left[n1], v_right[n2];
  
    for (int i = 0; i < n1; i++)
        v_left[i] = v[left + i];

    for (int j = 0; j < n2; j++)
        v_right[j] = v[mid + 1 + j];
  
    int i=0, j=0, k=left;
    do{

        if (v_left[i].idx < v_right[j].idx) 
            v[k] = v_left[i++];

        else {
            v[k] = v_right[j++];
        }

        k++;
    }while (i < n1 && j < n2);

    while (i < n1) 
        v[k++] = v_left[i++];
  
    while (j < n2) 
        v[k++] = v_right[j++];

    return v;
}
  
CoefData* mergeSortIndex(CoefData v[], int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;
  
        v = mergeSortIndex(v, left, mid);
        v = mergeSortIndex(v, mid + 1, right);
  
        v = mergeIndex(v, left, mid, right);

        return v;
    }

    return v;
}

CoefData* mergeMagnitude(CoefData v[], int left, int mid, int right){

    int n1 = mid - left + 1;
    int n2 = right - mid;
  
    CoefData v_left[n1], v_right[n2];
  
    for (int i = 0; i < n1; i++)
        v_left[i] = v[left + i];

    for (int j = 0; j < n2; j++)
        v_right[j] = v[mid + 1 + j];
  
    int i=0, j=0, k=left;
    do{

        if (v_left[i].magnitude >= v_right[j].magnitude) 
            v[k] = v_left[i++];

        else {
            v[k] = v_right[j++];
        }

        k++;
    }while (i < n1 && j < n2);

    while (i < n1) 
        v[k++] = v_left[i++];
  
    while (j < n2) 
        v[k++] = v_right[j++];

    return v;
}
  
CoefData* mergeSortMagnitude(CoefData v[], int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;
  
        v = mergeSortMagnitude(v, left, mid);
        v = mergeSortMagnitude(v, mid + 1, right);
  
        v = mergeMagnitude(v, left, mid, right);

        return v;
    }

    return v;
}

unsigned char* read_wav_data(char* fname, int *data_size) {
    FILE* fp = fopen(fname, "rb");
    unsigned char buf4[4];

    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    int dataSize = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;

    unsigned char* data = malloc(sizeof(*data) * (dataSize));
    
    int i = 0;
    while (i < dataSize) {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);

    *data_size = dataSize;
    return data;
}

CoefData *DFT(unsigned char *audio, int length) {
    CoefData *coef = (CoefData *) calloc(length, sizeof(CoefData));

    int k;
    int counter_leq_zero = 0; //contador de valores menores ou iguais a zero
    for (k = 0; k < length; k++) {
        for (int n = 0; n < length; n++) {
            coef[k].coef += audio[n] * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }

        coef[k].magnitude = sqrt(pow(creal(coef[k].coef),2) + pow(cimag(coef[k].coef),2));

        //caso a parte real e a imaginária sejam menores que 0, incrementar contador
        if (creal(coef[k].coef) <= 0 && cimag(coef[k].coef) <= 0)
            counter_leq_zero++;

        coef[k].idx = k;
    }

    printf("%d\n",k); //imprime a quantidade de samples
    printf("%d\n",counter_leq_zero); //imprime a quantidade de valores menores ou iguais a zero
    return coef;
}

unsigned char* DFT_inverse(CoefData *v_coef, int length) {
    unsigned char *audio = (unsigned char *) malloc(length * sizeof(unsigned char));
    CoefData *coef = (CoefData *) calloc(length, sizeof(CoefData));

    for (int n = 0; n < length; n++) {
        for (int k = 0; k < length; k++) {
            coef[n].coef += v_coef[k].coef * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }
        coef[n].coef = (int) coef[n].coef/length;
        coef[n].magnitude = sqrt(pow(creal(coef[n].coef),2) + pow(cimag(coef[n].coef),2));
        coef[n].idx = n;
        audio[n] = creal(coef[n].coef);
//        printf("%d) %.1lf + %.1lfi\n", k, creal(coef[k].coef), cimag(coef[k].coef));
    }

    free(coef);

    return audio;
}
