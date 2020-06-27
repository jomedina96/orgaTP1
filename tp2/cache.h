#ifndef TP2_CACHE_H
#define TP2_CACHE_H
#include "lista.h"

struct bloqueCache;
struct conjunto;
struct cache;

typedef unsigned char[128] bloqueDeMemoria_t;

typedef struct memoriaPrincipal {
    bloqueDeMemoria_t memoria[512];
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
