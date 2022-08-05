#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "polilinea.h"
#include "figuras.h"
#include "nave.h"

static bool cambiar_color_poli(const polilinea_t *p, SDL_Renderer *renderer)
{
    uint8_t r, g, b;
    if(!polilinea_getter_color(p, &r, &g, &b))
        return false;
    SDL_SetRenderDrawColor(renderer, r, g, b, 0x00);
    return true;
}

static bool dibujar_polilinea(const polilinea_t *poli, float escala, float posx, float posy, float ang, SDL_Renderer *renderer)
{
    //Creo un clon de la polilinea
    polilinea_t *p = polilinea_mov(poli, posx, posy, ang);
    if(p == NULL) return false;

    //Asigno un color a la futura polilinea
    if(!cambiar_color_poli(p, renderer))
        {
            polilinea_destruir(p);
            return false;
        }

    //Imprimo punto por punto a la polilinea
    size_t cant_puntos = polilinea_cantidad_puntos(p);
    float x, y, x_sig, y_sig;

    for (size_t pos = 0; pos < (cant_puntos -1) ; pos++)
    {
        if (pos == 0) //Primera vez, busco los dos puntos, actual y anterior
        {  
            if( (!polilinea_getter_punto(p, pos , &x, &y))  || 
                (!polilinea_getter_punto(p, pos + 1 , &x_sig, &y_sig))
              )
            {
                polilinea_destruir(p);
                return false;
            } 
            else
            {
                //El punto siguiente pasa a ser el actual
                x = x_sig;
                y = y_sig;

                //Punto siguiente
                if(!polilinea_getter_punto(p, pos + 1 , &x_sig, &y_sig))
                {
                    polilinea_destruir(p);
                    return false;
                }
            }
        }

        //Imprimo de punto anterior al actual
        if ( SDL_RenderDrawLine( 
                renderer ,
                (x * escala) ,
                (-y * escala) , 
                (x_sig * escala) , 
                (-y_sig * escala) 
                )
            != 0)
        {
            polilinea_destruir(p);
            return false;
        }

        polilinea_destruir(p);
    }

    return true;
}

bool dibujar_figura(figura_t *fig, float escala, float posx, float posy, float ang, SDL_Renderer *renderer)
{
    //Imprimo todas las polilineas de una figura
    for (size_t i = 0; i < fig->cantidad_polilineas ; i++)
    {
        if(!dibujar_polilinea(fig->polis[i], escala, posx, posy, ang, renderer))
            return false;
    }

    return true;
}





/*
void dibujado_de_nivel(lista_t *lista_f,nave_t *nave,SDL_Renderer *renderer){
    
    //########## NAVE ##########
    nivel_t elegir_nivel = INICIO;
    nave_t *nave = nave_crear();
    figura_t *nave_fig = obtener_figura ("FIGURA");

    dibujar_polilinea (nave_fig->polis,f,nave->pos[0],nave->pos[1]);


    //########## OBJETOS ##########
    
    figura_t *combustible = obtener_figura("COMBUSTIBLE",lista_f)
    figura_t *torreta = obtener_figura("TORRETA",lista_f);
    
    switch (elegir_nivel){
        case INICIO:
            
            //########## DIBUJADO DE INICIO ##########
            nave->pos[0] = 388;
            nave->pos[1] = 218;

            figura_t *base = obtener_figura("BASE",lista_f);
            dibujar_polilinea (base->polis,f,388,218,renderer);
            figura_t *estrella = obtener_figura("ESTRELLA",lista_f);
            dibujar_polilinea (estrella->polis,f,457,364,renderer);
            figura_t *planeta1 = obtener_figura("PLANETA1",lista_f);
            dibujar_polilinea (planeta1->polis,f,663,473,renderer);
            figura_t *planeta2 = obtener_figura("PLANETA2",lista_f);
            dibujar_polilinea (planeta2->polis,f,671,145,renderer);
            figura_t *planeta3 = obtener_figura("PLANETA3",lista_f);
            dibujar_polilinea (planeta3->polis,f,110,79,renderer);
            figura_t *planeta4 = obtener_figura("PLANETA4",lista_f);
            dibujar_polilinea (estrella->polis,f,204,455,renderer);
            figura_t *planeta5 = obtener_figura("PLANETA5",lista_f);
            dibujar_polilinea (estrella->polis,f,111,307,renderer);

            //########## INTERACCIONES DE INICIO ##########

            
            break;

        case NIVEL1:
            figura_t *nivel1ne = obtener_figura("NIVEL1NE",lista_f);
            dibujar_polilinea (nivel1ne->polis,f,VENTANA_ANCHO/2,VENTANA_ALTO/2,renderer);
            //dos objetos no pueden usar la misma polilinea si esa se debe de rotar, asi que hay que cambiarlo
            dibujar_polilinea (combustible->polis,f,1064,13,renderer);
            dibujar_polilinea (combustible->polis,f,1685,113,renderer);
            dibujar_polilinea (torreta->polis,f,916,75,renderer);
            dibujar_polilinea (torreta->polis,f,1425,159,renderer);
            break;
        case NIVEL2:
            figura_t *nivel1se = obtener_figura("NIVEL1SE",lista_f);
            dibujar_polilinea (nivel1se->polilinea,f,VENTANA_ANCHO/2,VENTANA_ALTO/2,renderer);
            //2 combustibles y 4 torretas
            break;
        case NIVEL3:
            figura_t *nivel1sw = obtener_figura("NIVEL1SW",lista_f);
            dibujar_polilinea (nivel1sw->polilinea,f,VENTANA_ANCHO/2,VENTANA_ALTO/2,renderer);
            //3 combustibles y 6 torretas
            break;
        case NIVEL4:
            figura_t *nivel1nw = obtener_figura("NIVEL1NW",lista_f);
            dibujar_polilinea (nivel1nw->polilinea,f,VENTANA_ANCHO/2,VENTANA_ALTO/2,renderer);
            //4 combustibles Y 8 torretas
            break;
        case NIVEL5:
            figura_t *nivel1r = obtener_figura("NIVEL1R",lista_f);
            dibujar_polilinea (nivel1r->polilinea,f,VENTANA_ANCHO/2,VENTANA_ALTO/2,renderer);
            figura_t *reactor = obtener_figura("REACTOR",lista_f);
            dibujar_polilinea (reactor->polilinea,f,815,309,renderer);
            break;
    }
}
*/