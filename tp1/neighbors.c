#include "neighbors.h"

//Funcion que busque los laterales dado un punto
void findSides(unsigned int referencePoint,unsigned int column,unsigned int columnsSize,unsigned int* sides) {
    //Analiza que no este en el borde derecho o izquierdo
    if (column != 0 && column != (columnsSize -1)) {
        sides[0] = referencePoint - 1;
        sides[1] = referencePoint + 1;
    } else {
        //si esta en el borde izquierdo
        if (column == 0) {
            sides[0] = referencePoint + columnsSize - 1;
            sides[1] = referencePoint + 1;
        } else {
            //si esta en el borde derecho
            sides[0] = referencePoint - 1;
            sides[1] = referencePoint - columnsSize + 1;
        }
    }
}

//Funcion que se encarga de encontrar a todos los vecinos del perimetro
void findNeighbors(unsigned int referencePoint,unsigned int row,unsigned int column,unsigned int rowsSize,unsigned int columnsSize,unsigned int* neighborsPerimeter) {
   unsigned int top;
   unsigned int bottom;
   unsigned int centralSides[SIDES_SIZE];
   unsigned int topSides[SIDES_SIZE];
   unsigned int bottomSides[SIDES_SIZE];

    findSides(referencePoint, column, columnsSize, centralSides);
    //analiza si el punto no esta en el borde superior o inferior
    if (row > 0 && row < rowsSize - 1) {
        top = referencePoint - columnsSize;
        findSides(top, column, columnsSize, topSides);
        bottom = referencePoint + columnsSize;
        findSides(bottom, column, columnsSize, bottomSides);
    } else {
        //si esta en el borde superior
        if (row == 0) {
            top = referencePoint + columnsSize*(rowsSize - 1);
            findSides(top, column, columnsSize, topSides);
            bottom = referencePoint + columnsSize;
            findSides(bottom, column, columnsSize, bottomSides);
        } else {
            //si esta en el borde inferior
            top = referencePoint - columnsSize;
            findSides(top, column, columnsSize, topSides);
            bottom = referencePoint - columnsSize * (rowsSize - 1);
            findSides(bottom, column, columnsSize, bottomSides);
        }
    }
    neighborsPerimeter[0] = top;
    neighborsPerimeter[1] = bottom;
    neighborsPerimeter[2] = centralSides[0];
    neighborsPerimeter[3] = centralSides[1];
    neighborsPerimeter[4] = topSides[0];
    neighborsPerimeter[5] = topSides[1];
    neighborsPerimeter[6] = bottomSides[0];
    neighborsPerimeter[7] = bottomSides[1];
} 

unsigned int vecinos(unsigned char* a,unsigned int i,unsigned int j,unsigned int M,unsigned int N) {
   unsigned int referencePoint =  i * N + j;
   unsigned int neighborsPerimeter [NEIGHBORS_PERIMETER_SIZE];
   unsigned int neighborCounter = 0;

    findNeighbors(referencePoint, i, j, M, N, neighborsPerimeter);
    //contabiliza la cantidad de vecinos vivos
    for (int pos = 0; pos < NEIGHBORS_PERIMETER_SIZE; pos++) {
        unsigned int isAlive = a[neighborsPerimeter[pos]] == ALIVE_CELL? 1 : 0;
        neighborCounter += isAlive;
    }

    return neighborCounter;
}