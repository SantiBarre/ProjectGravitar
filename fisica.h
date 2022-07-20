#ifndef FISICA_H
#define FISICA_H

#include <stddef.h>
#include <stdbool.h>
#include "config.h"
#include "nave.h"

enum dim{
    X,
    Y,
};

double comp_vel(double vi, double a, double dt);

double comp_pos(double pi, double vi, double dt);

/**
 * @brief 
 * Funcion para trasladar objetos
 * @param obj 
 * @param gravX 
 * @param gravY 
 * @param chorro 
 */
void mov_nave(nave_t *obj, int gravX, int gravY);


#endif /* FISICA_H */
