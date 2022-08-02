#include <stdbool.h>
#include <stdlib.h>
#include "nave.h"

//Definiciones de funciones de la nave, para ver documentacion ver nave.h
nave_t* nave_crear(){
    nave_t *nave = malloc(sizeof(nave_t));
    if (nave == NULL) {
        return NULL;
    }
    nave->pos[0] = 0;
    nave->pos[1] = 0;
    nave->vel[0] = 0;
    nave->vel[1] = 0;
    nave->dir = 0;
    nave->chorro = false;
    nave->escudo = false;
    nave->disparo = false;

    return nave;
}
void nave_cambiar_pos(nave_t *nave,float posx, float posy){
    nave->pos[0] = posx;
    nave->pos[1] = posy;
}
void nave_cambiar_vel(nave_t *nave, float velx, float vely){
    nave->vel[0] = velx;
    nave->vel[1] = vely;
}
void nave_cambiar_dir(nave_t *nave, float dir){
    nave->dir = dir;
}
void nave_prender_chorro(nave_t *nave){
    if (nave->chorro){
        nave->chorro = false;
    }
    else {
        nave->chorro = true;
    }
}
void nave_prender_escudo(nave_t *nave){
      if (nave->escudo){
        nave->escudo = false;
    }
    else {
        nave->escudo = true;
    }
}
void nave_disparar(nave_t *nave){
      if (nave->disparo){
        nave->disparo = false;
    }
    else {
        nave->disparo = true;
    }
}
void nave_destruir(nave_t *nave){
    free (nave);
}


//Definiciones de funciones de los disparos.
disparo_t* disparo_crear(float posx,float posy,float dir){
    disparo_t *disparo = malloc(sizeof(disparo_t));
    if (disparo==NULL){
        return NULL;
    }
    disparo->pos[0] = posx;
    disparo->pos[1] = posy;
    disparo->dir = dir;
    disparo->cronometro = 10;

    return disparo;
}
void disparo_cambiar_pos(disparo_t *disparo,float posx,float posy){
    disparo->pos[0] = posx;
    disparo->pos[1] = posy;
}
void disparo_cambiar_dir(disparo_t *disparo,float dir){
    disparo->dir = dir;
}
void disparo_cronometro(disparo_t *disparo,float disminucion){
    disparo->cronometro -= disminucion;
}
void disparo_destruir(disparo_t *disparo){
    free (disparo);
}

//Definiciones de funciones de las torretas.
torreta_t* torreta_crear(float posx,float posy,float dir){
    torreta_t *torreta = malloc(sizeof(torreta_t));
    if (torreta == NULL){
        return NULL;
    }
    torreta->pos[0] = posx;
    torreta->pos[1] = posy;
    torreta->dir = dir;
    torreta->disparo = false;
    return torreta;
}
void torreta_cambiar_pos(torreta_t *torreta,float posx,float posy){
    torreta->pos[0] = posx;
    torreta->pos[1] = posy;
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
