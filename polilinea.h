#ifndef POLILINEA_H
#define POLILINEA_H

#include <stdbool.h>// Booleanos
#include <stdlib.h>

typedef struct polilinea polilinea_t;

//      Creación y destrucción

/*
 *Cree una nueva polilínea con n puntos pero sin inicializar sus coordenadas. 
 *Post: devolver la polilínea creada o NULL en caso de falla.
 */
polilinea_t *polilinea_crear_vacia(size_t n);

/*
 *cree una nueva polilínea en base a los n puntos recibidos.
 *Post: devolver la polilínea creada o NULL en caso de falla.
 */
polilinea_t *polilinea_crear(const float puntos[][2], size_t n);

/*
libere la memoria asociada a la polilinea previamente creada.
*/
void polilinea_destruir(polilinea_t *polilinea);


//      Getters y setters

/*
devuelva la cantidad de puntos en la polilinea recibida.
*/
size_t polilinea_cantidad_puntos(const polilinea_t *polilinea);

/* 
que devuelva por la interfaz las coordenadas (x, y) del punto que está en la posición pos de polilinea.
 La función debe retornar true de poder completar la operación, false en caso contrario.
*/
bool polilinea_getter_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y);

/**
 * @brief 
 * que asigne el punto de coordenadas (x, y) en la posición pos de la polilinea.
 La función debe retornar true de poder completar la operación, false en caso contrario.
 * @param polilinea 
 * @param pos 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
bool polilinea_setter_punto(polilinea_t *polilinea, size_t pos, float x, float y);

/**
 * @brief 
 * Dado un color de tipo color_t se lo asigna a la polilinea
 * @param polilinea 
 * @param color 
 * @return true 
 * @return false 
 */
bool polilinea_setter_color(polilinea_t *polilinea, color_t color);

/**
 * @brief 
 * Devuelve por variables los colores en formato RGB
 * @param polilinea 
 * @param r 
 * @param g 
 * @param b 
 * @return true 
 * @return false 
 */
bool polilinea_getter_color(const polilinea_t *polilinea, int *r, int *g, int *b);


//      Memoria

/**
 * @brief 
 *Que dada una polilinea devuelva la copia de la misma en memoria nueva
 */
polilinea_t *polilinea_clonar(const polilinea_t *polilinea);


////    Calculo

/**
 * @brief 
 * Rota un angulo rad la polilinea
 * @param polilinea 
 * @param n 
 * @param rad 
 */
void rotar(double polilinea[][2], size_t n, double rad);

/**
 * @brief 
 * Traslada todo a un punto
 * @param polilinea 
 * @param n 
 * @param dx 
 * @param dy 
 */
void trasladar(double polilinea[][2], size_t n, float dx, float dy);

/**
 * @brief 
 * Me dice la distancia minima de una polilinea a un punto 
 * @param polilinea 
 * @param n 
 * @param px 
 * @param py 
 * @return double 
 */
double distancia_punto_a_polilinea(double polilinea[][2], size_t n, float px, float py);

#endif /* POLILINEA_H */




