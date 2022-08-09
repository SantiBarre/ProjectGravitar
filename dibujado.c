<<<<<<< HEAD
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


void dibujado_de_nivel(lista_t *lista_f,lista_t *lista_combus,lista_t *lista_torr,nave_t *nave,nivel_t elegir_nivel,SDL_Renderer *renderer){

    figura_t *combustible = obtener_figura("COMBUSTIBLE",lista_f);
    figura_t *torr_fig = obtener_figura("TORRETA",lista_f);

    //########## ESCALA ##########
    float escala = 1;
    float centro = VENTANA_ANCHO/2;
    
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
        calculo_escala(&escala,&centro,nave);
        
        dibujar_figura (nivel1ne,escala,0 -centro + VENTANA_ANCHO / 2 / escala,0,renderer);
        dibujar_figura (nivel1ne,escala,0 -centro + VENTANA_ANCHO / 2 / escala + 2000,0,renderer);
        dibujar_figura (nivel1ne,escala,0 -centro + VENTANA_ANCHO / 2 / escala - 2000,0,renderer);
        
        dibujar_figura (combustible,escala,1064 -centro + VENTANA_ANCHO / 2 / escala,13,renderer);
        dibujar_figura (combustible,escala,1685 -centro + VENTANA_ANCHO / 2 / escala,113,renderer);
        
        figura_t *torr_1 = figura_mov(torr_fig,0,0,-0.66);
        dibujar_figura (torr_1,escala,916 -centro + VENTANA_ANCHO / 2 / escala,75,renderer);
        figura_t *torr_2 = figura_mov(torr_fig,0,0,0.66);
        dibujar_figura (torr_2,escala,1425 -centro + VENTANA_ANCHO / 2 / escala,159,renderer);
        //2 combustibles y 2 torretas
    }

    if (elegir_nivel == NIVEL2) {
        centro = VENTANA_ANCHO/2 ;
        calculo_escala(&escala,&centro,nave);
        figura_t *nivel1se = obtener_figura("NIVEL1SE",lista_f);
        //Es infinito
        dibujar_figura (nivel1se,escala,0 -centro + VENTANA_ANCHO / 2 / escala,0,renderer);
        dibujar_figura (nivel1se,escala,0 -centro + VENTANA_ANCHO / 2 / escala + 2087,0,renderer);
        dibujar_figura (nivel1se,escala,0 -centro + VENTANA_ANCHO / 2 / escala - 2087,0,renderer);
        
        dibujar_figura (combustible,escala,482 -centro + VENTANA_ANCHO / 2 / escala,94,renderer);
        dibujar_figura (combustible,escala,1751 -centro + VENTANA_ANCHO / 2 / escala,247,renderer);

        figura_t *torr_3 = figura_mov(torr_fig,0,0,-0.66);
        dibujar_figura (torr_3,escala,423 -centro + VENTANA_ANCHO / 2 / escala,195,renderer);
        figura_t *torr_4 = figura_mov(torr_fig,0,0,-0.33);
        dibujar_figura (torr_4,escala,806 -centro + VENTANA_ANCHO / 2 / escala,215,renderer);
        figura_t *torr_5 = figura_mov(torr_fig,0,0,0.66);
        dibujar_figura (torr_5,escala,1254 -centro + VENTANA_ANCHO / 2 / escala,153,renderer);
        figura_t *torr_6 = figura_mov(torr_fig,0,0,2.23);
        dibujar_figura (torr_6,escala,1587 -centro + VENTANA_ANCHO / 2 / escala,223,renderer);
        //2 combustibles y 4 torretas
    }

    if (elegir_nivel == NIVEL3) {
        centro = VENTANA_ANCHO/2 ;
        calculo_escala(&escala,&centro,nave);
        figura_t *nivel1sw = obtener_figura("NIVEL1SW",lista_f);
        //Es infinito
        dibujar_figura (nivel1sw,escala,0 -centro + VENTANA_ANCHO / 2 / escala,0,renderer);
        dibujar_figura (nivel1sw,escala,0 -centro + VENTANA_ANCHO / 2 / escala + 1790,0,renderer);
        dibujar_figura (nivel1sw,escala,0 -centro + VENTANA_ANCHO / 2 / escala - 1790,0,renderer);
        
        dibujar_figura (combustible,escala,820 -centro + VENTANA_ANCHO / 2 / escala,46,renderer);
        dibujar_figura (combustible,escala,1196 -centro + VENTANA_ANCHO / 2 / escala,68,renderer);
        dibujar_figura (combustible,escala,1602 -centro + VENTANA_ANCHO / 2 / escala,46,renderer);

        figura_t *torr_7 = figura_mov(torr_fig,0,0,0);
        dibujar_figura (torr_7,escala,70 -centro + VENTANA_ANCHO / 2 / escala,46,renderer);
        figura_t *torr_8 = figura_mov(torr_fig,0,0,0);
        dibujar_figura (torr_8,escala,506 -centro + VENTANA_ANCHO / 2 / escala,12,renderer);
        figura_t *torr_9 = figura_mov(torr_fig,0,0,0);
        dibujar_figura (torr_9,escala,952 -centro + VENTANA_ANCHO / 2 / escala,12,renderer);
        figura_t *torr_10 = figura_mov(torr_fig,0,0,0);
        dibujar_figura (torr_10,escala,1385 -centro + VENTANA_ANCHO / 2 / escala,12,renderer);
        figura_t *torr_11 = figura_mov(torr_fig,0,0,3.14);
        dibujar_figura (torr_11,escala,757 -centro + VENTANA_ANCHO / 2 / escala,210,renderer);
        figura_t *torr_12 = figura_mov(torr_fig,0,0,3.14);
        dibujar_figura (torr_12,escala,1161 -centro + VENTANA_ANCHO / 2 / escala,210,renderer);
        //3 combustibles y 6 torretas
    }

    if (elegir_nivel == NIVEL4) {
        escala = VENTANA_ALTO * 1.0 / 746;
        if(VENTANA_ANCHO * 1.0 / (1139 + 150) < escala)
            escala = VENTANA_ANCHO * 1.0 / (1139 + 150);
        centro = (1139 + 150) / 2;

        figura_t *nivel1nw = obtener_figura("NIVEL1NW",lista_f);
        dibujar_figura (nivel1nw,escala,0,0,renderer);
        
        dibujar_figura (combustible,escala,188 -centro + VENTANA_ANCHO / 2 / escala,429,renderer);
        dibujar_figura (combustible,escala,667 -centro + VENTANA_ANCHO / 2 / escala,600,renderer);
        dibujar_figura (combustible,escala,1054 -centro + VENTANA_ANCHO / 2 / escala,404,renderer);
        dibujar_figura (combustible,escala,574 -centro + VENTANA_ANCHO / 2 / escala,344,renderer);

        figura_t *torr_13 = figura_mov(torr_fig,0,0,0.66);
        dibujar_figura (torr_13,escala,257 -centro + VENTANA_ANCHO / 2 / escala,440,renderer);
        figura_t *torr_14 = figura_mov(torr_fig,0,0,2.23);
        dibujar_figura (torr_14,escala,719 -centro + VENTANA_ANCHO / 2 / escala,674,renderer);
        figura_t *torr_15 = figura_mov(torr_fig,0,0,0);
        dibujar_figura (torr_15,escala,985 -centro + VENTANA_ANCHO / 2 / escala,565,renderer);
        figura_t *torr_16 = figura_mov(torr_fig,0,0,3.8);
        dibujar_figura (torr_16,escala,1125 -centro + VENTANA_ANCHO / 2 / escala,417,renderer);
        figura_t *torr_17 = figura_mov(torr_fig,0,0,3.8);
        dibujar_figura (torr_17,escala,862 -centro + VENTANA_ANCHO / 2 / escala,163,renderer);
        figura_t *torr_18 = figura_mov(torr_fig,0,0,2.23);
        dibujar_figura (torr_18,escala,626 -centro + VENTANA_ANCHO / 2 / escala,323,renderer);
        figura_t *torr_19 = figura_mov(torr_fig,0,0,3.8);
        dibujar_figura (torr_19,escala,505 -centro + VENTANA_ANCHO / 2 / escala,331,renderer);
        figura_t *torr_20 = figura_mov(torr_fig,0,0,2.23);
        dibujar_figura (torr_20,escala,378 -centro + VENTANA_ANCHO / 2 / escala,296,renderer);
        //4 combustibles Y 8 torretas
    }

    if (elegir_nivel == NIVEL5) {
        escala = VENTANA_ALTO * 1.0 / 726;
        if(VENTANA_ANCHO * 1.0 / (1146 + 0) < escala)
            escala = VENTANA_ANCHO * 1.0 / (1146 + 0);
        centro = (1146 + 0) / 2;
        
        figura_t *nivel1r = obtener_figura("NIVEL1R",lista_f);
        dibujar_figura (nivel1r,escala,0,0,renderer);
        figura_t *reactor = obtener_figura("NAVE",lista_f);
        dibujar_figura (reactor,escala,815,309,renderer);
        
    }
}

