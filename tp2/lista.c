#include "lista.h"
#include <stdlib.h>

typedef struct nodo{
    bloqueCache_t* dato;
	struct nodo* prox;
} nodo_t;


struct lista{
	nodo_t* prim;
	nodo_t* ult;
	size_t len;
};

nodo_t* crear_nodo(bloqueCache_t* valor){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (!nodo) return NULL;

	nodo->dato = valor;
	nodo->prox = NULL;

	return nodo;
}

lista_t *lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	if (lista==NULL) return NULL;
	lista->prim = NULL;
	lista->ult = NULL;
	lista->len = 0;
	return lista;
}

void lista_destruir(lista_t *lista){
	while (!(lista_esta_vacia(lista))){
		lista_borrar_primero(lista);
	}
	free(lista);
}


void *lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	void* dato = lista->prim->dato;
	nodo_t* prox_nodo = lista->prim->prox;
	free(lista->prim);
	lista->prim = prox_nodo;
	if (prox_nodo == NULL) 
		lista->ult = NULL;
	lista->len--;
	return dato;
}

bool lista_insertar_primero(lista_t *lista, bloqueCache_t* dato){
	nodo_t* nodo = crear_nodo(dato);
	if (nodo == NULL) return false;
	nodo_t* nodo_prim = lista->prim;
	nodo->prox = nodo_prim;
	lista->prim = nodo;
	if (nodo_prim == NULL) lista->ult = nodo;
	lista->len++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, bloqueCache_t* dato){
	nodo_t* nodo = crear_nodo(dato);
	if (nodo == NULL) return false;
	nodo_t* nodo_ult = lista->ult;
	if (nodo_ult == NULL){
		lista->prim = nodo;
	}
	else{
		nodo_ult->prox = nodo;
	}
	lista->ult = nodo;
	lista->len++;
	return true;
}

bool lista_esta_vacia(const lista_t *lista){
	return lista->len == 0;
}

size_t lista_largo(const lista_t *lista){
	return lista->len;
}

void *lista_ver_primero(const lista_t *lista){
	if (lista_esta_vacia(lista)) return NULL;
	return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if (lista_esta_vacia(lista)) return NULL;
	return lista->ult->dato;
}
