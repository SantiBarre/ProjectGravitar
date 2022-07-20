#ifndef FIGURAS_H
#define FIGURAS_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

typedef uint8_t color_t;
typedef struct polilinea polilinea_t; 


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
 * Crea un color
 * @param r 
 * @param g 
 * @param b 
 * @return color_t 
 */
color_t color_crear(bool r, bool g, bool b);

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


////    Lectura     ////

/**
 * @brief 
 * Se encarga de devolver el encabesado y retorna por variable
 * @param f 
 * @param nombre 
 * @param tipo 
 * @param infinito 
 * @param cantidad_polilineas 
 * @return true 
 * @return false 
 */
bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas);

/**
 * @brief 
 * Lee la polilinea segun la estructura
 * @param f 
 * @return polilinea_t*  
 */
polilinea_t *leer_polilinea(FILE *f);



#endif /* FIGURAS_H */