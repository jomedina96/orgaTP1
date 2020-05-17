#include <stdio.h>
#include <string.h>

#define HELP_COMMAND "-h"
int main(int argc, char* argv[]) {
    if (argc > 7) {
        fprintf(stderr, "Por favor ingrese una cantidad de parametros correcta.\n");
        return 1;
    }
    if (strncmp(HELP_COMMAND, argv[1], strlen(HELP_COMMAND)) == 0) {
        printf("Uso\n conway -h\n");
        return 0;
    }
    return 0;
}