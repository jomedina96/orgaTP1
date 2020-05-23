#include "neighbors.h"
#include "archivos.h"

void showNeighborhood(char* neighborhood, int rowsSize, int columnsSize) {
	 for (int i = 0; i < rowsSize; i++) {
        for (int j = 0; j < columnsSize; j++){
            printf("%c", *(neighborhood));
			printf(" ");
            neighborhood = neighborhood + 1;
		}
        printf("\n");
    }
	return;
}

unsigned char evaluate_conditions(unsigned int alive_neighbors, unsigned char my_state) {
    
    if (alive_neighbors < 2 || alive_neighbors > 3) {
        return DEAD_CELL;
    }
    if (my_state == ALIVE_CELL) {
        if(alive_neighbors == 2 || alive_neighbors == 3) {
            return ALIVE_CELL;
        }
    } else {
        if (alive_neighbors == 3) {
            return DEAD_CELL;
        }
    }
    return my_state;
} 


void play_game(unsigned char** a, unsigned int rows_size, unsigned int columns_size) {
    unsigned char** matrix = create_game(rows_size, columns_size);
    int neighbor;
    char new_state;
    for (int i = 0; i < rows_size; i++) {
        for (int j = 0; j < columns_size; j++) {
            neighbor = vecinos(a[0], i, j, rows_size, columns_size);
             matrix[i][j] = evaluate_conditions(neighbor, a[i][j]);
		}
    }
    destroy_game(a, rows_size);
    a = matrix;
}
