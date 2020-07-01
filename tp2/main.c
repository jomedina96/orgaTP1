#include <stdio.h>
#include "archivos.h"
#include "binario.h"

int main(int argc, char* argv[]) {
	//ejecutar_desde_archivo("prueba_rota_5.mem");
	unsigned int test = 243;
	printf("Offset: %d\n", get_offset(test));
    printf("Idx: %d\n", find_set(test));
    printf("Tag: %d\n", get_tag(test));

    return 0;
}
