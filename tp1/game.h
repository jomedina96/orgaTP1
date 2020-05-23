#ifndef __GAME_H__
#define __GAME_H__

void showNeighborhood(unsigned char* neighborhood,unsigned int rowsSize,unsigned int columnsSize);
unsigned char evaluate_conditions(unsigned int alive_neighbors, unsigned char my_state);
void play_game(unsigned char *a, unsigned int rows_size, unsigned int columns_size);

#endif