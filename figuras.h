#ifndef FIGURAS_H
#define FIGURAS_H

#include <stdint.h>
#include <stdio.h>
#include "polilinea.h"
#include "lista.h"

typedef enum{
    ICONO,
    NIVEL,
    SPRITE,
    PLANETA,
    BASE,
    COMBUSTIBLE,
    TORRETA,
    REACTOR,
}figura_tipo_t; //Lo moví arriba de figura_t por que no dejaba compilar sino.

typedef struct
{
    char (*nombre)[20];
    bool infinito;
    figura_tipo_t tipo;

    polilinea_t **polis;
    size_t cantidad_polilineas;

}figura_t;

figura_t *crear_figura(char *nombre, figura_tipo_t tipo, bool infinito, size_t cantidad_polilineas);
polilinea_t *leer_polilinea(FILE *f);
bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas);
////    Tipo de figura      ////

/**
 * @brief 
 * Devuelve por un arreglo de char con el nombre de la figura
 * @param figura 
 * @return const char* 
 */
const char* figura_tipo_a_cadena(figura_tipo_t figura);


/**
 * @brief 
 * Destrulle una figura
 * @param fig 
 */
void figura_destruir(void *fig);

/**
 * @brief 
 * Devuelve la figura que se le paso por nombre
 * @param nom 
 * @param l 
 * @return figura_t* 
 */
figura_t *obtener_figura(char nom[], lista_t *l);

/**
 * @brief 
 * Devuelve lista de figuras
 * @param arch 
 * @return lista_t* 
 */
lista_t *guardar_figura(FILE *arch);

#endif /* FIGURAS_H */