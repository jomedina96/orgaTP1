#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

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
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un elemento al final de la lista. Devuelve Falso en caso de error.
// Pre: La lista fue creada
// Post: Se ha agregado un elemento al final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

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
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

// ITERADOR INTERNO

// Itera la lista, aplicandole visitar a todos los elementos de la lista.
// Pre: La lista fue creada, visitar es una funcion bool que recibe el dato, y un extra
// Post: Se le aplico visitar a todos los elementos hasta que visitar devolvio False.
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);

// ITERADOR EXTERNO
// Crea iterador externo. 
// Pre: Lista fue creada.
// Post: Se ha devuelto un iterador apuntando al primer elemento de la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza el iterador por la lista
// Devuelve false en caso de encontrarse al final.
// Pre: El iterador fue creado
// Post: El iterador se encuentra una posicion adelante de la lista.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el dato del elemento apuntado por el iterador. NULL en caso de encontrarse al final
// Pre: El iterador fue creado.
// Post: Se ha devuelto el dato del elemento apuntado por el iterador.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve True en caso de encontrarse al final de la lista. False en caso contrario
// Pre: El iterador fue creado.
// Post: Se ha devuelto un booleano indicando  si el iterador se encuentra al final de la lista.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: El iterador fue creado.
// Post: Se ha destruido el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta elemento en la posicion del iterador. Devuelve False en caso de error
// Pre: El iterador fue creado.
// Post: Se ha añadido un elemento a la lista.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra elemento en la posicion del iterador. Devuelve NULL en caso de encontrarse al final.
// Pre: El iterador fue creado
// Post: Se ha devuelvo el dato del elemento apuntado y se ha eliminado el elemento de la lista.
void *lista_iter_borrar(lista_iter_t *iter);


// PRUEBAS ALUMNO
void pruebas_lista_alumno(void);
#endif
