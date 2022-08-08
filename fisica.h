#ifndef FISICA_H
#define FISICA_H

#include <stddef.h>
#include <stdbool.h>
#include "config.h"
#include "nave.h"
#include "disparo.h"


double comp_vel(double vi, double a, double dt);

double comp_pos(double pi, double vi, double dt);

void mov_nave(nave_t *n, bool inicio);

float pendiente(const float vectorA[], const float vectorB[]);

void mov_disparo(disparo_t *d);



#endif /* FISICA_H */
