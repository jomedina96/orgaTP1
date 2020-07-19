//
// Created by christianflorez on 1/7/20.
//
#include "cache.h"

unsigned char read_byte(unsigned int address) {

    unsigned int offset, set, tag, way, blocknum;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);
    way = compare_tag(tag, set);
    if ( way == -1) {
        way = select_oldest(set);
        //calcula el bloque de memoria principal
        blocknum = (tag << 3) + set;
        read_tocache(blocknum, way, set);
    }
    struct way current_way = associative_cache.vias[way];
    struct conjunto current_set = current_way.conjuntos[set];

    return current_set[offset];
}

void write_byte(unsigned int address, unsigned char value) {

    unsigned int offset, set, tag, way, blocknum;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);
    way = compare_tag(tag, set);
    if ( way != -1) {
        write_tocache(address, value)
    }
    blocknum = (tag << 3) + set;
    memoriaPrincipal.memoria[blocknum] = value;
}

void init() {
    associative_cache.amount_access = 0;
    associative_cache.amount_misses = 0;
    for (int i=0; i<4; i++) {
        way_t* way = malloc(sizeof(way_t));
        for (int j=0; j<8; j++) {
            conjunto_t* conjunto = malloc(sizeof(conjunto_t));
            conjunto->listaEnlazada = lista_crear();
            way->conjuntos = conjunto;
        }
        associative_cache.ways[i] = way;
    }

    for (int i=0; i<MAIN_MEMORY_SIZE; i++) {
        memoriaPrincipal.memoria[i] = malloc(sizeof(bloqueDeMemoria_t));
    }
}