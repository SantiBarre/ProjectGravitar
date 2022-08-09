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
    n->dir = n->dir - NAVE_ROTACION_PASO;
}

void nave_izquieda(nave_t *n)
{
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

bool nave_muerta(nave_t *n)
{
    if(n->vidas <= 0)
        return true;
    return false;
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

static void rp_torreta_destruir (torreta_t * torreta){
    free(torreta);
}

void torreta_destruir(void *torreta)
{
    rp_torreta_destruir((torreta_t *)torreta);
}

combustible_t* combustible_crear(float posx,float posy,float dir){
    combustible_t* aux = malloc (sizeof(combustible_t));
    if(aux == NULL) return NULL;

    aux->pos[0] = posx;
    aux->pos[1] = posy;
    aux->dir = dir;

    aux->uso = false;
    return aux;
}

void combustible_usar(combustible_t* combus){
    combus->uso = true;
}

static void rp_combustible_destruir(combustible_t* combus){
    free (combus);
}

void combustible_destruir(void *combus)
{
    rp_combustible_destruir((combustible_t *)combus);
}

reactor_t *reactor_crear(float posx,float posy){
    reactor_t* aux = malloc (sizeof(reactor_t));
    if(aux == NULL) return NULL;

    aux->pos[0] = posx;
    aux->pos[1] = posy;

    aux->destruido = false;

    return aux;

}

void reactor_d(reactor_t * r){
    r->destruido = true;
}

static void rp_reactor_destruir(reactor_t * r){
    free (r);
}

void reactor_destruit(void *r){
    rp_reactor_destruir((reactor_t *)r);
}