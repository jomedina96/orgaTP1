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
        switch (bloqueNuevo->V) {
            case INVALID_BIT: {
                way = i;
                break;
            }
            case VALID_BIT: {
                if (bloqueNuevo->ultimamente_usado < bloqueViejo->ultimamente_usado) {
                    way = i;
                }
                break;
            }
        }
    }

    return way;
}

void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set) {
    printf("Taking blocknum %d to cache with way: %d, set: %d\n", blocknum, way, set);
    conjunto_t* conjunto = associative_cache.conjuntos[set];

    bloqueCache_t* bloqueCache = conjunto->bloqueCache[way];

    bloqueCache->datos = memoriaPrincipal.memoria[blocknum];
    bloqueCache->tag = get_tag(blocknum);
    bloqueCache->V = VALID_BIT;

    associative_cache.amount_access++;
    associative_cache.amount_misses++;
}

unsigned char read_byte(unsigned int address) {
    unsigned int offset, set, tag, blocknum;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);

    printf("\nReading byte with: %d tag, %d set, %d offset. Address: %d\n", tag, set, offset, address);
    int way = compare_tag(tag, set);

    if (way == -1) {
        printf("Couldn't find address in cache\n");
        unsigned int newWay = select_oldest(set);

        //calcula el bloque de memoria principal
        blocknum = (tag << 3) + set;
        read_tocache(blocknum, newWay, set);

        way = newWay;
    }

    conjunto_t* conjunto = associative_cache.conjuntos[set];
    bloqueCache_t* bloqueCache = conjunto->bloqueCache[way];

    bloqueCache->ultimamente_usado = conjunto->contador;
    conjunto->contador++;

    return *(bloqueCache->datos)[offset];
}

void write_byte(unsigned int address, unsigned char value) {
    unsigned int offset, set, tag, blocknum;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);

    printf("\nWriting byte %u with: %d tag, %d set, %d offset. Address: %d\n", value, tag, set, offset, address);

    write_tocache(address, value);

    blocknum = (tag << 3) + set;
    *(memoriaPrincipal.memoria[blocknum])[offset] = value;
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
    float missRate;
    if (associative_cache.amount_access == 0) {
        missRate =  0;
    } else {
        missRate = ((float)associative_cache.amount_misses)/((float)associative_cache.amount_access);
    }

    printf("Missrate: %f\n", missRate);
    return missRate;
}


void write_tocache(unsigned int address, unsigned char value) {
    unsigned int offset, set, tag;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);

    conjunto_t* conjunto = associative_cache.conjuntos[set];
    int way = compare_tag(tag, set);

    if ( way == -1) {
        printf("Couldn't write to cache %d tag, %d set, %d offset\n", tag, set, offset);
        associative_cache.amount_misses++;
    } else {
        printf("Hit writing cache %d tag, %d set, %d offset\n", tag, set, offset);
        bloqueCache_t* bloqueCache = conjunto->bloqueCache[way];
        *(bloqueCache->datos)[offset] = value;
        bloqueCache->ultimamente_usado = conjunto->contador;
        conjunto->contador++;
    }
    associative_cache.amount_access++;
}

void destroy() {
    for (int i=0; i<MAIN_MEMORY_SIZE; i++) {
        if (!memoriaPrincipal.memoria[i]) continue;
        free(memoriaPrincipal.memoria[i]);
    }
    for (int i=0; i < AMOUNT_SETS; i++) {
        conjunto_t* conjunto = associative_cache.conjuntos[i];
        if (!conjunto) continue;

        for (int j = 0; j < AMOUNT_WAY; j++) {
            if (!conjunto->bloqueCache[j]) continue;
            free(conjunto->bloqueCache[j]);
        }
        free(conjunto);
    }

}
