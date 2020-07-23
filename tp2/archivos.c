//
// Created by jonathanmedina on 29/6/20.
//
#include "archivos.h"
#include "cache.h"

bool ejecutar_desde_archivo(char* nombre_archivo) {
    FILE* input = fopen(nombre_archivo, "r+t");
    if (!input) {
        fprintf(stderr, "Error archivo inexistente\n");
        return false;
    }
    fseek(input, 0L, SEEK_END);
    int numBytes = ftell(input);
    rewind(input);

    char* buffer  = malloc(sizeof(char)*(numBytes+1));
    if (!buffer) {
        fclose(input);
        fprintf(stderr, "Error mientras se intentaba pedir memoria para parsear el archivo\n");
        return false;
    }

    int read = fread(buffer, sizeof(char), numBytes, input);
    buffer[read]='\0';

    fclose(input);
    bool pudo_procesar = procesar_archivo(buffer);

    if (!pudo_procesar) {
        fprintf(stderr, "Error en el procesamiento del archivo\n");
    }

    free(buffer);
    return pudo_procesar;
}

bool procesar_archivo(char* buffer) {
    int i = 0;
    char comando_buffer[BUFFER_SIZE_MAX];
    comando_buffer[0] = '\0';

    char primer_parametro_buffer[BUFFER_SIZE_MAX];
    primer_parametro_buffer[0] = '\0';

    char segundo_parametro_buffer[BUFFER_SIZE_MAX];
    segundo_parametro_buffer[0] = '\0';

    bool leer_comando = true;
    bool leer_primer_parametro = false;
    bool leer_segundo_parametro = false;
    int j = 0;

    while (buffer[i]) {
        if (buffer[i] == '\n') {
            if (!procesar_linea(comando_buffer, primer_parametro_buffer, segundo_parametro_buffer)) {
                return false;
            }
            leer_comando = true;
            leer_primer_parametro = false;
            leer_segundo_parametro = false;
            comando_buffer[0] = '\0';
            primer_parametro_buffer[0] = '\0';
            segundo_parametro_buffer[0] = '\0';
            j = 0;
        } else if (leer_comando && buffer[i] == ' ') {
            leer_comando = false;
            leer_primer_parametro = true;
            j = 0;
        } else if (leer_comando) {
            comando_buffer[j] = buffer[i];
            j++;
            comando_buffer[j] = '\0';
        } else if (leer_primer_parametro && (buffer[i] == ',')) {
            leer_primer_parametro = false;
            j=0;
        } else if (!leer_primer_parametro && !leer_segundo_parametro && (buffer[i] == ' ')) {
            leer_segundo_parametro = true;
        } else if (leer_primer_parametro && isdigit(buffer[i])) {
                primer_parametro_buffer[j] = buffer[i];
                j++;
                primer_parametro_buffer[j] = '\0';
        } else if (leer_segundo_parametro && isdigit(buffer[i])) {
            segundo_parametro_buffer[j] = buffer[i];
            j++;
            segundo_parametro_buffer[j] = '\0';
        } else {
            return false;
        }

        i++;
    }
    return true;
}

bool procesar_linea(char* comando_buffer, char* primer_parametro_buffer, char* segundo_parametro_buffer) {
    if (strcmp(comando_buffer, FLUSH) == 0) {
        if ((strlen(primer_parametro_buffer) != 0) || (strlen(segundo_parametro_buffer) != 0)) {
            return false;
        }
        init();
    } else if (strcmp(comando_buffer, R) == 0) {
        if ((strlen(primer_parametro_buffer) == 0) || (strlen(segundo_parametro_buffer) != 0)) {
            return false;
        }
        read_byte(atoi(primer_parametro_buffer));
    } else if (strcmp(comando_buffer, W) == 0) {
        if ((strlen(primer_parametro_buffer) == 0) || (strlen(segundo_parametro_buffer) == 0)) {
            return false;
        }
        write_byte(atoi(primer_parametro_buffer), atoi(segundo_parametro_buffer));
    } else if (strcmp(comando_buffer, MR) == 0) {
        if ((strlen(primer_parametro_buffer) != 0) || (strlen(segundo_parametro_buffer) != 0)) {
            return false;
        }
        get_miss_rate();
    } else {
        return false;
    }
    return true;
}




