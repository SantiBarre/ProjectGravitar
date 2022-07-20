#include "figuras.h" 
#include "polilinea.h"
#include "lista.h"

#include <stddef.h> 
#include <stdint.h>
#include <stdbool.h>

////    Definiciones        ////

#define MASK_R 0x4
#define MASK_G 0x2
#define MASK_B 0x1

#define ON_COLOR 255
#define OFF_COLOR 0

#define MASK_NUM 0x3FF

#define MASK_TIPO 0xE
#define MASK_INF 0x40

////    Color       ////

static color_t color_crear(bool r, bool g, bool b)
{
    color_t color;

    color = (r) ?  MASK_R : 0;              //Aplico la mascara del color si es true y sino debuelvo lo mismo   
    color = (g) ? (color | MASK_G) : color;
    color = (b) ? (color | MASK_B) : color;
    
    return color;
}

void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b)
{
    *r = ((c & MASK_R) == MASK_R) ? ON_COLOR : OFF_COLOR;
    *g = ((c & MASK_G) == MASK_G) ? ON_COLOR : OFF_COLOR;
    *b = ((c & MASK_B) == MASK_B) ? ON_COLOR : OFF_COLOR;
}


////    Tipo de figura      ////

static const char *tipo[] = {
    [ICONO] = "Icono",
    [NIVEL] = "Nivel",
    [SPRITE] = "Sprite",
    [PLANETA] = "Planeta",
    [BASE] = "Base",
    [COMBUSTIBLE] = "Combustible",
    [TORRETA] = "Torreta",
    [REACTOR] = "Reactor",
};

static const char* figura_tipo_a_cadena(figura_tipo_t figura)
{
    return tipo[figura];
}



////    Lectura     ////

typedef struct
{
    char (*nombre)[20];
    bool infinito;
    figura_tipo_t tipo;

    polilinea_t *polis;
    size_t cantidad_polilineas;

}figura_t;

typedef struct{
    float (*puntos)[2];
    color_t color;
    size_t n;
}polilinea_t;


static bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas)
{
    //Leo el nombre
    if(!(fread(nombre, sizeof(char), 20, f) == 20)) return false;

    //Leo las caracteristicas (1 byte)
    uint8_t aux;
    if(!fread(&aux, sizeof(uint8_t), 1, f)) return false;

    //Descodifico nivel bit las caracteristicas
    *tipo = ((aux & MASK_TIPO) >> 1);

    *infinito = ((aux & MASK_INF) >> 6);

    //Leo catidad de polilineas (2 bytes)
    uint16_t aux1;
    if(!fread(&aux1, sizeof(uint16_t), 1, f)) return false;
    *cantidad_polilineas = aux1;

    return true;
}

static polilinea_t *leer_polilinea(FILE *f)
{   
    //Leo encabesado (2 bytes)
    uint16_t enca;
    if(!fread(&enca, sizeof(uint16_t), 1, f)) return NULL;

    //Descodifico el color
    bool r = (enca >> 15) & 1;
    bool g = (enca >> 14) & 1;
    bool b = (enca >> 13) & 1;
    
    color_t color = color_crear(r, g, b);

    //Descodifico numero de polilineas
    size_t n = enca & MASK_NUM;

    polilinea_t *poli = polilinea_crear_vacia(n);
    if (poli == NULL) return NULL;

    polilinea_setter_color(poli, color);

    //Seteo todos los puntos
    float x,y;
    for (size_t i = 0; i < n; i++)
    { 
        if(!fread(&x, sizeof(float), 1, f) || !fread(&y, sizeof(float), 1, f))
        {
            polilinea_destruir(poli);
            return NULL;
        }
       
        polilinea_setter_punto(poli, i, x, y);
    }

    return poli;
}

static figura_t *crear_figura(char *nombre, bool infinito, figura_tipo_t tipo, size_t cantidad_polilineas)
{
    figura_t *fig = malloc(sizeof(figura_t));
    if(fig == NULL) return NULL;

    fig->nombre = realloc(nombre, 20 * sizeof(char));
    if(fig->nombre == NULL)
    {
        free(fig);
        return NULL;
    }

    fig->polis = (cantidad_polilineas * sizeof(polilinea_t *));
    if(fig->polis = NULL)
    {
        free(fig->nombre);
        free(fig);
        return NULL;
    }

    fig->infinito = infinito;
    fig->tipo = tipo;
    fig->cantidad_polilineas = cantidad_polilineas;

    return true;
}

static void *r_figura_destruir(void *fig){
    figura_destruir(fig);
}
static void figura_destruir(figura_t *fig)
{
    free(fig->nombre);
    for (size_t i = 0; i < fig->cantidad_polilineas; i++)
    {

        free(fig->[i].polis)
    }
    free()

}

lista_t *guardar_figuras(char *archivo){

    FILE *f = fopen(*archivo, "rb");
    if(f == NULL) return NULL;

    lista_t *figuras_lista = lista_crear();
    if(figuras_lista == NULL)
    {
        fclose(f);
        return NULL;
    }

    char nombre[20];
    bool infinito;
    figura_tipo_t tipo;
    size_t cantidad_polilineas;

    while (1)
    {
        //Creo figura y guardo en una lista

        if(! leer_encabezado_figura(f, nombre, &tipo, &infinito, &cantidad_polilineas)) break;
        
        figura_t *fig = crear_figura(nombre, infinito, tipo, cantidad_polilineas);
        if(fig == NULL)
        {
            fclose(f);
            return NULL;
        }

        for(size_t i = 0; i < cantidad_polilineas; i++)
        {
            polilinea_t *poli = leer_polilinea(f);
            if(poli == NULL)
            {
                for (size_t j = 0; j < i; j++)
                    polilinea_destruir(fig->polis[j]);
                
                lista_destruir(figuras_lista, r_figura_destruir(fig));
                fclose(f);
                return NULL;
            }

            
            fig->polis[i] = poli;
        }

        if(! lista_agregar_al_final(figuras_lista, fig))
        {                                        
            lista_destruir(figuras_lista, r_figura_destruir(fig));
            fclose(f);
            return NULL;
        }

    }
    fclose(f);
    return figuras_lista;
}
