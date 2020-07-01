//
// Created by jonathanmedina on 1/7/20.
//

#include "binario.h"

unsigned int extract_bits(unsigned int addr, unsigned int start, unsigned int kBits) {
    return (addr & (((1 << kBits) - 1) << start)) >> start;
}

unsigned int get_offset(unsigned int address) {
    return extract_bits(address, 0, 7);
}

unsigned int get_tag(unsigned int address) {
    return extract_bits(address, 10, 6);
}

unsigned int find_set(unsigned int address) {
    return extract_bits(address, 7, 3);
}
