#ifndef TP2_CACHE_H
#define TP2_CACHE_H
#include "binario.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define CACHE_BLOCK_SIZE 128
#define MAIN_MEMORY_SIZE 512
#define AMOUNT_SETS 8
#define AMOUNT_WAY 4
#define VALID_BIT 1
#define INVALID_BIT 0

typedef unsigned char bloqueDeMemoria_t[CACHE_BLOCK_SIZE];

typedef struct bloqueCache {
    int V;
    unsigned int tag;
    bloqueDeMemoria_t* datos;
    int ultimamente_usado;
} bloqueCache_t;

typedef struct conjunto {
    bloqueCache_t* bloqueCache[AMOUNT_WAY];
    int contador;
} conjunto_t;

typedef struct memoriaPrincipal {
    bloqueDeMemoria_t* memoria[MAIN_MEMORY_SIZE];
} memoriaPrincipal_t;


typedef struct cache {
    int amount_access;
    int amount_misses;
    conjunto_t* conjuntos[AMOUNT_SETS];
} cache_t;

cache_t associative_cache;
memoriaPrincipal_t memoriaPrincipal;

unsigned char read_byte(unsigned int address);
void write_byte(unsigned int address, unsigned char value);
float get_miss_rate();
int compare_tag(unsigned int tag, unsigned int set);
unsigned int select_oldest(unsigned int setnum);
void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set);
void write_tocache(unsigned int address, unsigned char value);

void init();
void destroy();

#endif //TP2_CACHE_H
