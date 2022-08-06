#ifndef _CONFIG_H_
#define _CONFIG_H_

#define PI 3.14159265358979323846

#define VENTANA_ANCHO 800
#define VENTANA_ALTO 600

#define MARGEN_ALTURA 0.7
#define MARGEN_ANCHO 0.7
#define MARGEN_NIVEL_FIJO 0.9
#define ESCALA_MINIMA 0.6

#define JUEGO_FPS 100
#define JUEGO_COMBUSTIBLE_INICIAL 10000
#define JUEGO_COMBUSTIBLE_POT_X_SEG 250 //Combustible usado por el chorro en 1 segundo
#define JUEGO_COMBUSTIBLE_ESC_X_SEG 500 //Combustible usado por el escudo en 1 segundo

#define G 10

#define NAVE_ROTACION_PASO (PI/20)
#define NAVE_ACELERACION (10*G)

#define NAVE_ANGULO_INICIAL (PI/2)

typedef enum{
    INICIO = 1,
    NIVEL1 = 2,
    NIVEL2 = 3,
    NIVEL3 = 4,
    NIVEL4 = 5,
    NIVEL5 = 6,
}nivel_t;

#endif // _CONFIG_H_

