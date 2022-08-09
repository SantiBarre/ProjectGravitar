#ifndef NAVE_H
#define NAVE_H

#include <stddef.h>
#include <stdbool.h>


typedef struct{

    float pos[2]; //Posicion del centro, para el dibujado.
    float vel[2]; //Vector de la velocidad de la nave descompuesto en X e Y.
    float ace[2];

    float dir; //Vector de la direccion de la nave en RADIANES.

    bool chorro; //Si chorro == 1, aumentar la velocidad con respecto a la direccion y dibujar la nave con el chorro.
    bool escudo; //Si escudo == 1, activar el escudo y dibujarlo, ademas activar todas las interacciones con respecto al escudo (como perder combustible por ejemplo).
    bool disparo; //Si disparo ==1, disparar un proyectil.

    char vidas;

    float combustible;

    int puntos;

    size_t tiempo_disparo;
}nave_t;

//Crea una nave_t con todos sus floats = 0, y todos sus bool = 0.
nave_t* nave_crear();

//Destruye la nave (esto solo se usara cuando se cierre el programa o al perder, todavia no se si al perder destruimos la nave y la creamos devuelta o tan solo la movemos al centro de la pantalla en el nivel de seleccion de planeta).
void nave_destruir(nave_t *nave);


void nave_derecha(nave_t *n);

void nave_izquieda(nave_t *n);


//Estas funciones apagan o prenden el booleano del nave_t dependiendo si el mismo esta prendido o apagado.
void nave_chorro(nave_t *n, bool on_off);
void nave_escudo(nave_t *n, bool on_off);
void nave_disparar(nave_t *n, bool on_off);

bool nave_muerta(nave_t *n);

//ACA LAS NUEVAS
void propulsion_chorro (nave_t *nave);
void nave_velocidad (nave_t *nave);
void aceleracion_nave (nave_t *nave);



typedef struct {//STRUCT TORRETA.
    float pos[2];
    float dir;//dir en este caso representa a donde apunta la torreta
    bool disparo;//en rad.
}torreta_t;
//Hagamos que las torretas solo disparen hacia donde apuntan, por que sino es un re quilombo implementar alguna manera en la que
//apunten, ademas el profe nos permite hacer que solo disparen hacia donde apuntan.

//Crea una torreta apuntando hacia dir 
torreta_t* torreta_crear(float dir);

//Estas funciones cambian datos del struct torreta_t
void torreta_cambiar_dir(torreta_t *torreta,float dir);

//Esta funcion cambia el booleano de V a F o de F a V
void torreta_disparar(torreta_t *torreta);

typedef struct {
    float pos[2];
    bool uso;
    float dir;
}combustible_t;

combustible_t* combustible_crear(float posx,float posy,float dir);

//True significa usado, flase sin usar
void combustible_usar(combustible_t* combus);

#endif /* NAVE_H */
