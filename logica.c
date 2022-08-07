#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "logica.h"
#include "polilinea.h"
#include "figuras.h"
#include "nave.h"
#include "config.h"

#define MARGEN_COLISION 20

void logica_niveles(nave_t *nave, nivel_t elegir_nivel){

                float pos_planeta[5][2] = { {663, 473}, {671, 145}, {110, 79}, {204, 455}, {111, 307} };

            float distancia_planeta;

    switch (elegir_nivel)
    {
        case INICIO : 
            //Posiciones de los planetas

            //Interaccion con los planetas
            for (size_t i = 0; i < 5; i++)
            {
                distancia_planeta = moduloV(nave->pos,pos_planeta[i]);

                if (distancia_planeta <= MARGEN_COLISION)
                {
                    elegir_nivel = i + 1;
                }
                
            }

            //Aparicion de la nave
            break;
        case NIVEL1 : 
            //Asi se sale del nivel 
            printf("Entro NIVEL");
            if (nave->pos[1] > VENTANA_ALTO / ESCALA_MINIMA){
                elegir_nivel = INICIO;
            }
            
            break;
        case NIVEL2 : 
            //Asi se sale del nivel 
                        printf("Entro NIVEL");
            if (nave->pos[1] > VENTANA_ALTO / ESCALA_MINIMA){
                elegir_nivel = INICIO;
            }
            
            break;
        case NIVEL3 : 
            //Asi se sale del nivel 
                        printf("Entro NIVEL");
            if (nave->pos[1] > VENTANA_ALTO / ESCALA_MINIMA){
                elegir_nivel = INICIO;
            }
            
            break;
        case NIVEL4 :
            //Asi se sale del nivel 
                        printf("Entro NIVEL");
            if (nave->pos[1] > VENTANA_ALTO / ESCALA_MINIMA){
                elegir_nivel = INICIO;
            }

            break;
        case NIVEL5 :
                    printf("Entro NIVEL");
            //Asi se sale del nivel 
            if (nave->pos[1] > VENTANA_ALTO / ESCALA_MINIMA){
                elegir_nivel = INICIO;
            }

            break;
    }
}



void logica_nave(nave_t *nave){

    propulsion_chorro (nave);

    nave_velocidad (nave);

    aceleracion_nave(nave);
}