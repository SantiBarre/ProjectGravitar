#ifndef FISICA_H
#define FISICA_H

#include <stddef.h>
#include <stdbool.h>
#include "config.h"
#include "lista.h"
#include "nave.h"
#include "disparo.h"

void mov_nave(nave_t *n, nivel_t planeta, lista_t *p);

float pendiente(const float vectorA[], const float vectorB[]);

void mov_disparo(disparo_t *d);



#endif /* FISICA_H */
