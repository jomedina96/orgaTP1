//
// Created by christianflorez on 1/7/20.
//
#include "cache.h"
#include "lista.c"
#include "binario.h"

int compare_tag(unsigned int tag, unsigned int set) {
    //Esto debería cargarse en una variable global
    cache_t memoriaCache;
    conjunto_t conjunto = memoriaCache.conjuntos[set];

    int way = 0;
    nodo_t* nodo = conjunto.listaEnlazada->prim;
    while (nodo != NULL || nodo->prox != NULL) {
        if (nodo->dato->tag == tag) {
            return way;
        }
        way++;
        nodo = nodo->prox;
    }

    return -1;
}

unsigned int select_oldest(unsigned int setnum) {
    //Esto debería cargarse en una variable global
    cache_t memoriaCache;
    conjunto_t conjunto = memoriaCache.conjuntos[setnum];

    nodo_t* nodo = conjunto.listaEnlazada->prim;
    for (int way = 0; way < conjunto.listaEnlazada->len; way++) {
        if (nodo == NULL) return way;
        nodo = nodo->prox;
    }

    return conjunto.listaEnlazada->len - 1;
}

unsigned char read_byte(unsigned int address) {
    unsigned int offset, set, tag, way, blocknum;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);
    way = compare_tag(tag, set);
    if (way == -1) {
        way = select_oldest(set);
        //calcuar el bloque de memoria principal
        blocknum = (tag << 3) + set;
        read_tocache(blocknum, way, set);
    }
    struct way current_way = associative_cache.vias[way];
    struct conjunto current_set = current_way.conjuntos[set];

    return current_set[offset];
}

