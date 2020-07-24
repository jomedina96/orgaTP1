//
// Created by christianflorez on 1/7/20.
//
#include "cache.h"
#include "binario.h"


int compare_tag(unsigned int tag, unsigned int set) {
    conjunto_t* conjunto = associative_cache.conjuntos[set];

    for (int way = 0; way < AMOUNT_WAY; way++) {
        bloqueCache_t* bloqueCache = conjunto->bloqueCache[way];

        if ((bloqueCache->V == VALID_BIT) && bloqueCache->tag == tag) {
            return way;
        }
    }

    return -1;
}

unsigned int select_oldest(unsigned int setnum) {
    conjunto_t* conjunto = associative_cache.conjuntos[setnum];
    int way = 0;
    for (int i = 0; i < AMOUNT_WAY; i++) {
        bloqueCache_t* bloqueViejo = conjunto->bloqueCache[way];
        bloqueCache_t* bloqueNuevo = conjunto->bloqueCache[i];

        if ((bloqueNuevo->V == VALID_BIT) && (bloqueNuevo->ultimamente_usado < bloqueViejo->ultimamente_usado)) {
            way = i;
        }
    }
    return way;
}

void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set) {
    conjunto_t* conjunto = associative_cache.conjuntos[set];

    bloqueCache_t* bloqueCache = conjunto->bloqueCache[way];

    bloqueCache->datos = memoriaPrincipal.memoria[blocknum];
    bloqueCache->tag = get_tag(blocknum);
    bloqueCache->V = VALID_BIT;
    bloqueCache->ultimamente_usado = conjunto->contador;

    conjunto->contador++;

    associative_cache.amount_access++;
    associative_cache.amount_misses++;
}

unsigned char read_byte(unsigned int address) {
    unsigned int offset, set, tag, way, blocknum;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);
    way = compare_tag(tag, set);

    if (way == -1) {
        way = select_oldest(set);

        //calcula el bloque de memoria principal
        blocknum = (tag << 3) + set;
        read_tocache(blocknum, way, set);
    }

    conjunto_t* conjunto = associative_cache.conjuntos[set];
    bloqueCache_t* bloqueCache = conjunto->bloqueCache[way];

    return *(bloqueCache->datos)[offset];
}

void write_byte(unsigned int address, unsigned char value) {
    unsigned int offset, set, tag, blocknum;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);

    write_tocache(address, value);

    blocknum = (tag << 3) + set;
    *(memoriaPrincipal.memoria)[blocknum][offset] = value;
}

void init() {
    associative_cache.amount_access = 0;
    associative_cache.amount_misses = 0;
    for (int i=0; i<AMOUNT_SETS; i++) {
        conjunto_t *conjunto = malloc(sizeof(conjunto_t));
        conjunto->contador = 0;
        for (int j = 0; j < AMOUNT_WAY; j++) {
            conjunto->bloqueCache[j] = malloc(sizeof(bloqueCache_t));
            conjunto->bloqueCache[j]->V = INVALID_BIT;
            conjunto->bloqueCache[j]->ultimamente_usado = -1;
            conjunto->bloqueCache[j]->datos = NULL;
        }
        associative_cache.conjuntos[i] = conjunto;
    }

    for (int i=0; i<MAIN_MEMORY_SIZE; i++) {
        memoriaPrincipal.memoria[i] = malloc(sizeof(bloqueDeMemoria_t));
    }
}

float get_miss_rate() {
    if (associative_cache.amount_access == 0) return 0;

    return ((float)associative_cache.amount_misses)/((float)associative_cache.amount_access);
}


void write_tocache(unsigned int address, unsigned char value) {
    unsigned int offset, set, tag, way;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);

    conjunto_t* conjunto = associative_cache.conjuntos[set];
    way = compare_tag(tag, set);

    if ( way == -1) {
        associative_cache.amount_misses++
    } else {
        bloqueCache_t* bloqueCache = conjunto->bloqueCache[way];
        *(bloqueCache->datos)[offset] = value;
        bloqueCache->ultimamente_usado = conjunto->contador;
        conjunto->contador++;
    }
    associative_cache.amount_access++;
}
