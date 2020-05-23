#ifndef __GAME_H__
#define __GAME_H__
#include "neighbors.h"
#include "archivos.h"

void show_neighborhood(unsigned char* neighborhood, unsigned int rowsSize, unsigned int columnsSize);
unsigned char evaluate_conditions(unsigned int alive_neighbors, unsigned char my_state);
bool play_game(unsigned char *a, unsigned int rows_size, unsigned int columns_size);
void copy_matrix(unsigned char *a, unsigned char *matrix, unsigned int rows_size, unsigned int columns_size);
#endif