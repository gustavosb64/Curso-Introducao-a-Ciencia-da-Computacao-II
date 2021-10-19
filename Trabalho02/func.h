#ifndef FUNC_H
#define FUNC_H


/*
 * A estrutura coefData mantém os dados de cada sample.
 *  coef: mantém o valor complexo 
 *  magnitude: armazena a magnitude
 *  idx: armazena o índice original
*/
typedef struct coefData{
    double complex coef;
    double magnitude; 
    int idx;
}CoefData;

/*Função de merge, chamada pela mergeSortIndex, para ordenar os coeficientes pelos seus índices
 *  seus parâmetros são um vetor de CoefData, a ser ordenado, e inteiros referentes às posições
 *  utilizadas pelo algoritmo de ordenação.
 *  retorna o próprio vetor ordenado.
*/
CoefData* mergeIndex(CoefData v[], int left, int mid, int right);

/*função mergeSort para ordenar os coeficientes pelos seus índices
 *  seus parâmetros são um vetor de CoefData, a ser ordenado, e inteiros referentes às posições
 *  utilizadas pelo algoritmo de ordenação.
 *  retorna o próprio vetor ordenado.
*/
CoefData* mergeSortIndex(CoefData v[], int left, int right) ;

/*função merge, chamada pela mergeSortMagnitude, para ordenar os coeficientes pela magnitude
 *  seus parâmetros e retorno são análos ao mergeIndex
*/
CoefData* mergeMagnitude(CoefData v[], int left, int mid, int right);

/*função mergeSort para ordenar os coeficientes pela magnitude
 *  seus parâmetros e retorno são análos ao mergeSortIndex
*/
CoefData* mergeSortMagnitude(CoefData v[], int left, int right) ;

unsigned char* read_wav_data(char* fname, int *data_size) ;

CoefData *DFT(unsigned char *audio, int length) ;

/*DFT inversa
 *  seus parâmetros são o vetor de coeficientes, lido em DFT, e o comprimento do arquivo.
 *  seu retorno é um unsigned char* referente aos dados no arquivo de áudio comprimido
*/
unsigned char* DFT_inverse(CoefData *v_coef, int length) ;


#endif
