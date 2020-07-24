#include "archivos.h"
#include "cache.h"

int main(int argc, char* argv[]) {
    if (argc > 2 || argc == 1)  {
        fprintf(stderr, "You need to send an argument for the name of the file\n");
        return 1;
    }
    init();
	bool couldExecute = ejecutar_desde_archivo(argv[1]);
	if (!couldExecute){
	    return 1;
	}
    return 0;
}
