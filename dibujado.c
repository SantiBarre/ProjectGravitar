#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "dibujado.h"
#include "polilinea.h"
#include "figuras.h"
#include "nave.h"
#include "config.h"


bool dibujar_figura(figura_t *fig, float escala, float posx,float posy, SDL_Renderer *renderer){
    for (size_t i=0; i < fig->cantidad_polilineas; i++){
            if (!dibujar_polilinea(fig->polis[i],escala,posx,posy,renderer)){
                perror ("ERROR DE DIBUJADO!");
                return false;
            }
        }
    return true;
}


bool dibujar_polilinea(polilinea_t *polilinea,float escala,float posx,float posy,SDL_Renderer *renderer){
    uint8_t r;
    uint8_t g;
    uint8_t b;
    color_a_rgb(polilinea->color,&r,&g,&b);
    SDL_SetRenderDrawColor(renderer, r, g, b, 0x00);
    for(int i = 0; i < polilinea->n - 1; i++){ 
        if (SDL_RenderDrawLine(
        renderer,
        polilinea->puntos[i][0] * escala + posx,
        -polilinea->puntos[i][1] * escala + (VENTANA_ALTO - posy),
        polilinea->puntos[i+1][0] * escala + posx,
        -polilinea->puntos[i+1][1] * escala + (VENTANA_ALTO - posy)
                ) != 0){
            perror("No se pudo dibujar_polilinea!");
            return false;
        }
    }
    return true;
}

bool dibujar_palabra(int ***palabra,size_t tamanio_palabra,float escala,float posx,float posy,SDL_Renderer *renderer){ 
    SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0xFF, 0x00);
    for (int j = 0; j <= tamanio_palabra; j++){
        int tamanio_letra = sizeof(*palabra) / (sizeof(int) * 2); 
        for(int i = 0; i < tamanio_letra - 1; i++){ 
            if (SDL_RenderDrawLine(
            renderer,
            palabra[j][i][0] * escala + posx,
            -palabra[j][i][1] * escala + (VENTANA_ALTO - posy),
            palabra[j][i+1][0] * escala + posx,
            -palabra[j][i+1][1] * escala + (VENTANA_ALTO - posy)
                    ) != 0){
                perror("No se pudo dibujar_polilinea!");
                return false;
            }
        }
    }
    return true;
}


