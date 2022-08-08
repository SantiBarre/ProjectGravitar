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

////    Color       ////

/**
 * @brief 
 * Pasa de color 3 bit a 3 byte
 * @param c 
 * @param r retorna rojo
 * @param g retorna verde
 * @param b retorna azul
 */
void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b);

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
 * Guarda las figuras en una lista
 * @param archivo 
 * @return lista_t* 
 */
lista_t *guardar_figuras(char *archivo);

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

figura_t *figura_clonar(const figura_t *figura);

figura_t *figura_mov(const figura_t *figura, float posx, float posy, float ang);

#endif /* FIGURAS_H */