#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include "archivos.h"
#include "game.h"

void show_help() {
    fprintf(stdout, "\n");
    fprintf(stdout, "Uso:\n");
    fprintf(stdout, "\tconway -h\n");
    fprintf(stdout, "\tconway -V\n");
    fprintf(stdout, "\tconway i M N inputfile [-o outputprefix]\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Opciones:\n");
    fprintf(stdout, "\t-h, --help \t Imprime este mensaje.\n");
    fprintf(stdout, "\t-V, --version \t Da la versión del programa.\n");
    fprintf(stdout, "\t-o, --outfile \t Prefijo de los archivos de salida.\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Ejemplo:\n");
    fprintf(stdout, "\tconway 10 20 20 glider -o estado\n");
    fprintf(stdout, "\tRepresenta 10 iteraciones del Juego de la Vida en una matriz de 20x20, con un estado inicial tomado del archivo ‘‘glider’’.\n");
    fprintf(stdout, "\tLos archivos de salida se llamarán estado_n.pbm.\n");
    fprintf(stdout, "\tSi no se da un prefijo para los archivos de salida, el prefijo será el nombre del archivo de entrada.\n");
    fprintf(stdout, "\n");
}

void show_version() {
    fprintf(stdout, "\n");
    fprintf(stdout, "Trabajo Práctico 1 - Organización de Computadoras 66.20\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Versión: 0.01\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Integrantes:\n");
    fprintf(stdout, "\tChristian Florez\n");
    fprintf(stdout, "\tJonathan Medina\n");
    fprintf(stdout, "\tPablo Inoriza\n");
    fprintf(stdout, "\n");
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
            fprintf(stdout, "Opción inválida. Asigne la opción -h para obtener ayuda.\n");
            exit(1);
            break;
        }
    }

    int arg_i = atoi(argv[3]);
    int arg_M = atoi(argv[4]);
    int arg_N = atoi(argv[5]);
    char* arg_namefile = argv[6];

    unsigned char* game = create_matrix_with_dead_cells(arg_M, arg_N);
    if (!game) {
        return 1;
    }
    bool couldLoadInput = load_input(game, arg_M, arg_N, arg_namefile);

    if (!couldLoadInput) {
        fprintf(stderr, "Couldn't load the input\n");
        return 1;
    }
    for (int i = 0; i < arg_i; i++) {
            bool couldPlay = play_game(game, arg_M, arg_N);
            if (!couldPlay) {
                fprintf(stderr, "Couldn't play the game\n");
                destroy_game(game);
                return 1;
            }
            bool couldSave = save_game(game, arg_M, arg_N, filenameo, i);
            if (!couldSave) {
                fprintf(stderr, "Couldn't save the game\n");
                destroy_game(game);
                return 1;
            }
    }
    printf("Listo\n");
    destroy_game(game);
    return 0;
}
