#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "logica.h"
#include "polilinea.h"
#include "figuras.h"
#include "nave.h"
#include "config.h"

#define MARGEN_COLISION 20

void volver_inicio(nave_t *n, nivel_t *elegir_nivel)
{
    n->pos[0] = 388;
    n->pos[1] = 218;

    n->vel[0] = 0;
    n->vel[1] = 0;
            
    *elegir_nivel = INICIO;
}

void logica_niveles(nave_t *nave, nivel_t *elegir_nivel, float *contador){

    //float punto_escudo = (nave->pos[0], nave->pos[1] - 30);
    reactor_t* reactor = reactor_crear(815,309);

    if (*elegir_nivel == INICIO) {

        //Posiciones de los planetas
        
        float pos_planeta1[2] = {663, 473};
        float pos_planeta2[2] = {671, 145};
        float pos_planeta3[2] = {110, 79};
        float pos_planeta4[2] = {204, 455};
        float pos_planeta5[2] = {111, 307}; 

        //Interaccion con los planetas
        if(moduloV(nave->pos,pos_planeta1) <= MARGEN_COLISION){
            nave->pos[0] = VENTANA_ANCHO /2;
            nave->pos[1] = 500;
            nave->vel[0] = 0;
            nave->vel[1] = 0;
            *elegir_nivel = NIVEL1;
        }
        if(moduloV(nave->pos,pos_planeta2) <= MARGEN_COLISION){
            nave->pos[0] = VENTANA_ANCHO /2;
            nave->pos[1] = 500;
            nave->vel[0] = 0;
            nave->vel[1] = 0;
            *elegir_nivel = NIVEL2;
        }
        if(moduloV(nave->pos,pos_planeta3) <= MARGEN_COLISION){
            nave->pos[0] = VENTANA_ANCHO /2;
            nave->pos[1] = 500;
            nave->vel[0] = 0;
            nave->vel[1] = 0;
            *elegir_nivel = NIVEL3;
        }
        if(moduloV(nave->pos,pos_planeta4) <= MARGEN_COLISION){
            nave->pos[0] = VENTANA_ANCHO /2;
            nave->pos[1] = 500;
            nave->vel[0] = 0;
            nave->vel[1] = 0;
            *elegir_nivel = NIVEL4;
        }
        if(moduloV(nave->pos,pos_planeta5) <= MARGEN_COLISION){
            nave->pos[0] = VENTANA_ANCHO /2;
            nave->pos[1] = 550;
            nave->vel[0] = 0;
            nave->vel[1] = 0;
            *elegir_nivel = NIVEL5;
        }
    }
    if (*elegir_nivel == NIVEL1) { 
        //Asi se sale del nivel 
        if (nave->pos[1] > VENTANA_ALTO)
            volver_inicio(nave, elegir_nivel);
        
    }
    if (*elegir_nivel == NIVEL2) {
        //Asi se sale del nivel 
        if (nave->pos[1] > VENTANA_ALTO)
            volver_inicio(nave, elegir_nivel);
    }

    if (*elegir_nivel == NIVEL3) {
        //Asi se sale del nivel 
        if (nave->pos[1] > VENTANA_ALTO)
            volver_inicio(nave, elegir_nivel);
    }
    
    if (*elegir_nivel == NIVEL4) {
        //Asi se sale del nivel 
        if (nave->pos[1] > VENTANA_ALTO)
            volver_inicio(nave, elegir_nivel);
    }
    
    if (*elegir_nivel == NIVEL5) {
        //Asi se sale del nivel 
        *contador += 1/100;

        if (*contador >= 25 && !reactor->destruido){
            nave->vidas = nave->vidas -1;
        }
        
        if (nave->pos[1] > VENTANA_ALTO)
            volver_inicio(nave, elegir_nivel);
    }
    reactor_destruir(reactor);
}

