//
// Created by jonathanmedina on 29/6/20.
//

#ifndef TP2_ARCHIVOS_H
#define TP2_ARCHIVOS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE_MAX 999
#define FLUSH "FLUSH"
#define R "R"
#define W "W"
#define MR "MR"

bool ejecutar_desde_archivo(char* nombre_archivo);
bool procesar_archivo(char* buffer);
bool procesar_linea(char* comando_buffer, char* primer_parametro_buffer, char* segundo_parametro_buffer);

#endif //TP2_ARCHIVOS_H
