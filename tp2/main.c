#include <stdio.h>
#include "archivos.h"
#include "cache.h"

int main(int argc, char* argv[]) {
    init();
	bool couldExecute = ejecutar_desde_archivo(argv[1]);
	if (!couldExecute){
	    return 1;
	}
    return 0;
}
