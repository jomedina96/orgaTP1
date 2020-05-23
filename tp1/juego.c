/* Inclusión de archivos */
#include <stdio.h>
#include <stdlib.h>
#define DEAD_CELL '0'
#define NEIGHBORS_PERIMETER_SIZE 8
#define SIDES_SIZE 2

void showNeighborhood(char* neighborhood, int rowsSize, int columnsSize) /* Función donde se ejecuta la lógica del programa */
{
	 for (int i = 0; i < rowsSize; i++) {
        for (int j = 0; j < columnsSize; j++){
            printf("%c", *(neighborhood));
			printf(" ");
            neighborhood = neighborhood + 1;
		}
        printf("\n");
    }
	return; /* sale de la función */
}

int* findSides(int referencePoint, int column, int columnsSize, int* sides) {
    printf("Calculo sides \n");
    //int* sides = malloc(2*sizeof(int));
    if (column != 0 && column != (columnsSize -1)) {
        sides[0] = referencePoint - 1;
        sides[1] = referencePoint + 1;
    } else {
        if (column == 0) {
            sides[0] = referencePoint + columnsSize - 1;
            sides[1] = referencePoint + 1;
        } else {
            sides[0] = referencePoint - 1;
            sides[1] = referencePoint - columnsSize + 1;
        }
    }
    printf("%d\n", sides[0]);
    printf("%d\n", sides[1]);
    return sides;
}


int* findNeighbors(int referencePoint, int row, int column, int rowsSize, int columnsSize, int* neighborsPerimeter) {
    int top;
    int bottom;
    int centralSides[SIDES_SIZE];
    int topSides[SIDES_SIZE];
    int bottomSides[SIDES_SIZE];

    findSides(referencePoint, column, columnsSize, centralSides);
    
    if (row > 0 && row < rowsSize - 1) {
        top = referencePoint - columnsSize;
        findSides(top, column, columnsSize, topSides);
        bottom = referencePoint + columnsSize;
        findSides(bottom, column, columnsSize, bottomSides);
    } else {
        if (row == 0) {
            top = referencePoint + columnsSize*(rowsSize - 1);
            findSides(top, column, columnsSize, topSides);
            bottom = referencePoint + columnsSize;
            findSides(bottom, column, columnsSize, bottomSides);
        } else {
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
    for (int pos = 0; pos < NEIGHBORS_PERIMETER_SIZE; pos++) {
        printf("%d\n", neighborsPerimeter[pos]);
        neighborCounter += *(neighborsPerimeter[pos] + a) - DEAD_CELL;
    }
    return neighborCounter; 

}

int main() {

    char glider[5][4] = {{'0','0','1','0'},{'1','0','1','0'},{'1','1','0','1'},{'0','1','1','0'},{'0','0','0','0'}};
    int rowsSize = (sizeof(glider)/sizeof(glider[0]));
    int columnsSize = (sizeof(glider[0])/sizeof(glider[0][0]));
    showNeighborhood(glider, rowsSize, columnsSize);
    int liveNeighbors = vecinos(glider, 2, 3, rowsSize, columnsSize);
    printf("cantidad de vecinos vivos: ");
    printf("%d\n", liveNeighbors);
    /*for (int i = 0; i < max_filas; i++) {
        for (int j = 0; j < max_columnas; j++){
            vecinos(glider, i, j, max_filas, max_columnas);
		}
    }*/
}