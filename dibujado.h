#ifndef DIBUJADO_H
#define DIBUJADO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "polilinea.h"
#include "figuras.h"
#include "nave.h"
#include "config.h"

//Dibuja una polilinea en la esquina arriba a la izquierda de la pantalla,
//donde dice renderer poner "renderer" sin comillas al usarla en el main.
//Para poder trasladarla a una posicion 

bool dibujar_polilinea(polilinea_t *polilinea,float escala,float posx,float posy,SDL_Renderer *renderer);

bool dibujar_figura(figura_t *fig, float escala, float posx, float posy, SDL_Renderer *renderer );

bool dibujar_palabra(int ***palabra,size_t tamanio_palabra,float escala,float posx,float posy,SDL_Renderer *renderer);

void dibujado_de_nivel(lista_t *lista_f,nivel_t elegir_nivel,SDL_Renderer *renderer);

void dibujado_de_nave(lista_t *lista_f,nave_t *nave,SDL_Renderer *renderer);

#endif