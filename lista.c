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



//    crea un nuevo iterador que apunta al primer elemento de la lista l

lista_iterador_t *lista_iterador_crear(lista_t *l);
    

void lista_iterador_destruir(lista_iterador_t *li);.

void *lista_iterador_actual(const lista_iterador_t *li);, devuelve el dato actual del iterador o NULL si el iterador ya se terminó.

bool lista_iterador_siguiente(lista_iterador_t *li);, incrementa el iterador. Devuelve true si la lista aún no se terminó.

bool lista_iterador_termino(const lista_iterador_t *li);, retorna true si el iterador ya llegó al final de la lista.

Y además:

    void *lista_iterador_eliminar(lista_iterador_t *li);, elimina el nodo actual de la lista, devuelve el dato contenido en ella. El iterador automáticamente pasa a apuntar al elemento siguiente.

    bool lista_iterador_insertar(lista_iterador_t *li, void *dato);, inserta un nodo nuevo después de la posición actual. El iterador permanece apuntando el dato actual.
