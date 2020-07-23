//
// Created by christianflorez on 1/7/20.
//
#include "cache.h"
#include "binario.h"


int compare_tag(unsigned int tag, unsigned int set) {
    conjunto_t* conjunto = associative_cache.conjuntos[set];

    int way = 0;
    nodo_t* nodo = conjunto->listaEnlazada->prim;
    while (nodo != NULL) {
        if ((nodo->dato->tag == tag) && (nodo->dato->V == 1)) {
            return way;
        }

        way++;
        nodo = nodo->prox;
    }

    return -1;
}

unsigned int select_oldest(unsigned int setnum) {
    conjunto_t* conjunto = associative_cache.conjuntos[setnum];
    if (lista_esta_vacia(conjunto->listaEnlazada)) return 0;

    return lista_largo(conjunto->listaEnlazada) - 1;
}

void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set) {
    conjunto_t* conjunto = associative_cache.conjuntos[set];
    nodo_t* nodo = conjunto->listaEnlazada->prim;

    for (int i=0; i <= way; i++) {
        nodo = nodo->prox;
    }

    nodo->dato->datos = memoriaPrincipal.memoria[blocknum];
    nodo->dato->tag = get_tag(blocknum);
    nodo->dato->V = 1;

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
        if (way < AMOUNT_WAY-1) {
            read_tocache(blocknum, way+1, set);
        } else {
            read_tocache(blocknum, way, set);
        }

    }

    conjunto_t* conjunto = associative_cache.conjuntos[set];
    nodo_t* nodo = conjunto->listaEnlazada->prim;

    for (int i=0; i <= way; i++) {
        nodo = nodo->prox;
    }

    return *(nodo->dato->datos)[offset];
}

void write_byte(unsigned int address, unsigned char value) {

    unsigned int offset, set, tag, way, blocknum;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);
    way = compare_tag(tag, set);
    if ( way != -1) {
        write_tocache(address, value);
    }
    blocknum = (tag << 3) + set;
    *(memoriaPrincipal.memoria)[blocknum][offset] = value;
}

void init() {
    associative_cache.amount_access = 0;
    associative_cache.amount_misses = 0;
    for (int i=0; i<8; i++) {
        conjunto_t *conjunto = malloc(sizeof(conjunto_t));
        conjunto->listaEnlazada = lista_crear();
        associative_cache.conjuntos[i] = conjunto;
    }

    for (int i=0; i<MAIN_MEMORY_SIZE; i++) {
        memoriaPrincipal.memoria[i] = malloc(sizeof(bloqueDeMemoria_t));
    }
}

float get_miss_rate() {
    return ((float)associative_cache.amount_misses)/((float)associative_cache.amount_access);
}


void write_tocache(unsigned int address, unsigned char value) {
    unsigned int offset, set, tag;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);

    nodo_t* way = associative_cache.conjuntos[set]->listaEnlazada->prim;

    while (way) {
        if (way->dato->V == 1 && way->dato->tag == tag) {
            *(way->dato->datos)[offset] = value;
            break;
        }
        way = way->prox;
    }

    if (!way) associative_cache.amount_misses++;
    associative_cache.amount_access++;
}
