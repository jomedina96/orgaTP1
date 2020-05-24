#ifndef __NEIGHBORS_H__
#define __NEIGHBORS_H__

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

#define NEIGHBORS_PERIMETER_SIZE 8
#define SIDES_SIZE 2

void find_sides(unsigned int reference_point, unsigned int column, unsigned int columns_size, unsigned int* sides);
void find_neighbors(unsigned int reference_point, unsigned int row, unsigned int column, unsigned int rowsSize, unsigned int columns_size, unsigned int* neighbors_perimeter);
unsigned int vecinos( unsigned char* a, unsigned int i, unsigned int j, unsigned int M, unsigned int N);

#endif