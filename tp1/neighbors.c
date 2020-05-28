#include "neighbors.h"

//Funcion que busque los laterales dado un punto
void find_sides(unsigned int reference_point, unsigned int column, unsigned int columns_size, unsigned int* sides) {
    //Analiza que no este en el borde derecho o izquierdo
    if (column != 0 && column != (columns_size - 1)) {
        sides[0] = reference_point - 1;
        sides[1] = reference_point + 1;
    } else {
        //si esta en el borde izquierdo
        if (column == 0) {
            sides[0] = reference_point + columns_size - 1;
            sides[1] = reference_point + 1;
        } else {
            //si esta en el borde derecho
            sides[0] = reference_point - 1;
            sides[1] = reference_point - columns_size + 1;
        }
    }
}

//Funcion que se encarga de encontrar a todos los vecinos del perimetro
void find_neighbors(unsigned int reference_point, unsigned int row, unsigned int column, unsigned int rowsSize, unsigned int columns_size, unsigned int* neighbors_perimeter) {
   unsigned int top;
   unsigned int bottom;
   unsigned int central_sides[SIDES_SIZE];
   unsigned int top_sides[SIDES_SIZE];
   unsigned int bottom_sides[SIDES_SIZE];

    find_sides(reference_point, column, columns_size, central_sides);
    //analiza si el punto no esta en el borde superior o inferior
    if (row > 0 && row < rowsSize - 1) {
        top = reference_point - columns_size;
        find_sides(top, column, columns_size, top_sides);
        bottom = reference_point + columns_size;
        find_sides(bottom, column, columns_size, bottom_sides);
    } else {
        //si esta en el borde superior
        if (row == 0) {
            top = reference_point + columns_size * (rowsSize - 1);
            find_sides(top, column, columns_size, top_sides);
            bottom = reference_point + columns_size;
            find_sides(bottom, column, columns_size, bottom_sides);
        } else {
            //si esta en el borde inferior
            top = reference_point - columns_size;
            find_sides(top, column, columns_size, top_sides);
            bottom = reference_point - columns_size * (rowsSize - 1);
            find_sides(bottom, column, columns_size, bottom_sides);
        }
    }
    neighbors_perimeter[0] = top;
    neighbors_perimeter[1] = bottom;
    neighbors_perimeter[2] = central_sides[0];
    neighbors_perimeter[3] = central_sides[1];
    neighbors_perimeter[4] = top_sides[0];
    neighbors_perimeter[5] = top_sides[1];
    neighbors_perimeter[6] = bottom_sides[0];
    neighbors_perimeter[7] = bottom_sides[1];
} 

unsigned int vecinos(unsigned char* a,unsigned int i,unsigned int j,unsigned int M,unsigned int N) {
   unsigned int reference_point = i * N + j;
   unsigned int neighbors_perimeter [NEIGHBORS_PERIMETER_SIZE];
   unsigned int neighbor_counter = 0;

    find_neighbors(reference_point, i, j, M, N, neighbors_perimeter);
    //contabiliza la cantidad de vecinos vivos
    for (int pos = 0; pos < NEIGHBORS_PERIMETER_SIZE; pos++) {
        unsigned int is_alive = a[neighbors_perimeter[pos]] == ALIVE_CELL ? 1 : 0;
        neighbor_counter += is_alive;
    }

    return neighbor_counter;
}