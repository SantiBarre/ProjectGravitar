#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "logica.h"
#include "polilinea.h"
#include "figuras.h"
#include "nave.h"
#include "config.h"

void propulsion_chorro (nave_t *nave,float *acex,float *acey){
    if (nave->chorro){
        *acex = NAVE_ACELERACION * (cos(nave->dir));
        *acey = NAVE_ACELERACION * (sin(nave->dir));
    }
    else {
        *acex = 0;
        *acey = 0;
    }
}

void nave_velocidad (nave_t *nave,float acex,float acey){
    nave->vel[0] = nave->vel[0] + acex * (1/JUEGO_FPS);
    nave->vel[1] = nave->vel[1] + acey * (1/JUEGO_FPS);
}

void aceleracion_nave (nave_t *nave,float acex,float acey){
    nave->pos[0] = nave->pos[0] + (nave->vel [0] * 1/JUEGO_FPS) + (acex/2 * pow((1/JUEGO_FPS),2));
    nave->pos[1] = nave->pos[1] + (nave->vel [1] * 1/JUEGO_FPS) + (acex/2 * pow((1/JUEGO_FPS),2));
}
