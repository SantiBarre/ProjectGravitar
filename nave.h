#ifndef NAVE_H
#define NAVE_H

typedef struct{
    float pos[2]; //Posicion del centro, para calcular colisiones.
    float vel[2]; //Vector de la velocidad de la nave descompuesto en X e Y.
    float dir; //Vector de la direccion de la nave en RADIANES.
    bool chorro; //Si chorro == 1, aumentar la velocidad con respecto a la direccion y dibujar la nave con el chorro.
    bool escudo; //Si escudo == 1, activar el escudo y dibujarlo, ademas activar todas las interacciones con respecto al escudo (como perder combustible por ejemplo).
    bool disparo; //Si disparo ==1, disparar un proyectil.
}nave_t;

nave_t nave_crear(); //Crea una nave_t con todos sus floats = 0, y todos sus bool = 0.
//Estas funciones cambian un valor adentro del nave_t por uno dado.
void nave_cambiar_pos(nave_t *nave,float posx, float posy);
void nave_cambiar_vel(nave_t *nave, float velx, float vely);
void nave_cambiar_dir(nave_t *nave, float dir);
//Estas funciones apagan o prenden el booleano del nave_t dependiendo si el mismo esta prendido o apagado.
void nave_prender_chorro(nave_t *nave);
void nave_prender_escudo(nave_t *nave);
void nave_disparar(nave_t *nave);

#endif /* NAVE_H */
