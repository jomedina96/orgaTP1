#ifndef TP2_CACHE_H
#define TP2_CACHE_H
#include "lista.h"
#define CACHE_SIZE 128
#define MAIN_MEMORY_SIZE 512

struct bloqueCache;
struct conjunto;
struct cache;

typedef unsigned char[CACHE_SIZE] bloqueDeMemoria_t;

typedef struct memoriaPrincipal {
    bloqueDeMemoria_t memoria[MAIN_MEMORY_SIZE];
} memoriaPrincipal_t;

typedef struct bloqueCache {
    int V;
    int tag;
    bloqueDeMemoria_t datos;
} bloqueCache_t;

typedef struct conjunto {
    lista_t* listaEnlazada;
} conjunto_t;

typedef struct cache {
    conjunto_t conjuntos[8];
} cache_t;

#endif //TP2_CACHE_H
