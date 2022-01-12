/* Estrutura de dados Hashing
 * com tabela hash com inteiros cujas chaves são positivas
 * e funcoes para criacao, busca, etc.
 * Moacir A Ponti 2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FREE -1
#define DEL -2

/* cria tabela de tamanho m */
int* create_hash_table(int m);

void destroy_hash_table(int** t);

/* insere elemento key na tabela t de tamanho m */
int insert(int* t, int key, int m);

/* busca elemento key na tabela t de tamanho m */
int search(int* t, int key, int m);

/* exclui elemento key da tabela t de tamanho m */
int remove_hash(int* t, int key, int m);

void print_table(int* t, int m);

int hash_division(int key, int m, int c);

int hash_multi(int key, int m, int c, double A);
