#include <stdbool.h>
#include <stdlib.h>
#include "nave.h"
#include "config.h"
#include "math.h"
//Definiciones de funciones de la nave, para ver documentacion ver nave.h
nave_t* nave_crear(){
    nave_t *nave = malloc(sizeof(nave_t));
    if (nave == NULL) {
        return NULL;
    }
    nave->vel[0] = 0;
    nave->vel[1] = 0;
    nave->dir = 0;
    nave->chorro = false;
    nave->escudo = false;
    nave->disparo = false;

    return nave;
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
disparo_t* disparo_crear(float dir){
    disparo_t *disparo = malloc(sizeof(disparo_t));
    if (disparo==NULL){
        return NULL;
    }
    disparo->dir = dir;
    disparo->cronometro = 10;

    return disparo;
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
torreta_t* torreta_crear(float dir){
    torreta_t *torreta = malloc(sizeof(torreta_t));
    if (torreta == NULL){
        return NULL;
    }
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

void propulsion_chorro (nave_t *nave,float *acex,float *acey){
    if (nave->chorro){
        *acex = NAVE_ACELERACION * (cos(nave->dir));
        *acey = NAVE_ACELERACION * (sin(nave->dir));
    }
    else {
        *acex = 0;
        *acey = 0;
    }
}

void nave_velocidad (nave_t *nave,float acex,float acey){
    nave->vel[0] = nave->vel[0] + acex * (1/JUEGO_FPS);
    nave->vel[1] = nave->vel[1] + acey * (1/JUEGO_FPS);
}

void aceleracion_nave (nave_t *nave,float acex,float acey){
    nave->pos[0] = nave->pos[0] + (nave->vel [0] * 1/JUEGO_FPS) + (acex/2 * pow((1/JUEGO_FPS),2));
    nave->pos[1] = nave->pos[1] + (nave->vel [1] * 1/JUEGO_FPS) + (acex/2 * pow((1/JUEGO_FPS),2));
}

