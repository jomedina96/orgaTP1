#ifndef __NEIGHBORS_H__
#define __NEIGHBORS_H__

#include <stdio.h>
#include <stdlib.h>
#define DEAD_CELL '0'
#define NEIGHBORS_PERIMETER_SIZE 8
#define SIDES_SIZE 2

int* findSides(int referencePoint, int column, int columnsSize, int* sides);
int* findNeighbors(int referencePoint, int row, int column, int rowsSize, int columnsSize, int* neighborsPerimeter);
int vecinos(char* a, int i, int j, int M, int N);

#endif