#include "polilinea.h" 
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include "lista.h"

#define MARGEN_DE_COLISION 10

static void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b)
{
    *r = ((c&4)/4)*255;
    *g = ((c&2)/2)*255;
}

polilinea_t *polilinea_crear_vacia(size_t n) //Elimine el static por que daba error al compilar
{
    polilinea_t *nueva = malloc(sizeof(polilinea_t));
    if (nueva == NULL) return NULL;

    nueva->n = n; 
    nueva->puntos = malloc(2 * n * sizeof(float));
    if(nueva->puntos == NULL)
    {
        free(nueva);
        return NULL;
    }

    return nueva;
}

polilinea_t *polilinea_crear(const float puntos[][2], size_t n)
{
    polilinea_t *poli = polilinea_crear_vacia(n);
    if(poli == NULL) return NULL;

    for (size_t i = 0; i < n; i++)
    {
        poli->puntos[i][0] = puntos[i][0];
        poli->puntos[i][1] = puntos[i][1];
    }
    return poli;
}

void polilinea_destruir(polilinea_t *polilinea)
{ 
    free(polilinea->puntos);
    free(polilinea);
}

size_t polilinea_cantidad_puntos(const polilinea_t *polilinea)
{
    return polilinea->n;
}

polilinea_t *polilinea_clonar(const polilinea_t *polilinea)
{
    polilinea_t *clon = polilinea_crear((const float (*)[2])polilinea->puntos, polilinea->n);
    if(clon == NULL) return NULL;
    clon->color = polilinea->color;
    return clon;
}


////    SET GET     POLILINEA   ////

bool polilinea_getter_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y)
{
    if(polilinea != NULL && pos < polilinea->n)
    {
        *x = polilinea->puntos[pos][0];
        *y = polilinea->puntos[pos][1];
        return true;
    }
    return false;
}

bool polilinea_setter_punto(polilinea_t *polilinea, size_t pos, float x, float y)
{
    if(polilinea != NULL && pos < polilinea->n)
    {
        polilinea->puntos[pos][0] = x;
        polilinea->puntos[pos][1] = y;
        return true;
    }
    return false;
}


////    SET GET     Color       ////

bool polilinea_setter_color(polilinea_t *polilinea, color_t color)
{
    if(polilinea != NULL)
    {
        polilinea->color = color;
        return true;
    }
    return false;
}

bool polilinea_getter_color(const polilinea_t *polilinea, uint8_t *r, uint8_t *g, uint8_t *b)
{
    if(polilinea != NULL)
    {
        color_a_rgb(polilinea->color, r, g, b);
        return true;
    }
    return false;
}


////    CALCULOS        ////

void rotar(float polilinea[][2], size_t n, double rad)
{
    float aux[2];

    for (size_t i = 0; i < n; i++)
    {
        aux[0] = polilinea[i][0];
        aux[1] = polilinea[i][1];

        polilinea[i][0] = aux[0] * cosf(rad) - aux[1] * sinf(rad);
        polilinea[i][1] = aux[0] * sinf(rad) + aux[1] * cosf(rad);
    }
}

void trasladar(float polilinea[][2], size_t n, float dx, float dy)
{
    for (size_t i = 0; i < n; i++)
    {
        polilinea[i][0] += dx;
        polilinea[i][1] += dy;
    }
}
static void sumaV(const float vectorA[], const float vectorB[], float BA[]) //NUEVO
{
    for (size_t i = 0; i < 2; i++)
        BA[i] = vectorA[i] + vectorB[i];
}

static void restaV(const float vectorA[], const float vectorB[], float BA[])
{
    for (size_t i = 0; i < 2; i++)
        BA[i] = vectorA[i] - vectorB[i];
}



float moduloV(const float vectorA[],const float vectorB[])
{
    return (float)sqrt(pow(vectorB[0] - vectorA[0],2) + pow(vectorB[1] - vectorA[1],2));
}

static float producto_escalar(const float vectorA[], const float vectorB[])
{
    float result = 0;

    for (size_t i = 0; i < 2; i++)
        result += vectorA[i] * vectorB[i];

    return result;
}

static float calc_angulo_fi(const float vectorA[], const float vectorB[], const float vectorP[])
{

    float AP[2], AB[2];
    float divisor = 0, dividendo;

    restaV(vectorP, vectorA, AP);
    restaV(vectorB, vectorA, AB);

    dividendo = producto_escalar(AP, AB);

    for (size_t i = 0; i < 2; i++)
        divisor += pow(AB[i], 2);

    return (dividendo / divisor);
}

float distancia_punto_a_polilinea(float polilinea[][2], size_t n, float px, float py)
{
    float distancia[n];
    float vectorP[2];
    float angulo_fi;

    for (size_t i = 0; i < n; i++)
    {
        vectorP[0] = px;
        vectorP[1] = py;

        angulo_fi = calc_angulo_fi(polilinea[i], polilinea[i + 1], vectorP);

        if (angulo_fi <= 0)
            distancia[i] = moduloV(vectorP, polilinea[i]);
        
        if (angulo_fi >= 1)
            distancia[i] = moduloV(vectorP, polilinea[i + 1]);

        if(angulo_fi > 0 && angulo_fi < 1)
        {
            float BA[2];
            float result[2];

            restaV(polilinea[i + 1], polilinea[i], BA);

            for (size_t i = 0; i < 2; i++)
                BA[i] = angulo_fi * BA[i];

            sumaV(polilinea[i], BA, result);

            distancia[i] = moduloV(vectorP, result);
        }
    }

    float dmin = distancia[0];

    for (size_t i = 1; i < n; i++)
        if (dmin > distancia[i])
            dmin = distancia[i];

    return dmin;
}

polilinea_t *polilinea_mov(const polilinea_t *poli, float posx, float posy, float ang)
{
    polilinea_t *p = polilinea_clonar(poli);
    if(p == NULL) {
        perror("No se pudo clonar una polilinea!");
        return NULL;
    }

    size_t cant_puntos = polilinea_cantidad_puntos(p);

    rotar(p->puntos, cant_puntos, ang);

    trasladar(p->puntos, cant_puntos, posx, posy);

    return p;
}

/*bool colision_polilineas (float polilineaA[][2],size_t nA,float polilineaB[][2],size_t nB ){
    float aux;
    for (size_t i=0; i < nB; i++){
        aux = distancia_punto_a_polilinea(polilineaA,nA,polilineaB[i][0],polilineaB[i][1]);
        if (aux <= MARGEN_DE_COLISION){
            return true;
        }
    }
    return false;
}*/