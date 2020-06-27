#ifndef TP2_CACHE_H
#define TP2_CACHE_H
#include "lista.h"

struct bloqueCache;
struct conjunto;
struct cache;

typedef struct bloqueCache {
    int V;
    int tag;
    unsigned char[128] datos;
} bloqueCache_t;

typedef struct conjunto {
    lista_t* listaEnlazada;
} conjunto_t;

typedef struct cache {
    conjunto_t conjuntos[8];
} cache_t;

#endif //TP2_CACHE_H
