#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>

void show_help() {
    fprintf(stderr, "\n");
    fprintf(stderr, "Uso:\n");
    fprintf(stderr, "\tconway -h\n");
    fprintf(stderr, "\tconway -V\n");
    fprintf(stderr, "\tconway i M N inputfile [-o outputprefix]\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Opciones:\n");
    fprintf(stderr, "\t-h, --help \t\t Imprime este mensaje.\n");
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
    while ((option = getopt(argc, argv, "hV")) != -1)
    {
        switch (option)
        {
        case 'h':
            show_help();
            exit(0);
            break;
        
        case 'V':
            show_version();
            exit(0);
            break;
        
        default:
            fprintf(stderr, "Opción inválida. Asigne la opción -h para obtener ayuda.\n");
            exit(1);
            break;
        }
    }
    
    return 0;
}