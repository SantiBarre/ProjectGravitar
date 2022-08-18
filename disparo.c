#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "config.h"
#include "nave.h"
#include "disparo.h"


//Crea un disparo y le aplica direccion dada, ademas pone su cronometro en 10 segs.
disparo_t* disparo_crear_t(torreta_t *t, nave_t *n)
{
    disparo_t *d = malloc(sizeof(disparo_t));
    if (d == NULL ) return NULL;

    //comienza en la misma posicion que la torreta
    for (size_t i = 0; i < 2; i++)
        d->pos[i] = t->pos[i];

    srand(time(NULL));
    float a = -0.4; // es decir -20 grados
    float b = 0.4;

    float random = rand() * (b - a) + a;

    float pendiente = atan2f(n->pos[0] - t->pos[0], n->pos[1] - t->pos[1]);

    float direcion = pendiente + random;

    d->vel[0] = cos(direcion) * VELOCIDAD_DISPARO;
    d->vel[1] = sin(direcion) * VELOCIDAD_DISPARO;

    d->tiempo_vida = 0;
    d->vivo = true;

    return d;
}

disparo_t* disparo_crear_n(nave_t *n)
{
    disparo_t *d = malloc(sizeof(disparo_t));
    if (d == NULL ) return NULL;

    for (size_t i = 0; i < 2; i++)
        d->pos[i] = n->pos[i];

    d->vel[0] = cos(n->dir) * VELOCIDAD_DISPARO;
    d->vel[1] = sin(n->dir) * VELOCIDAD_DISPARO;

    d->tiempo_vida = 0;
    d->vivo = true;

    return d;
}

void disparo_destruir(disparo_t *d)
{
    free(d);
}

