#include "polilinea.h"
#include "figuras.h" 

#include <stdbool.h>
#include <stddef.h>


typedef struct{
    float (*puntos)[2];
    color_t color;
    size_t n;
}polilinea_t;


static polilinea_t *polilinea_crear_vacia(size_t n)
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

bool polilinea_getter_color(const polilinea_t *polilinea, int *r, int *g, int *b)
{
    if(polilinea != NULL)
    {
        color_a_rgb(polilinea->color, r, g, b);
        return true;
    }
    return false;
}


////    CALCULOS        ////

void rotar(double polilinea[][2], size_t n, double rad)
{
    double aux[2];

    for (size_t i = 0; i < n; i++)
    {
        aux[0] = polilinea[i][0];
        aux[1] = polilinea[i][1];

        polilinea[i][0] = aux[0] * cosf(rad) - aux[1] * sinf(rad);
        polilinea[i][1] = aux[0] * sinf(rad) + aux[1] * cosf(rad);
    }
}

void trasladar(double polilinea[][2], size_t n, float dx, float dy)
{
    for (size_t i = 0; i < n; i++)
    {
        polilinea[i][0] += dx;
        polilinea[i][1] += dy;
    }
}

static void restaV(const double vectorA[], const double vectorB[], double BA[])
{
    for (size_t i = 0; i < 2; i++)
        BA[i] = vectorA[i] - vectorB[i];
}

static double producto_escalar(const double vectorA[], const double vectorB[])
{
    double result = 0;

    for (size_t i = 0; i < 2; i++)
        result += vectorA[i] * vectorB[i];

    return result;
}

static double calc_angulo_fi(const double vectorA[], const double vectorB[], const double vectorP[])
{

    double AP[2], AB[2];
    double divisor = 0, dividendo;

    restaV(vectorP, vectorA, AP);
    restaV(vectorB, vectorA, AB);

    dividendo = producto_escalar(AP, AB);

    for (size_t i = 0; i < 2; i++)
        divisor += pow(AB[i], 2);

    return (dividendo / divisor);
}

double distancia_punto_a_polilinea(double polilinea[][2], size_t n, float px, float py)
{
    double distancia[n];
    double vectorP[2];
    double angulo_fi;

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
            double BA[2];
            double result[2];

            restaV(polilinea[i + 1], polilinea[i], BA);

            for (size_t i = 0; i < 2; i++)
                BA[i] = angulo_fi * BA[i];

            sumaV(polilinea[i], BA, result);

            distancia[i] = moduloV(vectorP, result);
        }
    }

    double dmin = distancia[0];

    for (size_t i = 1; i < n; i++)
        if (dmin > distancia[i])
            dmin = distancia[i];

    return dmin;
}