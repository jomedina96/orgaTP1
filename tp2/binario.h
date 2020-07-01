//
// Created by jonathanmedina on 1/7/20.
//

#ifndef TP2_BINARIO_H
#define TP2_BINARIO_H

unsigned int get_offset(unsigned int address);
unsigned int get_tag(unsigned int address);
unsigned int find_set(unsigned int address);
unsigned int extract_bits(unsigned int addr, unsigned int start, unsigned int kBits);

#endif //TP2_BINARIO_H
