#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>

#define MAX_LEITURA 100
#define TAM_ASCII 256

typedef struct nohuff {
    void *caracter; // Ponteiro genérico para caracter ou valor (como um array)
    int frequencia;
    struct nohuff *prox;
    struct nohuff *esquerda, *direita;
}NOHUFF;

// Essa merda é uma heap
typedef struct {
    NOHUFF *inicio; // Susbtitui a função do array
    int tamanho;
}LISTA;