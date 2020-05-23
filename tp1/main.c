#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include "archivos.h"
#include "game.h"

void show_help() {
    fprintf(stderr, "\n");
    fprintf(stderr, "Uso:\n");
    fprintf(stderr, "\tconway -h\n");
    fprintf(stderr, "\tconway -V\n");
    fprintf(stderr, "\tconway i M N inputfile [-o outputprefix]\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Opciones:\n");
    fprintf(stderr, "\t-h, --help \t Imprime este mensaje.\n");
    fprintf(stderr, "\t-V, --version \t Da la versión del programa.\n");
    fprintf(stderr, "\t-o, --outfile \t Prefijo de los archivos de salida.\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Ejemplo:\n");
    fprintf(stderr, "\tconway 10 20 20 glider -o estado\n");
    fprintf(stderr, "\tRepresenta 10 iteraciones del Juego de la Vida en una matriz de 20x20, con un estado inicial tomado del archivo ‘‘glider’’.\n");
    fprintf(stderr, "\tLos archivos de salida se llamarán estado_n.pbm.\n");
    fprintf(stderr, "\tSi no se da un prefijo para los archivos de salida, el prefijo será el nombre del archivo de entrada.\n");
    fprintf(stderr, "\n");
}

void show_version() {
    fprintf(stderr, "\n");
    fprintf(stderr, "Trabajo Práctico 1 - Organización de Computadoras 66.20\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Versión: 0.01\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Integrantes:\n");
    fprintf(stderr, "\tChristian Florez\n");
    fprintf(stderr, "\tJonathan Medina\n");
    fprintf(stderr, "\tPablo Inoriza\n");
    fprintf(stderr, "\n");
}

int main(int argc, char* argv[]) {

    int option;
    char * filenameo;

    /* Parse arguments */
    while ((option = getopt(argc, argv, "o:hV")) != -1)
    {
        switch (option)
        {
        case 'o': /* outfile */
            filenameo = optarg;
            break;

        case 'h': /* help */
            show_help();
            exit(0);
            break;
        
        case 'V': /* version */
            show_version();
            exit(0);
            break;
        
        default:
            fprintf(stderr, "Opción inválida. Asigne la opción -h para obtener ayuda.\n");
            exit(1);
            break;
        }
    }

    int arg_i = atoi(argv[3]);
    int arg_M = atoi(argv[4]);
    int arg_N = atoi(argv[5]);
    char* arg_namefile = argv[6];

    //Esto es para probar la salida de cada parámetro (después se elimina)
    fprintf(stdout, "Cantidad de iteraciones: %i \n", arg_i);
    fprintf(stdout, "Cantidad de filas: %i \n", arg_M);
    fprintf(stdout, "Cantidad de columnas: %i \n", arg_N);
    fprintf(stdout, "Nombre de archivo de entrada: %s \n", arg_namefile);
    fprintf(stdout, "Nombre de archivo de salida: %s \n", filenameo);

    //Con los parámetros ya obtenidos, a continuación se puede invocar todas las funciones restantes...
    unsigned char** game = create_game(arg_M, arg_N);
    load_input(game, arg_M, arg_N, arg_namefile);
    if (load_input) {
        for (int i = 0; i < arg_i; i++) {
            play_game(game, arg_M, arg_N);
            save_game(game, arg_M, arg_N, filenameo, i);
        }
        destroy_game(game, arg_M);
    } else {
        return 1;
    }
    return 0;
}
