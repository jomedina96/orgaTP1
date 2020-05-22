/* Inclusión de archivos */
#include <stdio.h>
#include <stdlib.h>
#define DEAD_CELL '0'

void imprimir(char* matriz, int filas, int columnas) /* Función donde se ejecuta la lógica del programa */
{
	 for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++){
            printf("%c", *(matriz));
			printf(" ");
            matriz = matriz + 1;
		}
        printf("\n");
    }
	return; /* sale de la función */
}

int add(int first_pos, int second_pos, char* inicio) {
    char first_value = *(first_pos + inicio);
    char second_value = *(second_pos + inicio);
    return  first_value + second_value - DEAD_CELL - DEAD_CELL;
}

int* encontrarLaterales(int pos_referencia, int col_actual, int max_col) {
    printf("Calculo laterales \n");
    int* laterales = malloc(2*sizeof(int));
    if (col_actual != 0 && col_actual != (max_col -1)) {
        laterales[0] = pos_referencia - 1;
        laterales[1] = pos_referencia + 1;
    } else {
        if (col_actual == 0) {
            laterales[0] = pos_referencia + max_col - 1;
            laterales[1] = pos_referencia + 1;
        } else {
            laterales[0] = pos_referencia - 1;
            laterales[1] = pos_referencia - max_col + 1;
        }
    }
    printf("%d\n", laterales[0]);
    printf("%d\n", laterales[1]);
    return laterales;
}


int* encontrarPerimetro(int pos_referencia, int pos_fil, int pos_col, int max_fila, int max_col) {
    //int perimetroCalculado[8]; //[izq, derecha, arriba, abajo, arriba_izq, arriba_der, abajo_izq, abajo_der]
    int* perimetroCalculado =  malloc(8*sizeof(int));
    int superior;
    int inferior;
    int* lateralesCentro;
    int* lateralesSuperior;
    int* laterealesInferior;

    lateralesCentro = encontrarLaterales(pos_referencia, pos_col, max_col);
    
    if (pos_fil > 0 && pos_fil < max_fila - 1) {
        superior = pos_referencia - max_col;
        lateralesSuperior = encontrarLaterales(superior, pos_col, max_col);
        inferior = pos_referencia + max_col;
        laterealesInferior = encontrarLaterales(inferior, pos_col, max_col);
    } else {
        if (pos_fil == 0) {
            superior = pos_referencia + max_col*(max_fila - 1);
            lateralesSuperior = encontrarLaterales(superior, pos_col, max_col);
            inferior = pos_referencia + max_col;
            laterealesInferior = encontrarLaterales(inferior, pos_col, max_col);
        } else {
            superior = pos_referencia - max_col;
            lateralesSuperior = encontrarLaterales(superior, pos_col, max_col);
            inferior = pos_referencia - max_col * (max_fila - 1);
            laterealesInferior = encontrarLaterales(inferior, pos_col, max_col);
        }
    }
    perimetroCalculado[0] = superior;
    perimetroCalculado[1] = inferior;
    perimetroCalculado[2] = lateralesCentro[0];
    perimetroCalculado[3] = lateralesCentro[1];
    perimetroCalculado[4] = lateralesSuperior[0];
    perimetroCalculado[5] = lateralesSuperior[1];
    perimetroCalculado[6] = laterealesInferior[0];
    perimetroCalculado[7] = laterealesInferior[1];
    return perimetroCalculado;
} 

int vecinos(char* a, int i, int j, int M, int N) {
    int pos_referencia =  i * N + j;

    int* perimetro = encontrarPerimetro(pos_referencia, i, j, M, N);
    int max_filas = (sizeof(perimetro)/sizeof(perimetro[0]));
    printf("max_filas: ");
    printf("%d\n", max_filas);

    int contador = 0;
    for (int pos = 0; pos < 8; pos++) {
        printf("%d\n", perimetro[pos]);
        contador += *(perimetro[pos] + a) - DEAD_CELL;
    } 

    return contador; 

}

/*int vecinos(char* a, int i, int j, int M, int N) {
    
    int pos_referencia =  i * N + j; /*fila * numero de columnas + columna 
    int pos_sup = pos_referencia - N;
    int pos_inf = pos_referencia + N;
    int pos_izq = pos_referencia - 1;
    int pos_der = pos_referencia + 1;
    int pos_sup_izq = pos_sup - 1;
    int pos_sup_der = pos_sup + 1;
    int pos_inf_izq = pos_inf - 1;
    int pos_inf_der = pos_inf + 1;

    int suma_horizontal = add(pos_der, pos_izq, a);
    int suma_vertical = add(pos_inf, pos_sup, a);
    int suma_diagonal_der = add(pos_sup_der, pos_inf_izq, a);
    int suma_diagonal_izq = add(pos_sup_izq, pos_inf_der, a);

    int cantidad_de_vecinos = suma_horizontal + suma_vertical + suma_diagonal_der + suma_diagonal_izq;
    
    return cantidad_de_vecinos;
}*/

int main() {

    char glider[5][4] = {{'0','0','1','0'},{'1','0','1','0'},{'1','1','0','1'},{'0','1','1','0'},{'0','0','0','0'}};
    int max_filas = (sizeof(glider)/sizeof(glider[0]));
    int max_columnas = (sizeof(glider[0])/sizeof(glider[0][0]));
    imprimir(glider, max_filas, max_columnas);
    int result = vecinos(glider, 2, 3, max_filas, max_columnas);
    printf("cantidad de vecinos vivos: ");
    printf("%d\n", result);
    /*for (int i = 0; i < max_filas; i++) {
        for (int j = 0; j < max_columnas; j++){
            vecinos(glider, i, j, max_filas, max_columnas);
		}
    }*/
}