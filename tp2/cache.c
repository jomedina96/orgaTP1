//
// Created by christianflorez on 1/7/20.
//
#include "cache.h"
#include "binario.h"


typedef struct nodo{
    bloqueCache_t* dato;
    struct nodo* prox;
} nodo_t;


struct lista{
    nodo_t* prim;
    nodo_t* ult;
    size_t len;
};

int compare_tag(unsigned int tag, unsigned int set) {
    conjunto_t* conjunto = associative_cache.conjuntos[set];

    int way = 0;
    nodo_t* nodo = conjunto->listaEnlazada->prim;
    while (nodo != NULL) {
        if (nodo->dato->tag == tag && nodo->dato->V == 1) {
            return way;
        }
        way++;
        nodo = nodo->prox;
    }

    return -1;
}

unsigned int select_oldest(unsigned int setnum) {
    conjunto_t* conjunto = associative_cache.conjuntos[setnum];

    nodo_t* nodo = conjunto->listaEnlazada->prim;
    for (int way = 0; way < conjunto->listaEnlazada->len; way++) {
        if (nodo == NULL) return way;
        nodo = nodo->prox;
    }

    return conjunto->listaEnlazada->len - 1;
}

void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set) {
    conjunto_t* conjunto = associative_cache.conjuntos[set];
    nodo_t* nodo = conjunto->listaEnlazada->prim;

    for (int i=0; i <= way; i++) {
        nodo = nodo->prox;
    }

    nodo->dato->datos = memoriaPrincipal.memoria[blocknum];
}

unsigned char read_byte(unsigned int address) {
    unsigned int offset, set, tag, way, blocknum;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);
    way = compare_tag(tag, set);
    if (way == -1) {
        way = select_oldest(set);
        //calcula el bloque de memoria principal
        blocknum = (tag << 3) + set;
        read_tocache(blocknum, way, set);
    }
    conjunto_t* conjunto = associative_cache.conjuntos[set];
    nodo_t* nodo = conjunto->listaEnlazada->prim;

    for (int i=0; i <= way; i++) {
        nodo = nodo->prox;
    }

    //struct way current_way = associative_cache.vias[way];
    //struct conjunto current_set = current_way.conjuntos[set];

    //return current_set[offset];

    return *(nodo->dato->datos)[offset];
}

void write_byte(unsigned int address, unsigned char value) {

    unsigned int offset, set, tag, way, blocknum;

    offset = get_offset(address);
    set = find_set(address);
    tag = get_tag(address);
    way = compare_tag(tag, set);
    if ( way != -1) {
        write_tocache(address, value);
    }
    blocknum = (tag << 3) + set;
    *(memoriaPrincipal.memoria)[blocknum][offset] = value;
}

void init() {
    associative_cache.amount_access = 0;
    associative_cache.amount_misses = 0;
    for (int i=0; i<8; i++) {
        conjunto_t *conjunto = malloc(sizeof(conjunto_t));
        conjunto->listaEnlazada = lista_crear();
        associative_cache.conjuntos[i] = conjunto;
    }

    for (int i=0; i<MAIN_MEMORY_SIZE; i++) {
        memoriaPrincipal.memoria[i] = malloc(sizeof(bloqueDeMemoria_t));
    }
}

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

bool lista_insertar_ultimo(lista_t *lista, bloqueCache_t *dato){
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