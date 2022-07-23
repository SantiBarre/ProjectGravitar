#ifndef FIGURAS_H
#define FIGURAS_H

#include <stdint.h>

typedef struct
{
    char (*nombre)[20];
    bool infinito;
    figura_tipo_t tipo;

    polilinea_t *polis;
    size_t cantidad_polilineas;

}figura_t;

typedef enum{
    ICONO,
    NIVEL,
    SPRITE,
    PLANETA,
    BASE,
    COMBUSTIBLE,
    TORRETA,
    REACTOR,
}figura_tipo_t;

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

lista_t *guardar_figuras(char *archivo);

#endif /* FIGURAS_H */