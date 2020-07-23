#ifndef TP2_CACHE_H
#define TP2_CACHE_H
#include "binario.h"
#include <stdlib.h>
#include <stdbool.h>

#define CACHE_BLOCK_SIZE 128
#define MAIN_MEMORY_SIZE 512


struct lista;
typedef struct lista lista_t;
typedef unsigned char bloqueDeMemoria_t[CACHE_BLOCK_SIZE];

typedef struct bloqueCache {
    int V;
    int tag;
    bloqueDeMemoria_t* datos;
} bloqueCache_t;

typedef struct memoriaPrincipal {
    bloqueDeMemoria_t* memoria[MAIN_MEMORY_SIZE];
} memoriaPrincipal_t;


typedef struct conjunto {
    lista_t* listaEnlazada;
} conjunto_t;

typedef struct cache {
    int amount_access;
    int amount_misses;
    conjunto_t* conjuntos[8];
} cache_t;

cache_t associative_cache;
memoriaPrincipal_t memoriaPrincipal;

unsigned char read_byte(unsigned int address);
void write_byte(unsigned int address, unsigned char value);
float get_miss_rate();
int compare_tag(unsigned int tag, unsigned int set);
unsigned int select_oldest(unsigned int setnum);
void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set);
void write_tocache(unsigned int address, unsigned char value);

void init();

// ------------------------------------

// Crea una lista enlazada.
// Post: devuelve una nueva lista enlazada vacía.
lista_t *lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos.
// Pre: la lista enlazada fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un elemento al principio de la lista. Devuelve Falso en caso de error.
// Pre: La lista fue creada
// Post: Se ha agrego un elemento al principio de la lista.
bool lista_insertar_primero(lista_t *lista, bloqueCache_t* dato);

// Agrega un elemento al final de la lista. Devuelve Falso en caso de error.
// Pre: La lista fue creada
// Post: Se ha agregado un elemento al final de la lista.
bool lista_insertar_ultimo(lista_t *lista, bloqueCache_t* dato);

// Saca el primer elemento de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se borro el primer elemento de la lista
void lista_borrar_primero(lista_t *lista);

// Devuelve el primer elemento de la lista. Devuelve NULL en caso de no haber elementos.
// Pre: La lista fue creada
// Post: se devolvio el primer elemento de la lista
bloqueCache_t *lista_ver_primero(const lista_t *lista);

// Devuelve el ultimo elemento de la lista. Devuelve NULL en caso de no haber elementos.
// Pre: La lista fue creada
// Post: Se devolvio el ultimo elemento de la lista
bloqueCache_t *lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista enlazada.
// Pre: La lista fue creada.
// Post: Se devolvio el largo de la lista enlazada
size_t lista_largo(const lista_t *lista);

// Destruye la lista.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista);

#endif //TP2_CACHE_H
