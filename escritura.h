#ifndef ESCRITURA_H
#define ESCRITURA_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "nave.h"

bool dibujar_texto(char *texto, bool color, float escala, float posx, float posy, SDL_Renderer *renderer);

bool textos(nave_t *n,  SDL_Renderer *renderer);

bool punto_mundo(SDL_Renderer *renderer);

bool punto_del_mundo(int puntos, SDL_Renderer *renderer);

#endif