#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>
#include "cache.h"

struct lista;
struct lista_iter;
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

//PRIMITIVAS LISTA ENLAZADA

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
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Devuelve el primer elemento de la lista. Devuelve NULL en caso de no haber elementos.
// Pre: La lista fue creada 
// Post: se devolvio el primer elemento de la lista
void *lista_ver_primero(const lista_t *lista);

// Devuelve el ultimo elemento de la lista. Devuelve NULL en caso de no haber elementos.
// Pre: La lista fue creada
// Post: Se devolvio el ultimo elemento de la lista
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista enlazada.
// Pre: La lista fue creada.
// Post: Se devolvio el largo de la lista enlazada
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parametro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista);

#endif
