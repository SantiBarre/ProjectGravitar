#include "lista.h"
#include <stdlib.h>

typedef struct{
    void *dato;
    nodo_t *sig;
}nodo_t;

struct lista{
    nodo_t *prim;
    size_t cant; // invariante: cant == cantidad de nodos
};

struct lista_iterador{
    nodo_t* ant;
	nodo_t* act;
};

static nodo_t *nodo_crear(void *dato, nodo_t *sig)
{
    nodo_t *n = malloc(sizeof(nodo_t));
    if (n == NULL) return NULL;
    
    n->dato = dato;
    n->sig= sig;
    return n;
}

lista_t *lista_crear(void)
{
    lista_t *l = malloc(sizeof(lista_t));
    if (l == NULL) return NULL;

    l->prim = NULL;
    l->cant = 0;
    return l;
}

bool lista_agregar(lista_t *l, void *dato)
{
    nodo_t *n = nodo_crear(dato, l->prim);
    if (n == NULL) return false;

    l->prim = n;
    l->cant++;
    return true
}

bool lista_agregar_al_final(lista_t *l, void *dato)
{
    nodo_t *n = nodo_crear(dato, NULL);
    if (n == NULL) return false;
    
    if (l->prim == NULL)   // lista vacia
    {        
        l->prim = nuevo_nodo;
    }
    else    // lista no vacia
    {
        nodo_t *act = l->prim;

        while (act->sig != NULL)
        {
            act = act->sig;
        }
        // act->prox es NULL
        // o sea, estamos en el ultimo nodo
        act->sig = n;
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
    nodo_t *act = l->prim, *sig;
    while(actual != NULL)
    {
        destruir_dato(act->dato);
        sig = act->sig;
        free(act);
        act = sig;
    }
    free(l);
}

lista_t *lista_filtrar(lista_t *l, bool (*f)(void *dato, void *extra), void *extra)
{
    lista_t laux = lista_crear;
    if(laux == NULL) return NULL;

    for( lista_iterador_t *li = lista_iterador_crear(l); !lista_iterador_termino(li) ; lista_iterador_siguiente(li)) 
    {
        void *dato = lista_iterador_actual(li);
        if( f(dato, extra) )
        {
            lista_agregar(laux, dato);
            lista_iterador_eliminar(li)
        }
    }
    lista_iterador_destruir(li);
    return laux;
}

lista_iterador_t *lista_iterador_crear(lista_t *l)
{
    lista_iterador_t *li = malloc(sizeof(lista_iterador_t));
    if(li == NULL) return NULL;

    li->ant = NULL;
	li->act = l->prim;
	return li;   
}
    
void lista_iterador_destruir(lista_iterador_t *li)
{
    free(li);
}

void *lista_iterador_actual(const lista_iterador_t *li)
{
    if(li->act == NULL) return NULL;
    return li->act->dato;
}

bool lista_iterador_siguiente(lista_iterador_t *li)
{
    if(lista_iterador_termino(li))return false;

    li->ant = li->act;
    li->act = li->act->sig;

    return true;
}

bool lista_iterador_termino(const lista_iterador_t *li)
{
    if(li->act == NULL) return true;
    return false;
}

void *lista_iterador_eliminar(lista_iterador_t *li)
{
    void *dato = li->act->dato;

    free(li->act);

    li->ant->sig = li->act->sig;
    li->act = li->act->sig;

    return dato;
}

bool lista_iterador_insertar(lista_iterador_t *li, void *dato)
{
    nodo_t *n = nodo_crear(dato, li->act->sig);
    if (n == NULL) return false;

    n->sig = li->act->sig;
    li->act->sig = n;
    
    return true;
}

