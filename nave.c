#include <stdbool.h>
#include <stdlib.h>
#include "nave.h"
#include "config.h"
#include "math.h"

#define DISPAROS_X_SEG 1
//Definiciones de funciones de la nave, para ver documentacion ver nave.h

nave_t* nave_crear(void)
{
    nave_t *n= malloc(sizeof(nave_t));
    if (n == NULL) return NULL;

    n->dir = NAVE_ANGULO_INICIAL;

    //Variables logicas
    n->chorro = false;
    n->escudo = false;
    n->disparo = false;

    //contador de tiempo de disparos en 0
    n->disparo = 0;

    //Cantidad de vidas de la nave
    n->vidas = 3;

    //Combustible de la nave
    n->combustible = JUEGO_COMBUSTIBLE_INICIAL;

    n->vel[0] = 0;
    n->vel[1] = 0;

    n->pos[0] = 388;
    n->pos[1] = 218;


    return n;
}


void nave_derecha(nave_t *n)
{
    if(n->dir < 0)
        n->dir = PI - NAVE_ROTACION_PASO;
    else
        n->dir = n->dir - NAVE_ROTACION_PASO;
}

void nave_izquieda(nave_t *n)
{
    if(n->dir > PI)
        n->dir = NAVE_ROTACION_PASO;
    else
        n->dir = n->dir + NAVE_ROTACION_PASO;
}

void nave_chorro(nave_t *n, bool on_off)
{
    n->chorro = on_off;
    if(n->chorro)
        n->combustible -= (float)JUEGO_COMBUSTIBLE_POT_X_SEG / JUEGO_FPS;
}


void nave_escudo(nave_t *n, bool on_off)
{
    n->escudo = on_off;
    if(n->escudo)
        n->combustible -= (float)JUEGO_COMBUSTIBLE_ESC_X_SEG / JUEGO_FPS;
}

void nave_disparar(nave_t *n, bool on_off)
{   
    if(on_off)
    {
        if (n->tiempo_disparo >= JUEGO_FPS / DISPAROS_X_SEG)
        {
            n->disparo = on_off;
            n->tiempo_disparo = 0;
        }
    }
    n->tiempo_disparo++;
}

void nave_destruir(nave_t *nave)
{
    free (nave);
}


//Definiciones de funciones de las torretas.
torreta_t* torreta_crear(float dir)
{
    torreta_t *torreta = malloc(sizeof(torreta_t));
    if(torreta == NULL) return NULL;

    torreta->dir = dir;
    torreta->disparo = false;
    return torreta;
}

void torreta_cambiar_dir(torreta_t *torreta,float dir){
    torreta->dir = dir;
}

void torreta_disparar(torreta_t *torreta){
      if (torreta->disparo){
        torreta->disparo = false;
    }
    else {
        torreta->disparo = true;
    }
}

