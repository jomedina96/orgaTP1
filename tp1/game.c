#include "game.h"

void show_neighborhood(unsigned char* neighborhood, unsigned int rows_size, unsigned int columns_size) {
	 for (int i = 0; i < rows_size; i++) {
        for (int j = 0; j < columns_size; j++){
            printf("%c ", *(neighborhood));
			neighborhood++;
        }
        printf("\n");
    }
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
            return ALIVE_CELL;
        }
    }
    return my_state;
} 


bool play_game(unsigned char *a, unsigned int rows_size, unsigned int columns_size) {
    unsigned char *matrix = create_matrix_with_dead_cells(rows_size, columns_size);
    if (!matrix) {
        return false;
    }
    for (unsigned int i = 0; i < rows_size; i++) {
        for (unsigned int j = 0; j < columns_size; j++) {
            unsigned int neighbor = vecinos(a, i, j, rows_size, columns_size);
            unsigned int reference_point = i * columns_size + j;
            matrix[reference_point] = evaluate_conditions(neighbor, a[reference_point]);
		}
    }
    copy_matrix(a, matrix, rows_size, columns_size);
    destroy_game(matrix);
    return true;
}

void copy_matrix(unsigned char *a, unsigned char *matrix, unsigned int rows_size, unsigned int columns_size) {
    for (unsigned int i = 0; i < rows_size; i++) {
        for (unsigned int j = 0; j < columns_size; j++) {
            unsigned int reference_point = i * columns_size + j;
            a[reference_point] = matrix[reference_point];
        }
    }
}
