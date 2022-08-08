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

void mov_nave(nave_t *n, bool inicio);


disparo_t* disparo_crear_t(torreta_t *t, nave_t *n,size_t count);



#endif /* FISICA_H */