lista_t *inicializar_combustibles(void){

    lista_t* combustibles = lista_crear();

    combustible_t *combustible_1 = combustible_crear(1064,13,0);
    combustible_t *combustible_2 = combustible_crear(1685,113,0);
    combustible_t *combustible_3 = combustible_crear(482,94,0);
    combustible_t *combustible_4 = combustible_crear(1751,247,0);
    combustible_t *combustible_5 = combustible_crear(820,46,0);
    combustible_t *combustible_6 = combustible_crear(1196,68,0);
    combustible_t *combustible_7 = combustible_crear(1602,46,0);
    combustible_t *combustible_8 = combustible_crear(188,429,0);
    combustible_t *combustible_9 = combustible_crear(667,600,0);
    combustible_t *combustible_10 = combustible_crear(1054,404,3.14);
    combustible_t *combustible_11 = combustible_crear(574,344,3.14);

    lista_agregar(combustibles,combustible_1);
    lista_agregar(combustibles,combustible_2);
    lista_agregar(combustibles,combustible_3);
    lista_agregar(combustibles,combustible_4);
    lista_agregar(combustibles,combustible_5);
    lista_agregar(combustibles,combustible_6);
    lista_agregar(combustibles,combustible_7);
    lista_agregar(combustibles,combustible_8);
    lista_agregar(combustibles,combustible_9);
    lista_agregar(combustibles,combustible_10);
    lista_agregar(combustibles,combustible_11);

    return combustibles;
}
lista_t *inicializar_torretas(void){
    lista_t* torretas = lista_crear();

    torreta_t *torreta_1 = torreta_crear(-0.66); 
    torreta_t *torreta_2 = torreta_crear(0.66); 
    torreta_t *torreta_3 = torreta_crear(-0.66); 
    torreta_t *torreta_4 = torreta_crear(-0.33); 
    torreta_t *torreta_5 = torreta_crear(0.66); 
    torreta_t *torreta_6 = torreta_crear(2.23); 
    torreta_t *torreta_7 = torreta_crear(0); 
    torreta_t *torreta_8 = torreta_crear(0); 
    torreta_t *torreta_9 = torreta_crear(0); 
    torreta_t *torreta_10 = torreta_crear(0); 
    torreta_t *torreta_11 = torreta_crear(3.14); 
    torreta_t *torreta_12 = torreta_crear (3.14);
    torreta_t *torreta_13 = torreta_crear(0.66); 
    torreta_t *torreta_14 = torreta_crear(2.23); 
    torreta_t *torreta_15 = torreta_crear(0); 
    torreta_t *torreta_16 = torreta_crear(3.8); 
    torreta_t *torreta_17 = torreta_crear(3.8); 
    torreta_t *torreta_18 = torreta_crear(2.23); 
    torreta_t *torreta_19 = torreta_crear(3.8); 
    torreta_t *torreta_20 = torreta_crear(2.23); 

    lista_agregar(torretas,torreta_1);
    lista_agregar(torretas,torreta_2);
    lista_agregar(torretas,torreta_3);
    lista_agregar(torretas,torreta_4);
    lista_agregar(torretas,torreta_5);
    lista_agregar(torretas,torreta_6);
    lista_agregar(torretas,torreta_7);
    lista_agregar(torretas,torreta_8);
    lista_agregar(torretas,torreta_9);
    lista_agregar(torretas,torreta_10);
    lista_agregar(torretas,torreta_11);
    lista_agregar(torretas,torreta_12);
    lista_agregar(torretas,torreta_13);
    lista_agregar(torretas,torreta_14);
    lista_agregar(torretas,torreta_15);
    lista_agregar(torretas,torreta_16);
    lista_agregar(torretas,torreta_17);
    lista_agregar(torretas,torreta_18);
    lista_agregar(torretas,torreta_19);
    lista_agregar(torretas,torreta_20);

    return torretas;
}

/*
void logica_nave(nave_t *nave){

    propulsion_chorro (nave);
    
    nave_velocidad (nave);
    
    aceleracion_nave(nave);
    
}
*/