void calculo_escala(float *escala,float *centro,nave_t *nave){
    if(nave->pos[1] > VENTANA_ALTO * MARGEN_ALTURA)
            *escala = VENTANA_ALTO * MARGEN_ALTURA / nave->pos[1];
        if(*escala < ESCALA_MINIMA)
            *escala = ESCALA_MINIMA;

        if((nave->pos[0] - *centro) * *escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
            *centro = nave->pos[0] - VENTANA_ANCHO / 2 * MARGEN_ANCHO / *escala;
        else if((*centro - nave->pos[0]) * *escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
            *centro = nave->pos[0] + VENTANA_ANCHO / 2 * MARGEN_ANCHO / *escala;
}

void dibujado_de_nave(lista_t *lista_f,nave_t *nave,nivel_t elegir_nivel,SDL_Renderer *renderer){

    figura_t *nave_fig;
    figura_t *nave_escudo;

    float escala = 1;
    float centro = VENTANA_ANCHO /2;
   if(nave->pos[1] > VENTANA_ALTO * MARGEN_ALTURA)
            escala = VENTANA_ALTO * MARGEN_ALTURA / nave->pos[1];
        if(escala < ESCALA_MINIMA)
            escala = ESCALA_MINIMA;

        if((nave->pos[0] - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
            centro = nave->pos[0] - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
        else if((centro - nave->pos[0]) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
            centro = nave->pos[0] + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

    
    


    if (nave->chorro)
    {
        nave_fig = obtener_figura("NAVE+CHORRO",lista_f);
    }
    else
    {
        nave_fig = obtener_figura ("NAVE",lista_f);
    }


    figura_t *aux = figura_mov(nave_fig,0,0,nave->dir);  
    if (elegir_nivel == INICIO || elegir_nivel == NIVEL4 || elegir_nivel == NIVEL5){
        dibujar_figura(aux,1,nave->pos[0],nave->pos[1],renderer); 
        if (nave->escudo){
        nave_escudo = obtener_figura("ESCUDO2",lista_f);
        dibujar_figura(nave_escudo,1,nave->pos[0],nave->pos[1] -10,renderer);
    }
    } else{
        dibujar_figura(aux,1,nave->pos[0] -centro + VENTANA_ANCHO / 2,nave->pos[1],renderer); 
        if (nave->escudo){
        nave_escudo = obtener_figura("ESCUDO2",lista_f);
        dibujar_figura(nave_escudo,1,nave->pos[0] -centro + VENTANA_ANCHO / 2,nave->pos[1] -10,renderer);
    }
    }
    
    figura_destruir(aux);
}

void dibujar_vidas(lista_t *lista_f,nave_t *nave,SDL_Renderer *renderer){

    float posx = 40;
    float posy = 560;
    float espacio = 30;

    float tamanio = 3;

    figura_t *nave_fig = obtener_figura("NAVE",lista_f);
    
    if (nave->vidas >= 1){
        dibujar_figura(nave_fig,tamanio,posx,posy,renderer);
        printf("UNO ");
    }
    if (nave->vidas >= 2){
        dibujar_figura(nave_fig,tamanio,posx + espacio,posy,renderer);
        printf("DOS ");
    }
    if (nave->vidas >= 3){
        dibujar_figura(nave_fig,tamanio,posx + (espacio * 2),posy,renderer);
        printf("TRES ");
    }
    if (nave->vidas >= 4){
        dibujar_figura(nave_fig,tamanio,posx + (espacio * 3),posy,renderer);
        printf("CUATRO ");
    }
    if (nave->vidas >= 5){
        dibujar_figura(nave_fig,tamanio,posx + (espacio * 4),posy,renderer);
        printf("CINCO ");
    }

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
=======

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <stddef.h>


#include "dibujado.h"
#include "polilinea.h"
#include "figuras.h"
#include "nave.h"
#include "config.h"
#include "escritura.h"


bool dibujar_figura(figura_t *fig, float escala, float posx,float posy, SDL_Renderer *renderer)
{
    for (size_t i=0; i < fig->cantidad_polilineas; i++)
    {
        if (!dibujar_polilinea(fig->polis[i],escala,posx,posy,renderer)){
            perror ("ERROR DE DIBUJADO!");
            return false;
        }
    }
    return true;
}


bool dibujar_polilinea(polilinea_t *polilinea,float escala,float posx,float posy,SDL_Renderer *renderer)
{
    //Seteo el color
    uint8_t r, g, b;
    color_a_rgb(polilinea->color,&r,&g,&b);
    SDL_SetRenderDrawColor(renderer, r, g, b, 0x00);

    for(int i = 0; i < polilinea->n - 1; i++)
    { 
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

/*
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
*/

void dibujado_de_nivel(lista_t *lista_f,nave_t *nave,nivel_t elegir_nivel,SDL_Renderer *renderer){


    //########## ESCALA ##########
    float escala = 1;
    float centro = VENTANA_ANCHO/2;
    
       // printf("x:%f y:%f \n",nave->pos[0],nave->pos[1]);
       // printf("escala:%f",escala);
        
    if (elegir_nivel == INICIO) { 
        
        //########## DIBUJADO DE INICIO ##########
        /*nave->pos[0] = 388;
        nave->pos[1] = 218; */
        punto_mundo(renderer);

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
        calculo_escala(&escala,&centro,nave);
        punto_del_mundo(2000, renderer);
        dibujar_figura (nivel1ne,escala,0 -centro + VENTANA_ANCHO / 2 / escala,0,renderer);
        dibujar_figura (nivel1ne,escala,0 -centro + VENTANA_ANCHO / 2 / escala + 2000,0,renderer);
        dibujar_figura (nivel1ne,escala,0 -centro + VENTANA_ANCHO / 2 / escala - 2000,0,renderer);
        //dos objetos no pueden usar la misma polilinea si esa se debe de rotar, asi que hay que cambiarlo
        //2 combustibles y 2 torretas
    }

    if (elegir_nivel == NIVEL2) {
        centro = VENTANA_ANCHO/2 ;
        calculo_escala(&escala,&centro,nave);
        figura_t *nivel1se = obtener_figura("NIVEL1SE",lista_f);
        //Es infinito
        punto_del_mundo(4000, renderer);
        dibujar_figura (nivel1se,escala,0 -centro + VENTANA_ANCHO / 2 / escala,0,renderer);
        dibujar_figura (nivel1se,escala,0 -centro + VENTANA_ANCHO / 2 / escala + 2087,0,renderer);
        dibujar_figura (nivel1se,escala,0 -centro + VENTANA_ANCHO / 2 / escala - 2087,0,renderer);
        //2 combustibles y 4 torretas
    }

    if (elegir_nivel == NIVEL3) {
        centro = VENTANA_ANCHO/2 ;
        calculo_escala(&escala,&centro,nave);
        figura_t *nivel1sw = obtener_figura("NIVEL1SW",lista_f);
        //Es infinito
        punto_del_mundo(6000, renderer);
        dibujar_figura (nivel1sw,escala,0 -centro + VENTANA_ANCHO / 2 / escala,0,renderer);
        dibujar_figura (nivel1sw,escala,0 -centro + VENTANA_ANCHO / 2 / escala + 1790,0,renderer);
        dibujar_figura (nivel1sw,escala,0 -centro + VENTANA_ANCHO / 2 / escala - 1790,0,renderer);
        //3 combustibles y 6 torretas
    }

    if (elegir_nivel == NIVEL4) {
        escala = VENTANA_ALTO * 1.0 / 746;
        if(VENTANA_ANCHO * 1.0 / (1139 + 150) < escala)
            escala = VENTANA_ANCHO * 1.0 / (1139 + 150);
        centro = (1139 + 150) / 2;
        punto_del_mundo(8000, renderer);
        figura_t *nivel1nw = obtener_figura("NIVEL1NW",lista_f);
        dibujar_figura (nivel1nw,escala,0,0,renderer);
        //4 combustibles Y 8 torretas
    }

    if (elegir_nivel == NIVEL5) {
        escala = VENTANA_ALTO * 1.0 / 726;
        if(VENTANA_ANCHO * 1.0 / (1146 + 0) < escala)
            escala = VENTANA_ANCHO * 1.0 / (1146 + 0);
        centro = (1146 + 0) / 2;
        
        punto_del_mundo(9000, renderer);
        figura_t *nivel1r = obtener_figura("NIVEL1R",lista_f);
        dibujar_figura (nivel1r,escala,0,0,renderer);
        figura_t *reactor = obtener_figura("NAVE",lista_f);
        dibujar_figura (reactor,escala,815,309,renderer);
        
    }
}

void calculo_escala(float *escala,float *centro,nave_t *nave){
    if(nave->pos[1] > VENTANA_ALTO * MARGEN_ALTURA)
            *escala = VENTANA_ALTO * MARGEN_ALTURA / nave->pos[1];
        if(*escala < ESCALA_MINIMA)
            *escala = ESCALA_MINIMA;

        if((nave->pos[0] - *centro) * *escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
            *centro = nave->pos[0] - VENTANA_ANCHO / 2 * MARGEN_ANCHO / *escala;
        else if((*centro - nave->pos[0]) * *escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
            *centro = nave->pos[0] + VENTANA_ANCHO / 2 * MARGEN_ANCHO / *escala;
}

bool dibujado_de_nave(lista_t *lista_f,nave_t *nave,nivel_t elegir_nivel,SDL_Renderer *renderer)
{

    figura_t *nave_fig,  *nave_escudo;
    //float tras = 0;
    float escala = 1, centro = VENTANA_ANCHO /2;
    
    if(nave->pos[1] > VENTANA_ALTO * MARGEN_ALTURA)
            escala = VENTANA_ALTO * MARGEN_ALTURA / nave->pos[1];
        if(escala < ESCALA_MINIMA)
            escala = ESCALA_MINIMA;

        if((nave->pos[0] - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
            centro = nave->pos[0] - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
        else if((centro - nave->pos[0]) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
            centro = nave->pos[0] + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
    /*
    if (elegir_nivel == NIVEL1)
    {
        tras = centro + VENTANA_ANCHO / 2 / escala;
    }
    */
    


    if (nave->chorro)
    {
        nave_fig = obtener_figura("NAVE+CHORRO",lista_f);
    }
    else
    {
        nave_fig = obtener_figura ("NAVE",lista_f);
    }


    figura_t *aux = figura_mov(nave_fig,0,0,nave->dir);  
    if(aux == NULL) return false;

    if (elegir_nivel == INICIO || elegir_nivel == NIVEL4 || elegir_nivel == NIVEL5)
    {
        dibujar_figura(aux,1,nave->pos[0],nave->pos[1],renderer);

        if(nave->escudo)
        {
            nave_escudo = obtener_figura("ESCUDO2",lista_f);
            dibujar_figura(nave_escudo,1,nave->pos[0],nave->pos[1] -10,renderer);
        }
    }
    else
    {
        dibujar_figura(aux,1,nave->pos[0] -centro + VENTANA_ANCHO / 2,nave->pos[1],renderer);

        if(nave->escudo)
        {
            nave_escudo = obtener_figura("ESCUDO2",lista_f);
            dibujar_figura(nave_escudo,1,nave->pos[0] -centro + VENTANA_ANCHO / 2,nave->pos[1] -10,renderer);
        }
    }

    figura_destruir(aux);
    return true;
}

void dibujar_vidas(lista_t *lista_f,nave_t *nave,SDL_Renderer *renderer)
{

    float posx = 40, posy = 560, espacio = 30, tamanio = 3;

    figura_t *nave_fig = obtener_figura("NAVE",lista_f);
    
    for (size_t i = 0; i < nave->vidas; i++)
        dibujar_figura(nave_fig,tamanio,posx + (espacio * i),posy,renderer);

/*
    if (nave->vidas >= 1){
        dibujar_figura(nave_fig,tamanio,posx,posy,renderer);
        printf("UNO ");
    }
    if (nave->vidas >= 2){
        dibujar_figura(nave_fig,tamanio,posx + espacio,posy,renderer);
        printf("DOS ");
    }
    if (nave->vidas >= 3){
        dibujar_figura(nave_fig,tamanio,posx + (espacio * 2),posy,renderer);
        printf("TRES ");
    }
    if (nave->vidas >= 4){
        dibujar_figura(nave_fig,tamanio,posx + (espacio * 3),posy,renderer);
        printf("CUATRO ");
    }
    if (nave->vidas >= 5){
        dibujar_figura(nave_fig,tamanio,posx + (espacio * 4),posy,renderer);

    }
*/
}
>>>>>>> 1d97e7b8ff2084ab6d5859158cc004a55dd43fd1
