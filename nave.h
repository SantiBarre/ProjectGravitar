#ifndef NAVE_H
#define NAVE_H

typedef struct{ //STRUCT NAVE.
    float pos[2]; //Posicion del centro, para el dibujado.
    float vel[2]; //Vector de la velocidad de la nave descompuesto en X e Y.
    float dir; //Vector de la direccion de la nave en RADIANES.
    bool chorro; //Si chorro == 1, aumentar la velocidad con respecto a la direccion y dibujar la nave con el chorro.
    bool escudo; //Si escudo == 1, activar el escudo y dibujarlo, ademas activar todas las interacciones con respecto al escudo (como perder combustible por ejemplo).
    bool disparo; //Si disparo ==1, disparar un proyectil.
}nave_t;
//Crea una nave_t con todos sus floats = 0, y todos sus bool = 0.
nave_t* nave_crear();
//Estas funciones cambian un valor adentro del nave_t por uno dado.
void nave_cambiar_pos(nave_t *nave,float posx, float posy);
void nave_cambiar_vel(nave_t *nave, float velx, float vely);
void nave_cambiar_dir(nave_t *nave, float dir);
//Estas funciones apagan o prenden el booleano del nave_t dependiendo si el mismo esta prendido o apagado.
void nave_prender_chorro(nave_t *nave);
void nave_prender_escudo(nave_t *nave);
void nave_disparar(nave_t *nave);
//Destruye la nave (esto solo se usara cuando se cierre el programa o al perder, todavia no se si al perder destruimos la nave y la creamos devuelta o tan solo la movemos al centro de la pantalla en el nivel de seleccion de planeta).
void nave_destruir(nave_t *nave);

typedef struct{ //STRUCT DISPARO.
    float pos[2];
    float dir; //En rad.
    float cronometro; //marca el tiempo el cual le queda al disparo antes de ser destruido.
                      // 10 segs por default.
}disparo_t;

//Crea un disparo y le aplica la posicion y direccion dada, ademas pone su cronometro en 10 segs.
disparo_t* disparo_crear(float posx,float posy,float dir);
//Estas funciones cambian los datos de disparo_t
void disparo_cambiar_dir(disparo_t *disparo,float dir);
void disparo_cambiar_pos(disparo_t *disparo,float posx,float posy);
//Esta funcion lo que hace es disminuir el cronometro por la disminucion y ademas, si el valor de cronometro fuera 0 o menor
//eliminara ese disparo de la memoria (CABE A ACLARAR QUE CUANDO SE IMPLEMENTEN LAS LISTAS ENLAZADAS DEBEREMOS ACTUALIZAR
//ESTA FUNCION PARA QUE EL NODO QUE TUVIESE A ESTE DISPARO NO SE QUEDE APUNTANDO A LA NADA).
//Disminucion al ser ejecutado en cada FPS deberia ser igual a "1/FPS"
void disparo_cronometro(disparo_t *disparo,float disminucion);
//Destruye el disparo, esto solo se deberia usar al terminar el cronometro del disparo y cuando el disparo colisiona con algo
//sea nuestra nave o terreno.
void disparo_destruir(disparo_t *disparo);

typedef struct {//STRUCT TORRETA.
    float pos[2];
    float dir;//dir en este caso representa a donde apunta la torreta
    bool disparo;//en rad.
}torreta_t;
//Hagamos que las torretas solo disparen hacia donde apuntan, por que sino es un re quilombo implementar alguna manera en la que
//apunten, ademas el profe nos permite hacer que solo disparen hacia donde apuntan.

//Crea una torreta en (posx,posy) apuntando hacia dir 
torreta_t* torreta_crear(float posx,float posy,float dir);
//Estas funciones cambian datos del struct torreta_t
void torreta_cambiar_pos(torreta_t *torreta,float posx,float posy);
void torreta_cambiar_dir(torreta_t *torreta,float dir);
//Esta funcion cambia el booleano de V a F o de F a V
void torreta_disparar(torreta_t *torreta);
#endif /* NAVE_H */
