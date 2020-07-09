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
        //calcuar el bloque de memoria principal
        blocknum = (tag << 3) + set;
        read_tocache(blocknum, way, set);
    }
    struct way current_way = associative_cache.vias[way];
    struct conjunto current_set = current_way.conjuntos[set];

    return current_set[offset];
}

