#include "lista.h"
#include <stdlib.h>

typedef struct nodo{
	void* dato;
	struct nodo* prox;
} nodo_t;


struct lista{
	nodo_t* prim;
	nodo_t* ult;
	size_t len;
};

struct lista_iter{
	nodo_t* ant;
	nodo_t* act;
	lista_t* lista;
};

nodo_t* crear_nodo(void* valor){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL) return NULL;
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

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
	void* dato;
	while (!(lista_esta_vacia(lista))){
		dato = lista_borrar_primero(lista);
		if (destruir_dato != NULL){
			destruir_dato(dato);
		}
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

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nodo = crear_nodo(dato);
	if (nodo == NULL) return false;
	nodo_t* nodo_prim = lista->prim;
	nodo->prox = nodo_prim;
	lista->prim = nodo;
	if (nodo_prim == NULL) lista->ult = nodo;
	lista->len++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
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

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra){
	nodo_t* nodo_act = lista->prim;
	nodo_t* nodo_sig;
	while (nodo_act != NULL){
		nodo_sig = nodo_act->prox;
		void* nodo_dato = nodo_act->dato;
		if (!(visitar(nodo_dato,extra))) break;
		nodo_act = nodo_sig;
	}
}


lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if (iter == NULL) return NULL;
	iter->ant = NULL;
	iter->act = lista->prim;
	iter->lista = lista;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if (iter->act == NULL) return false;
	iter->ant = iter->act;
	iter->act = iter->act->prox;
	return true;
}
void *lista_iter_ver_actual(const lista_iter_t *iter){
	if (iter->act == NULL) return NULL;
	return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return iter->act == NULL;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	nodo_t* nodo = crear_nodo(dato);
	if (nodo == NULL) return false;
	nodo->prox = iter->act;
	if (iter->ant == NULL){
		iter->lista->prim = nodo;		
	}
	if (iter->act == NULL){
		iter->lista->ult = nodo;
	}
	if (iter->ant){
		iter->ant->prox = nodo;
	}
	iter->lista->len++;
	iter->act = nodo;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
	if (iter->act == NULL) return NULL;
	void* dato = iter->act->dato;
	if (iter->ant == NULL){
		iter->lista->prim = iter->act->prox;
	}
	if (iter->act->prox == NULL) {
		iter->lista->ult = iter->ant;
	}
	if (iter->ant){
		iter->ant->prox = iter->act->prox;

	}
	nodo_t* viejoact = iter->act;
	iter->act = iter->act->prox;
	free(viejoact);
	iter->lista->len--;
	return dato;
}
