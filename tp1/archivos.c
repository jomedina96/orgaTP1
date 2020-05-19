#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define ALIVE_CELL 1
#define DEAD_CELL 0
#define BUFFER_ROW_MAX_SIZE 10
#define BUFFER_COL_MAX_SIZE 10

bool load_input(unsigned char** a, int M, int N, char* file_name) {
    FILE* input = fopen(file_name, "r+t");
    if (!input) return false;
    fseek(input, 0L, SEEK_END);
    int numBytes = ftell(input);
    rewind(input);
    
    char* buffer  = malloc(sizeof(char)*(numBytes+1));
    if (!buffer) {
        fclose(input);
        return false;
    }

    int read = fread(buffer, sizeof(char), numbytes, input);
	buffer[read]='\0';
    
    fclose(input);
    bool couldProcessFile =  process_file(a, M, N, buffer);
    
    free(buffer);
    return couldProcessFile;
}

bool process_file(unsigned char** a, int M, int N, char* buffer_file) {
    int idx_file = 0;
    int idx_row = 0;
    int idx_col = 0;
    char buffer_row[BUFFER_ROW_MAX_SIZE];
    buffer_row[0] = '\0';
    char buffer_col[BUFFER_COL_MAX_SIZE];
    buffer_col[0] = '\0';
    bool reading_row = true;
    bool has_to_validate_last_row = false;
    while (buffer_file[idx_file] != '\0') {
        if (!reading_row && (buffer_file[idx_file] == ' ')) {
            return false;
        } else if (buffer_file[idx_file] == ' ') {
            reading_row = false;
            idx_row = 0;
        } else if (buffer_file[idx_file] == '\n') {
            if (!validate_and_process_row(a, M, N, buffer_row, buffer_col)) {
                return false;
            }
            buffer_row[idx_row] = '\0';
            buffer_col[idx_col] = '\0';
            idx_row = 0;
            idx_col = 0;
            reading_row = true;
        } else {
            if (!isdigit(buffer_file[idx_file])) return false;

            if (reading_row) {
                buffer_row[idx_row] = buffer_file[idx_file];
                idx_row++;       
            } else {
                buffer_col[idx_col] = buffer_file[idx_file];
                idx_col++;
            }
        }
        idx_file++;
    }
    if (idx_file > 0) {
        return validate_and_process_row(a, M, N, buffer_row, buffer_col);
    }
    return true;
}

bool validate_and_process_row(unsigned char** a, int M, int N, char* buffer_row, char* buffer_col) {
    if ((strlen(buffer_row) == 0 ) || (strlen(buffer_col) == 0 )) return false;
    
    int row_number = atoi(buffer_row);
    int col_number = atoi(buffer_col);

    if ((row_number>M) || (col_number>N)) return false;

    a[row_number][col_number] = ALIVE_CELL;

    return true;
}