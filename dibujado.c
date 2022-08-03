#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "polilinea.h"
#include "figuras.h"

bool dibujar_polilinea(polilinea_t *polilinea,float escala,SDL_Renderer *renderer){
    uint8_t r;
    uint8_t g;
    uint8_t b;
    color_a_rgb(polilinea->color,&r,&g,&b);
    SDL_SetRenderDrawColor(renderer, r, g, b, 0x00);
    for(int i = 0; i < polilinea->n - 1; i++){ 
        if (SDL_RenderDrawLine(
        renderer,
        polilinea->puntos[i][0] * escala,
        -polilinea->puntos[i][1] * escala,
        polilinea->puntos[i+1][0] * escala,
        -polilinea->puntos[i+1][1] * escala 
                ) != 0){
            return false;
        }
    }
    return true;
}
