#include <stdlib.h>
#include "lista.h"

typedef struct{
    void *dato;
    struct nodo *sig;
} nodo_t;

struct lista {
    nodo_t *prim;
    size_t cant; // invariante: cant == cantidad de nodos
};

static nodo_t *nodo_crear(void *dato, nodo_t *sig)
{
    nodo_t *n = malloc(sizeof(nodo_t *));
    if (n == NULL) return NULL;
    
    n->dato = dato;
    n->sig = sig;
    return n;
}

lista_t *lista_crear(void)
{
    lista_t *l = malloc(sizeof(lista_t *));
    if (l == NULL) return NULL;

    l->prim = NULL;
    l->cant = 0;
    return l;
}

bool lista_agregar_al_final(lista_t *l, void *dato)
{
    nodo_t *nuevo_nodo = nodo_crear(dato, NULL);
    if (nuevo_nodo == NULL) return false;
    
    if (l->prim == NULL)   // lista vacia
    {        
        l->prim = nuevo_nodo;
    }
    else    // lista no vacia
    {
        nodo_t *actual = l->prim;
        while (actual->sig != NULL)
        {
            actual = actual->sig;
        }
        // act->prox es NULL
        // o sea, estamos en el ultimo nodo
        actual->sig = nuevo_nodo;
    }
    l->cant++;
    return true;
}

size_t lista_largo(lista_t *l)
{
    return l->cant;
}

void lista_destruir(lista_t *l, void (*destruir_dato)(void *))
{
    nodo_t *actual = l->prim, *sig;
    while(actual != NULL)
    {
        destruir_dato(actual->dato);
        sig = actual->sig;
        free(actual);
        
        actual = sig;
    }
    free(l);
}