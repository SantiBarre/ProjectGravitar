#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

typedef struct lista lista_t;

lista_t *lista_crear(void);

bool lista_agregar_al_final(lista_t *, void *);

size_t lista_largo(lista_t *);

void lista_destruir(lista_t *, void (*destruir_dato)(void *));

#endif /* LISTA_H */
