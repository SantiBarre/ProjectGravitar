#include "lista.h"
#include <stdio.h>

int main()
{

    int dato[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    lista_t *l = lista_crear();
    if(l == NULL)
    {
        fprintf(stderr, "Error de memoria \n");
        return 1;
    }

    for (size_t i = 0; i < 10; i++)
    {
        printf( " Dato : %d %d \n" , dato[i], lista_agregar(l, &dato[i]));
    }

    for( lista_iterador_t *li = lista_iterador_crear(l) ; !lista_iterador_termino(li); lista_iterador_siguiente(li) )
    {
        int *dato = lista_iterador_actual(li);
        printf( " Dato : %d \n" , *dato);
    }

    return 0;
}