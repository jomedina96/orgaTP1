#include "archivos.h"
void destroy_game(unsigned char* a) {
    free(a);
}

unsigned char* create_matrix_with_dead_cells(unsigned int M, unsigned int N) {
    unsigned char* a = malloc(sizeof(unsigned char*)*M*N);
    if (!a) return NULL;
    for (int i = 0; i < M*N; i++) {
        a[i] = DEAD_CELL;
    }
    return a;
}

bool save_game(unsigned char *a, unsigned int M, unsigned int N, char* prefix_name, int step) {
    char* file_name = malloc(sizeof(char)*(strlen(prefix_name)+9)); // "_000.PBM"
    if (!file_name) return false;

    sprintf(file_name, "%s_%03d.PBM", prefix_name, step);

    FILE* output = fopen(file_name, "w");
    if (!output) return false;
    printf("Grabando %s\n", file_name);
    free(file_name);
    fprintf(output, "P1\n%d %d", M, N);

    for (int i = 0; i < M; i++) {
        fputc('\n', output);
        for (int j = 0; j < N; j++) {
            unsigned int referencePoint =  i * N + j;
            fprintf(output, "%c ", a[referencePoint]);
        }
    }
    fclose(output);
    return true;
}

bool load_input(unsigned char *a, unsigned int M, unsigned int N, char* file_name) {
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

    int read = fread(buffer, sizeof(char), numBytes, input);
	buffer[read]='\0';
    
    fclose(input);
    bool couldProcessFile =  process_file(a, M, N, buffer);
    
    free(buffer);
    return couldProcessFile;
}

bool process_file(unsigned char *a, unsigned int M, unsigned int N, char* buffer_file) {
    int idx_file = 0;
    int idx_row = 0;
    int idx_col = 0;
    char buffer_row[BUFFER_ROW_MAX_SIZE];
    buffer_row[0] = '\0';
    char buffer_col[BUFFER_COL_MAX_SIZE];
    buffer_col[0] = '\0';
    bool reading_row = true;

    while (buffer_file[idx_file] != '\0') {
        if (!reading_row && (buffer_file[idx_file] == ' ')) {
            return false;
        } else if (buffer_file[idx_file] == ' ') {
            reading_row = false;
        } else if (buffer_file[idx_file] == '\n') {
            buffer_row[idx_row] = '\0';
            buffer_col[idx_col] = '\0';
            if (!validate_and_process_row(a, M, N, buffer_row, buffer_col)) {
                return false;
            }
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
/*  TODO: Decidir que hacer si tenemos un archivo de una sola linea sin \n
    Decidir que hacer si tenemos un archivo que termine con \0 la ultima linea, sin \n
    En los ejemplos todos tienen un \n al final (bash command: xxd)

    if (idx_file > 0) {
        buffer_row[idx_row] = '\0';
        buffer_col[idx_col] = '\0';
        return validate_and_process_row(a, M, N, buffer_row, buffer_col);
    }
*/
    return true;
}

bool validate_and_process_row(unsigned char *a, unsigned int M, unsigned int N, char* buffer_row, char* buffer_col) {
    if ((strlen(buffer_row) == 0 ) || (strlen(buffer_col) == 0 )) return false;
    
    int row_number = atoi(buffer_row) - 1;
    int col_number = atoi(buffer_col) - 1;

    if ((row_number>M) || (col_number>N)) return false;

    unsigned int referencePoint =  row_number * N + col_number;
    a[referencePoint] = ALIVE_CELL;

    return true;
}
