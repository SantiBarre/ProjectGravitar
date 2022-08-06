#ifndef LOGICA_H
#define LOGICA_H

#include "polilinea.h"
#include "figuras.h"
#include "nave.h"
#include "config.h"

void propulsion_chorro (nave_t *nave,float *acex,float *acey);

void nave_velocidad (nave_t *nave,float acex,float acey);

void aceleracion_nave (nave_t *nave,float acex,float acey);

#endif // LOGICA_H