void dibujado_de_nivel(lista_t *lista_f,nave_t *nave,nivel_t elegir_nivel,SDL_Renderer *renderer){


    //########## ESCALA ##########
    float escala;
    float centro = VENTANA_ANCHO/2;
        if(nave->pos[1] > VENTANA_ALTO * MARGEN_ALTURA)
            escala = VENTANA_ALTO * MARGEN_ALTURA / nave->pos[1];
        if(escala < ESCALA_MINIMA)
            escala = ESCALA_MINIMA;

        if((nave->pos[0] - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
            centro = nave->pos[0] - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
        else if((centro - nave->pos[0]) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
            centro = nave->pos[0] + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
        printf("x:%f y:%f \n",nave->pos[0],nave->pos[1]);
        printf("escala:%f",escala);
        
    if (elegir_nivel == INICIO) { 
        
        //########## DIBUJADO DE INICIO ##########
        /*nave->pos[0] = 388;
        nave->pos[1] = 218; */

        figura_t *base = obtener_figura("BASE",lista_f);
        dibujar_figura (base,1,388,218,renderer);
        figura_t *estrella = obtener_figura("ESTRELLA",lista_f);
        dibujar_figura (estrella,1,457,364,renderer);
        //Si colisiona aca la nave muere y se pierde una vida

        figura_t *planeta1 = obtener_figura("PLANETA1",lista_f);
        dibujar_figura (planeta1,1,663,473,renderer);


        figura_t *planeta2 = obtener_figura("PLANETA2",lista_f);
        dibujar_figura (planeta2,1,671,145,renderer);


        figura_t *planeta3 = obtener_figura("PLANETA3",lista_f);
        dibujar_figura (planeta3,1,110,79,renderer);


        figura_t *planeta4 = obtener_figura("PLANETA4",lista_f);
        dibujar_figura (planeta4,1,204,455,renderer);
        

        figura_t *planeta5 = obtener_figura("PLANETA5",lista_f);
        dibujar_figura (planeta5,1,111,307,renderer);

        //########## INTERACCIONES DE INICIO ##########

        
    }

    if (elegir_nivel == NIVEL1) {
        figura_t *nivel1ne = obtener_figura("NIVEL1NE",lista_f);
        //Es infinito
        dibujar_figura (nivel1ne,escala,0,0,renderer);
        dibujar_figura (nivel1ne,escala,2000,0,renderer);
        dibujar_figura (nivel1ne,escala,-2000,0,renderer);
        //dos objetos no pueden usar la misma polilinea si esa se debe de rotar, asi que hay que cambiarlo
        //2 combustibles y 2 torretas
    }

    if (elegir_nivel == NIVEL2) {
        figura_t *nivel1se = obtener_figura("NIVEL1SE",lista_f);
        //Es infinito
        dibujar_figura (nivel1se,escala,0,0,renderer);
        dibujar_figura (nivel1se,escala,2087,0,renderer);
        dibujar_figura (nivel1se,escala,-2087,0,renderer);
        //2 combustibles y 4 torretas
    }

    if (elegir_nivel == NIVEL3) {
        figura_t *nivel1sw = obtener_figura("NIVEL1SW",lista_f);
        //Es infinito
        dibujar_figura (nivel1sw,escala,0,0,renderer);
        dibujar_figura (nivel1sw,escala,1790,0,renderer);
        dibujar_figura (nivel1sw,escala,-1790,0,renderer);
        //3 combustibles y 6 torretas
    }

    if (elegir_nivel == NIVEL4) {
        figura_t *nivel1nw = obtener_figura("NIVEL1NW",lista_f);
        dibujar_figura (nivel1nw,escala,0,0,renderer);
        //4 combustibles Y 8 torretas
    }

    if (elegir_nivel == NIVEL5) {
        figura_t *nivel1r = obtener_figura("NIVEL1R",lista_f);
        dibujar_figura (nivel1r,escala,0,0,renderer);
        figura_t *reactor = obtener_figura("REACTOR",lista_f);
        dibujar_figura (reactor,escala,815,309,renderer);
        
    }
}


void dibujado_de_nave(lista_t *lista_f,nave_t *nave,SDL_Renderer *renderer){

    figura_t *nave_fig;

    if (nave->chorro)
    {
        nave_fig = obtener_figura("NAVE+CHORRO",lista_f);
    }
    else
    {
        nave_fig = obtener_figura ("NAVE",lista_f);
    }


    figura_t *aux = figura_mov(nave_fig,0,0,nave->dir);  
    dibujar_figura(aux,1,nave->pos[0],nave->pos[1],renderer);
    figura_destruir(aux);
}

/*void dibujado_de_nave(lista_t *lista_f,nave_t *nave,SDL_Renderer *renderer){

    figura_t *nave_fig = obtener_figura ("NAVE",lista_f);
    figura_t *nave_fig2 = obtener_figura("NAVE+CHORRO",lista_f);
        if (nave->chorro){
            figura_t *aux = figura_mov(nave_fig,nave->pos[0],nave->pos[1],nave->dir);  
            dibujar_figura(aux,1,nave->pos[0],nave->pos[1],renderer);  
            figura_destruir(aux);
        }
        else {
            figura_t *aux = figura_mov(nave_fig2,nave->pos[0],nave->pos[1],nave->dir);  
            dibujar_figura(aux,1,nave->pos[0],nave->pos[1],renderer);
            figura_destruir(aux);
        }
    free(nave_fig);
    free(nave_fig2);
}*/