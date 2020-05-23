#include "neighbors.h"

//Funcion que busque los laterales dado un punto
int* findSides(int referencePoint, int column, int columnsSize, int* sides) {
    printf("Calculo sides \n");
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
    return sides;
}

//Funcion que se encarga de encontrar a todos los vecinos del perimetro
int* findNeighbors(int referencePoint, int row, int column, int rowsSize, int columnsSize, int* neighborsPerimeter) {
    int top;
    int bottom;
    int centralSides[SIDES_SIZE];
    int topSides[SIDES_SIZE];
    int bottomSides[SIDES_SIZE];

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
    
    return neighborsPerimeter;
} 

int vecinos(char* a, int i, int j, int M, int N) {
    int referencePoint =  i * N + j;
    int neighborsPerimeter [NEIGHBORS_PERIMETER_SIZE];
    int neighborCounter = 0;

    findNeighbors(referencePoint, i, j, M, N, neighborsPerimeter);
    //contabiliza la cantidad de vecinos vivos
    for (int pos = 0; pos < NEIGHBORS_PERIMETER_SIZE; pos++) {
        printf("%d\n", neighborsPerimeter[pos]);
        neighborCounter += *(neighborsPerimeter[pos] + a) - DEAD_CELL;
    }
    return neighborCounter; 
}