#ifndef __ARCHIVOS_H__
#define __ARCHIVOS_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALIVE_CELL 1
#define DEAD_CELL 0
#define BUFFER_ROW_MAX_SIZE 10
#define BUFFER_COL_MAX_SIZE 10

bool load_input(unsigned char** a, int M, int N, char* file_name);
bool process_file(unsigned char** a, int M, int N, char* buffer_file);
bool validate_and_process_row(unsigned char** a, int M, int N, char* buffer_row, char* buffer_col);


#endif
