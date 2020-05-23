#include "neighbors.h"

void showNeighborhood(char* neighborhood, int rowsSize, int columnsSize)
{
	 for (int i = 0; i < rowsSize; i++) {
        for (int j = 0; j < columnsSize; j++){
            printf("%c", *(neighborhood));
			printf(" ");
            neighborhood = neighborhood + 1;
		}
        printf("\n");
    }
	return;
}

/*
int main(int argc, char* argv[]) {
    char glider[5][4] = {{'0','0','1','0'},{'1','0','1','0'},{'1','1','0','1'},{'0','1','1','0'},{'0','0','0','0'}};
    int rowsSize = (sizeof(glider)/sizeof(glider[0]));
    int columnsSize = (sizeof(glider[0])/sizeof(glider[0][0]));
    showNeighborhood(glider, rowsSize, columnsSize);
    int liveNeighbors = vecinos(glider, 2, 3, rowsSize, columnsSize);
    printf("cantidad de vecinos vivos: ");
    printf("%d\n", liveNeighbors);
}
*/