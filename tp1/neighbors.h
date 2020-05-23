#ifndef __NEIGHBORS_H__
#define __NEIGHBORS_H__

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

#define NEIGHBORS_PERIMETER_SIZE 8
#define SIDES_SIZE 2

void findSides(unsigned int referencePoint, unsigned int column, unsigned int columnsSize, unsigned int* sides);
void findNeighbors(unsigned int referencePoint, unsigned int row, unsigned int column, unsigned int rowsSize, unsigned int columnsSize, unsigned int* neighborsPerimeter);
unsigned int vecinos( unsigned char* a, unsigned int i, unsigned int j, unsigned int M, unsigned int N);

#endif