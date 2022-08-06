#ifndef DIBUJADO_H
#define DIBUJADO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "polilinea.h"
#include "figuras.h"
#include "nave.h"

typedef enum{
    INICIO,
    NIVEL1,
    NIVEL2,
    NIVEL3,
    NIVEL4,
    NIVEL5,
}nivel_t;

//Dibuja una polilinea en la esquina arriba a la izquierda de la pantalla,
//donde dice renderer poner "renderer" sin comillas al usarla en el main.
//Para poder trasladarla a una posicion 
bool dibujar_polilinea(const polilinea_t *poli, float escala, float posx, float posy, float ang, SDL_Renderer *renderer);

/**
 * @brief 
 * Dibuja una figura
 * @param fig 
 * @param escala 
 * @param posx 
 * @param posy 
 * @param ang 
 * @param renderer 
 * @return true 
 * @return false 
 */
bool dibujar_figura(figura_t *fig, float escala, float posx, float posy, float ang, SDL_Renderer *renderer);

#endif