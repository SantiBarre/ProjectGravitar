#include "lista.h"
#include <stdlib.h>

struct nodo
{
    void *dato;
    struct nodo *sig;
};

struct lista
{
    struct nodo *prim;
    size_t cant; // invariante: cant == cantidad de nodos
};

struct lista_iterador
{
    struct nodo* ant;
	struct nodo* act;
};



static struct nodo *nodo_crear(void *dato, struct nodo *sig)
{
    struct nodo *n = malloc(sizeof(struct nodo));
    if (n == NULL) return NULL;
    
    n->dato = dato;
    n->sig = sig;

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
    struct nodo *n = nodo_crear(dato, l->prim);
    if (n == NULL) return false;

    l->prim = n;
    l->cant++;

    return true;
}

bool lista_agregar_al_final(lista_t *l, void *dato)
{
    struct nodo *n = nodo_crear(dato, NULL);
    if (n == NULL) return false;
    
    if (l->prim == NULL)   // lista vacia
    {        
        l->prim = n;
    }
    else    // lista no vacia
    {
        struct nodo *act = l->prim;

        while (act->sig != NULL)
        {
            act = act->sig;
        }
        act->sig = n;
    }
    l->cant++;

    return true;
}

size_t lista_largo(lista_t *l)
{
    return l->cant;
}

void lista_destruir(lista_t *l, void (*destruir_dato)(void *)) //CAMBIE void* por figura_t*
{
    struct nodo *act = l->prim;
    
    while(act != NULL)
    {
        destruir_dato(act->dato);
        struct nodo *sig = act->sig;

        free(act);

        act = sig;
    }
    free(l);
}

lista_t *lista_filtrar(lista_t *l, bool (*f)(void *dato, void *extra), void *extra)
{
    lista_t *laux = lista_crear();
    if(laux == NULL) return NULL;

        lista_iterador_t *li = lista_iterador_crear(l);

        while (!lista_iterador_termino(li))
        {

            if( f(li->act->dato, extra))
            {

                li->ant->sig = li->act->sig;

                if(laux->prim == NULL)
                {
                    li->act->sig = NULL;
                }
                else
                {
                    li->act->sig = laux->prim;
                }
                laux->prim = li->act;
                laux->cant++;

            }
            lista_iterador_siguiente(li);
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
    if(lista_iterador_termino(li)) return NULL;
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
    return li->act == NULL;

}

void *lista_iterador_eliminar(lista_iterador_t *li)
{
    void *dato = li->act->dato;

    li->ant->sig = li->act->sig;

    free(li->act);

    li->act = li->ant->sig;

    return dato;
}

bool lista_iterador_insertar(lista_iterador_t *li, void *dato)
{
    struct nodo *n = nodo_crear(dato, li->act->sig);
    if (n == NULL) return false;

    li->act->sig = n;
    
    return true;
}
