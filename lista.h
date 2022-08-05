#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

typedef struct lista lista_t;

typedef struct lista_iterador lista_iterador_t;

/**
 * @brief 
 * Crea una lista y la devuelve por el nombre
 * @return lista_t* 
 */
lista_t *lista_crear(void);

/**
 * @brief 
 * Agrega un dato al principio de la lista
 * @param l La lista en la que se desea guardar el dato
 * @param dato La infomacion que se quiera guardar en puntero
 * @return true => (Dato bien guardado)
 * @return false => (Dato mal guardado)
 */
bool lista_agregar(lista_t *l, void *dato);

/**
 * @brief 
 * Agrega un dato al final de la lista
 * @param l La lista en la que se desea guardar el dato
 * @param dato La infomacion que se quiera guardar en puntero
 * @return true => (Dato bien guardado)
 * @return false => (Dato mal guardado)
 */
bool lista_agregar_al_final(lista_t *l, void *dato);

/**
 * @brief 
 * Cuantos elementos tiene la lista
 * @param l De cual lista? 
 * @return size_t
 */
size_t lista_largo(lista_t *l);

/**
 * @brief 
 * Destrulle la lista con todos los datos que lo contienen
 * @param l De cual lista?
 * @param destruir_dato Como se destrulle el dato?
 */
void lista_destruir(lista_t *l, void (*destruir_dato)(void *));

/**
 * @brief 
 * Separa la lista en dos dependiendo de una funcion
 * @param l De cual lista?
 * @param f Cual funcion?
 * @param extra 
 * @return lista_t*
 */
lista_t *lista_filtrar(lista_t *l, bool (*f)(void *dato, void *extra), void *extra);

void *primer_dato(lista_t *l);
////////////////////////////////////////
//      Iteradores con lista          //
////////////////////////////////////////


/**
 * @brief 
 * Crea un iterador de una lista y situa el actual en el inicio
 * @param l De cual lista?
 * @return lista_iterador_t* 
 */
lista_iterador_t *lista_iterador_crear(lista_t *l);

/**
 * @brief 
 * Destrulle el iterador
 * @param li 
 */
void lista_iterador_destruir(lista_iterador_t *li);

/**
 * @brief 
 * Devulde el puntero al dato actual
 * @param li Cual iterador?
 * @return void* 
 */
void *lista_iterador_actual(const lista_iterador_t *li);

/**
 * @brief 
 * Pasa al siguiente dato
 * @param li 
 * @return true => (Termino la lista) 
 * @return false => (Sigue la lista)
 */
bool lista_iterador_siguiente(lista_iterador_t *li);

/**
 * @brief 
 * Termino la lista
 * @param li 
 * @return true => (Termino la lista) 
 * @return false => (Sigue la lista)
 */
bool lista_iterador_termino(const lista_iterador_t *li);

/**
 * @brief 
 * Devuelve el dato y lo saca de la lista
 * @param li 
 * @return void* 
 */
void *lista_iterador_eliminar(lista_iterador_t *li);

/**
 * @brief 
 * Incerta un dato en la posicion siguiente
 * @param li 
 * @param dato 
 * @return true 
 * @return false 
 */
bool lista_iterador_insertar(lista_iterador_t *li, void *dato);

#endif /* LISTA_H */
