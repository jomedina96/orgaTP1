#ifndef TP2_CACHE_H
#define TP2_CACHE_H
#include "lista.h"
#include "binario.h"
#define CACHE_BLOCK_SIZE 128
#define MAIN_MEMORY_SIZE 512

typedef unsigned char bloqueDeMemoria_t[CACHE_BLOCK_SIZE];

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

//typedef struct way {
//    conjunto_t* conjuntos[8];
//} way_t;

typedef struct cache {
    int amount_access;
    int amount_misses;
    //way_t* ways[4];
    conjunto_t* conjuntos[8];
} cache_t;

cache_t associative_cache;
memoriaPrincipal_t memoriaPrincipal;

unsigned char read_byte(unsigned int address);
void write_byte(unsigned int address, unsigned char value);
float get_miss_rate();
void init();

#endif //TP2_CACHE_H
