#include <math.h>
#include <stdbool.h>

#include "config.h"
#include "fisica.h"

#include "nave.h"
#include "polilinea.h"
#include "disparo.h"
#include "lista.h"
#include "logica.h"

static double comp_vel(double vi, double a, double dt)
{
    return vi + dt * a;
}

static double comp_pos(double pi, double vi, double dt)
{
    return pi + dt * vi;
}

float pendiente(const float vectorA[], const float vectorB[])
{
    return atan2f(vectorA[0] - vectorB[0], vectorA[1] - vectorB[1]);
}

bool colision_mundo_punto(figura_t *f, float posx, float posy)
{
    size_t cant;
    float distrancia_nave;
    for (size_t i = 0 ; i < f->cantidad_polilineas ; i++)
    {
        cant = polilinea_cantidad_puntos(f->polis[i]);
        distrancia_nave = distancia_punto_a_polilinea(f->polis[i]->puntos, cant , posx, posy);
        if(distrancia_nave < 5)
            return true;
    }
    return false;
}

void mov_nave(nave_t *n, nivel_t planeta, lista_t *p)
{
    float dir_g[2];
    float distrancia_nave;

    if (planeta == INICIO)
    {
        float estrella[2] = {457, 364};

        distrancia_nave = moduloV(estrella, n->pos);

        if(distrancia_nave < 50)
        {
            n->vidas -= 1;
            n->pos[0] = 388;
            n->pos[1] = 218;
            n->vel[0] = n->vel[1] = 0;

            n->dir = NAVE_ANGULO_INICIAL;
        }

        //Por si chocas con la pared de inicio
        if(( n->pos[0] > VENTANA_ANCHO) || (n->pos[0] < 0))
            n->vel[0] = -n->vel[0];
        
        if((n->pos[1] > VENTANA_ALTO) || (n->pos[1] < 0))
            n->vel[1] = -n->vel[1];

        
        //Calculo la direcion de la gravedad
        float pen = pendiente(estrella, n->pos);

        dir_g[0] = sin(pen) * G;
        dir_g[1] = cos(pen) * G;

    }
    else
    {
        figura_t *nivel;
        if (NIVEL1)
        {
            nivel = obtener_figura("NIVEL1NE", p);

        }
        else if (NIVEL2)
        {
            nivel = obtener_figura("NIVEL1SE", p);
        }
        else if (NIVEL3)
        {
            nivel = obtener_figura("NIVEL1SW", p);
        }
        else if (NIVEL4)
        {
            nivel = obtener_figura("NIVEL1NW",p);
        }
        else
        {
            nivel = obtener_figura("NIVEL1R",p);
        }

        //Si el nivel es infinito
        if(nivel->infinito)
        {
            if(NIVEL1)
            {
                if (n->pos[0] >= 2000)
                    n->pos[0] = 0;
                    
                if (n->pos[0] <= 0)
                    n->pos[0] = 2000;
            }
            if(NIVEL2)
            {
                if (n->pos[0] > 2087)
                    n->pos[0] = n->pos[0] - 2087;
                
                if (n->pos[0] < 0)
                    n->pos[0] = n->pos[0] + 2087;    
            }
            if(NIVEL3)
            {
                if (n->pos[0] > 1790)
                    n->pos[0] = n->pos[0] - 1790;
                
                if (n->pos[0] < 0)
                    n->pos[0] = n->pos[0] + 1790;
            }
        }

        if(colision_mundo_punto(nivel, n->pos[0], n->pos[1]))
        {
            n->vidas -= 1;

            n->pos[0] = VENTANA_ANCHO/2;
            n->pos[1] = VENTANA_ALTO/2;

            n->vel[0] = n->vel[1] = 0;

            n->dir = NAVE_ANGULO_INICIAL;
        }


        dir_g[0] = 0;
        dir_g[1] = -G;
    }
    
    float ace[2];

    if(n->chorro)
    {
        ace[0] = (NAVE_ACELERACION * cos(n->dir)) + dir_g[0];
        ace[1] = (NAVE_ACELERACION * sin(n->dir)) + dir_g[1];
    }
    else
    {
        ace[0] = dir_g[0];
        ace[1] = dir_g[1];
    }

    for (size_t i = 0; i < 2; i++)
        n->vel[i] = comp_vel(n->vel[i], ace[i], (float) 1 / JUEGO_FPS);

    for (size_t i = 0; i < 2; i++)
        n->pos[i] = comp_pos(n->pos[i], n->vel[i], (float) 1 / JUEGO_FPS);
    
}


void mov_disparo(disparo_t *d)
{
    for (size_t i = 0; i < 2; i++)
        d->pos[i] = comp_pos(d->pos[i], d->vel[i], 1 / JUEGO_FPS);
    
    d->tiempo_vida++;

    if (d->tiempo_vida > 10 * JUEGO_FPS)
        d->vivo = false;
}



