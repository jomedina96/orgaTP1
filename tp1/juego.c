/* Inclusión de archivos */
#include <stdio.h>
#include <stdlib.h>
#define DEAD_CELL '0'
#define NEIGHBORS_PERIMETER_SIZE 8
#define SIDES_SIZE 2

void imprimir(char* matriz, int filas, int columnas) /* Función donde se ejecuta la lógica del programa */
{
	 for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++){
            printf("%c", *(matriz));
			printf(" ");
            matriz = matriz + 1;
		}
        printf("\n");
    }
	return; /* sale de la función */
}

int* findSides(int pos_referencia, int col_actual, int max_col, int* sides) {
    printf("Calculo sides \n");
    //int* sides = malloc(2*sizeof(int));
    if (col_actual != 0 && col_actual != (max_col -1)) {
        sides[0] = pos_referencia - 1;
        sides[1] = pos_referencia + 1;
    } else {
        if (col_actual == 0) {
            sides[0] = pos_referencia + max_col - 1;
            sides[1] = pos_referencia + 1;
        } else {
            sides[0] = pos_referencia - 1;
            sides[1] = pos_referencia - max_col + 1;
        }
    }
    printf("%d\n", sides[0]);
    printf("%d\n", sides[1]);
    return sides;
}


int* findNeighbors(int pos_referencia, int pos_fil, int pos_col, int max_fila, int max_col, int* neighborsPerimeter) {
    int top;
    int bottom;
    int centralSides[SIDES_SIZE];
    int topSides[SIDES_SIZE];
    int bottomSides[SIDES_SIZE];

    findSides(pos_referencia, pos_col, max_col, centralSides);
    
    if (pos_fil > 0 && pos_fil < max_fila - 1) {
        top = pos_referencia - max_col;
        findSides(top, pos_col, max_col, topSides);
        bottom = pos_referencia + max_col;
        findSides(bottom, pos_col, max_col, bottomSides);
    } else {
        if (pos_fil == 0) {
            top = pos_referencia + max_col*(max_fila - 1);
            findSides(top, pos_col, max_col, topSides);
            bottom = pos_referencia + max_col;
            findSides(bottom, pos_col, max_col, bottomSides);
        } else {
            top = pos_referencia - max_col;
            findSides(top, pos_col, max_col, topSides);
            bottom = pos_referencia - max_col * (max_fila - 1);
            findSides(bottom, pos_col, max_col, bottomSides);
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
    int pos_referencia =  i * N + j;
    int neighborsPerimeter [NEIGHBORS_PERIMETER_SIZE];
    int contador = 0;

    findNeighbors(pos_referencia, i, j, M, N, neighborsPerimeter);
    for (int pos = 0; pos < NEIGHBORS_PERIMETER_SIZE; pos++) {
        printf("%d\n", neighborsPerimeter[pos]);
        contador += *(neighborsPerimeter[pos] + a) - DEAD_CELL;
    }
    return contador; 

}

int main() {

    char glider[5][4] = {{'0','0','1','0'},{'1','0','1','0'},{'1','1','0','1'},{'0','1','1','0'},{'0','0','0','0'}};
    int max_filas = (sizeof(glider)/sizeof(glider[0]));
    int max_columnas = (sizeof(glider[0])/sizeof(glider[0][0]));
    imprimir(glider, max_filas, max_columnas);
    int result = vecinos(glider, 2, 3, max_filas, max_columnas);
    printf("cantidad de vecinos vivos: ");
    printf("%d\n", result);
    /*for (int i = 0; i < max_filas; i++) {
        for (int j = 0; j < max_columnas; j++){
            vecinos(glider, i, j, max_filas, max_columnas);
		}
    }*/
}