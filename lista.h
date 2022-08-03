#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

typedef struct{
    void *dato;
    struct nodo *sig;
}nodo_t;

typedef struct{
    struct nodo *prim;
    size_t cant; // invariante: cant == cantidad de nodos
}lista_t;

typedef struct{
    struct nodo* ant;
	struct nodo* act;
}lista_iterador_t;


lista_t *lista_crear(void);

bool lista_agregar(lista_t *l, void *dato);

bool lista_agregar_al_final(lista_t *l, void *dato);

size_t lista_largo(lista_t *l);

void lista_destruir(lista_t *l, void (*destruir_dato)(void *));

lista_t *lista_filtrar(lista_t *l, bool (*f)(void *dato, void *extra), void *extra);

lista_iterador_t *lista_iterador_crear(lista_t *l);

void lista_iterador_destruir(lista_iterador_t *li);

void *lista_iterador_actual(const lista_iterador_t *li); //CAMBIO ACA PARA PROBAR

bool lista_iterador_siguiente(lista_iterador_t *li);

bool lista_iterador_termino(const lista_iterador_t *li);

void *lista_iterador_eliminar(lista_iterador_t *li);

bool lista_iterador_insertar(lista_iterador_t *li, void *dato);

#endif /* LISTA_H */
