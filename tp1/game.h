#ifndef __GAME_H__
#define __GAME_H__
#include "neighbors.h"
#include "archivos.h"
#include "constants.h"

unsigned char evaluate_conditions(unsigned int alive_neighbors, unsigned char my_state);
bool play_game(unsigned char *a, unsigned int rows_size, unsigned int columns_size);
unsigned char* create_matrix_with_dead_cells(unsigned int M, unsigned int N);
void copy_matrix(unsigned char *a, unsigned char *matrix, unsigned int rows_size, unsigned int columns_size);
#endif