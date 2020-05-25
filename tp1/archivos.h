#ifndef __ARCHIVOS_H__
#define __ARCHIVOS_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "constants.h"

#define BUFFER_ROW_MAX_SIZE 10
#define BUFFER_COL_MAX_SIZE 10

bool load_input(unsigned char *a, unsigned int M, unsigned int N, char* file_name);
bool process_file(unsigned char *a, unsigned int M, unsigned int N, char* buffer_file);
bool validate_and_process_row(unsigned char *a, unsigned int M, unsigned int N, char* buffer_row, char* buffer_col);
bool save_game(unsigned char *a, unsigned int M, unsigned int N, char* prefix_name, int step);
void destroy_game(unsigned char* a);
#endif
