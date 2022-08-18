#ifndef LOGICA_H
#define LOGICA_H

#include "polilinea.h"
#include "figuras.h"
#include "nave.h"
#include "config.h"
#include "math.h"

void logica_niveles(nave_t *nave, nivel_t *elegir_nivel, float *contador);

void logica_nave(nave_t *nave);

lista_t *inicializar_combustibles(void);

lista_t *inicializar_torretas(void);

#endif // LOGICA_H