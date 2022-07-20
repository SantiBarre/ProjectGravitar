#include <math.h>
#include "config.h"
#include "fisica.h"
#include "nave.h"

#define DIM 2

static double comp_vel(double vi, double a, double dt)
{
    return vi + dt * a;
}

static double comp_pos(double pi, double vi, double dt)
{
    return pi + dt * vi;
}

void mov_nave(nave_t *obj, int gravX, int gravY)
{
    int acelera[DIM];

    if(obj->chorro)
    {
    acelera[X] = (NAVE_ACELERACION * cos(obj->dir)) - gravX;
    acelera[Y] = (NAVE_ACELERACION * sin(obj->dir)) - gravY;
    }
    else
    {
        acelera[X] = -gravX;
        acelera[Y] = -gravY;
    }
    
    obj->vel[X] = comp_vel(obj->vel[X], acelera[X], (float) 1 / JUEGO_FPS );
    obj->vel[Y] = comp_vel(obj->vel[Y], acelera[X], (float) 1 / JUEGO_FPS );

    obj->pos[X] = comp_pos( obj->pos[X], obj->vel[X], (float) 1 / JUEGO_FPS );
    obj->pos[Y] = comp_pos( obj->pos[Y], obj->vel[Y], (float) 1 / JUEGO_FPS );
}

