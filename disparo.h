#ifndef DISPARO_H
#define DISPARO_H

//STRUCT DISPARO
typedef struct{
    
    float pos[2];
    float vel[2];
    size_t tiempo_vida;
    bool vivo;

}disparo_t;


disparo_t* disparo_crear_t(torreta_t *t, nave_t *n);

disparo_t* disparo_crear_n(nave_t *n);

void disparo_destruir(disparo_t *d);

#endif // DISPARO_H  //