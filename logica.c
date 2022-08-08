#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "logica.h"
#include "polilinea.h"
#include "figuras.h"
#include "nave.h"
#include "config.h"

#define MARGEN_COLISION 20

void logica_niveles(nave_t *nave, nivel_t *elegir_nivel){


    if (*elegir_nivel == INICIO) {

        //Posiciones de los planetas
        
        float pos_planeta1[2] = {663, 473};
        float pos_planeta2[2] = {671, 145};
        float pos_planeta3[2] = {110, 79};
        float pos_planeta4[2] = {204, 455};
        float pos_planeta5[2] = {111, 307}; 

        //Interaccion con los planetas
        if(moduloV(nave->pos,pos_planeta1) <= MARGEN_COLISION){
            *elegir_nivel = NIVEL1;
        }
        if(moduloV(nave->pos,pos_planeta2) <= MARGEN_COLISION){
            *elegir_nivel = NIVEL2;
        }
        if(moduloV(nave->pos,pos_planeta3) <= MARGEN_COLISION){
            *elegir_nivel = NIVEL3;
        }
        if(moduloV(nave->pos,pos_planeta4) <= MARGEN_COLISION){
            *elegir_nivel = NIVEL4;
        }
        if(moduloV(nave->pos,pos_planeta5) <= MARGEN_COLISION){
            *elegir_nivel = NIVEL5;
        }


    }
    if (*elegir_nivel == NIVEL1) { 
        //Asi se sale del nivel 
        if (nave->pos[1] > VENTANA_ALTO / ESCALA_MINIMA){
            *elegir_nivel = INICIO;
        }
        
    }
    if (*elegir_nivel == NIVEL2) {
        //Asi se sale del nivel 
        if (nave->pos[1] > VENTANA_ALTO / ESCALA_MINIMA){
            *elegir_nivel = INICIO;
        }
    }

    if (*elegir_nivel == NIVEL3) {
        //Asi se sale del nivel 
        if (nave->pos[1] > VENTANA_ALTO / ESCALA_MINIMA){
            *elegir_nivel = INICIO;
        }
    }
    
    if (*elegir_nivel == NIVEL4) {
        //Asi se sale del nivel 
        if (nave->pos[1] > VENTANA_ALTO / ESCALA_MINIMA){
            *elegir_nivel = INICIO;
        }

    }
    
    if (*elegir_nivel == NIVEL5) {
        //Asi se sale del nivel 
        if (nave->pos[1] > VENTANA_ALTO / ESCALA_MINIMA){
            *elegir_nivel = INICIO;
        }
        
    }
    
}
/*
void logica_nave(nave_t *nave){

    propulsion_chorro (nave);
    
    nave_velocidad (nave);
    
    aceleracion_nave(nave);
    
}
*/