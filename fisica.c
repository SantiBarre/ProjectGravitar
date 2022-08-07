#include <math.h>
#include "config.h"
#include "fisica.h"
#include "nave.h"

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


void mov_nave(nave_t *n, bool inicio, float estrella[])
{
    float dir_g[2];
    if (inicio)
    {
        //Calculo la direcion de la gravedad
        float pen = pendiente(estrella, n->pos);

        dir_g[0] = cos(pen) * G;
        dir_g[1] = sin(pen) * G;
        
    }
    else
    {
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
        n->vel[i] = comp_vel(n->vel[i], ace[i], 1 / JUEGO_FPS);

    for (size_t i = 0; i < 2; i++)
        n->pos[i] = comp_pos(n->pos[i], n->vel[i], 1 / JUEGO_FPS);
    
}