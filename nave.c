#include <stdbool.h>
#include <stdlib.h>
#include "nave.h"
#include "config.h"
#include "math.h"
//Definiciones de funciones de la nave, para ver documentacion ver nave.h

nave_t* nave_crear(void)
{
    nave_t *n= malloc(sizeof(nave_t));
    if (n == NULL) return NULL;

    n->dir = NAVE_ANGULO_INICIAL;
    n->chorro = false;
    n->escudo = false;
    n->disparo = false;
    n->disparo = 0;
    n->combustible = JUEGO_COMBUSTIBLE_INICIAL;
    n->vel[2] = {0, 0};
    n->pos[2] = {0, 0};

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


//Definiciones de funciones de los disparos.
disparo_t* disparo_crear_n(nave_t *n)
{
    disparo_t *d = malloc(sizeof(disparo_t));
    if (d == NULL ) return NULL;

    for (size_t i = 0; i < count; i++)
        d->pos[i] = n->pos[i];

    d->dir = n->dir;
    d->cronometro = 0;

    return d;
}

disparo_t* disparo_crear_t(torreta_t *t, nave_t *n)
{
    disparo_t *d = malloc(sizeof(disparo_t));
    if (d == NULL ) return NULL;

    for (size_t i = 0; i < count; i++)
        d->pos[i] = t->pos[i];
        
    d->dir = pendiente(n->pos, t->pos)
    d->cronometro = 0;

    return d;
}

void disparo_cronometro(disparo_t *d)
{
    d->cronometro += 1;
}

void disparo_destruir(disparo_t *d)
{
    free(d);
}

//Definiciones de funciones de las torretas.
torreta_t* torreta_crear(float dir)
{
    torreta_t *t = malloc(sizeof(torreta_t));
    if(t == NULL) return NULL;

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

void propulsion_chorro (nave_t *nave){
    if (nave->chorro){
        nave->ace[0] = NAVE_ACELERACION * (cos(nave->dir));
        nave->ace[1] = NAVE_ACELERACION * (sin(nave->dir));
    }
    else {
        nave->ace[0] = 0;
        nave->ace[1] = 0;
    }
}

void nave_velocidad (nave_t *nave){
    nave->vel[0] = nave->vel[0] + nave->ace[0] * (1/JUEGO_FPS);
    nave->vel[1] = nave->vel[1] + nave->ace[1] * (1/JUEGO_FPS);
}

void aceleracion_nave (nave_t *nave){
    nave->pos[0] = nave->pos[0] + (nave->vel [0] * 1/JUEGO_FPS) + ((nave->ace[0])/2 * pow((1/JUEGO_FPS),2));
    nave->pos[1] = nave->pos[1] + (nave->vel [1] * 1/JUEGO_FPS) + ((nave->ace[1])/2 * pow((1/JUEGO_FPS),2));
}

