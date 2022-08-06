#include "figuras.h" 
#include "polilinea.h"
#include "lista.h"

#include <stddef.h> 
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
    *r = ((c&4)/4)*255;
    *g = ((c&2)/2)*255;
    *b = (c&1)*255;
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

const char* figura_tipo_a_cadena(figura_tipo_t figura)
{
    return tipo[figura];
}

////    Lectura     ////

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

//// Lectura de achivo


static figura_t *crear_figura_vacia(size_t cantidad_polilineas)
{
    figura_t *fig = malloc(sizeof(figura_t));
    if(fig == NULL) return NULL;

    fig->nombre = calloc(21, sizeof(char));
    if(fig->nombre == NULL)
    {
        free(fig);
        return NULL;
    }

    fig->polis = calloc(cantidad_polilineas, sizeof(polilinea_t *));
    if(fig->polis == NULL)
    {
        free(fig->nombre);
        free(fig);
        return NULL;
    }
    fig->cantidad_polilineas = cantidad_polilineas;

    return fig;
}

static void rp_figura_destruir(figura_t *fig)
{
    free(fig->nombre);
    for (size_t i = 0; i < fig->cantidad_polilineas; i++)
        polilinea_destruir(fig->polis[i]);
    free(fig->polis);
    free(fig);
    return;
}

void figura_destruir(void *fig)
{
    rp_figura_destruir((figura_t *)fig);
}


lista_t *guardar_figuras(char *archivo)
{

    FILE *f = fopen(archivo, "rb");
    if(f == NULL) {
        perror("No se pudo abrir el archivo!");
        return NULL;
    }
    
    lista_t *figuras_lista = lista_crear();
    if(figuras_lista == NULL)
    {
        perror("No se pudo crear una lista!");
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
        
        figura_t *fig = crear_figura_vacia(cantidad_polilineas);
        if (fig == NULL)
        {
            perror("No se pudo crear una figura!");
            lista_destruir(figuras_lista, figura_destruir);
            fclose(f);
            return NULL;
        }
    
        strcpy(*(fig->nombre), nombre); //LE METI UN * PARA PROBAR
        fig->infinito = infinito;
        fig->tipo = tipo;

        for(size_t i = 0; i < cantidad_polilineas; i++)
        {
  
            polilinea_t *pol = leer_polilinea(f);
            if(pol == NULL)
            {
                perror("No se pudo crear una polilinea!");
                for (size_t j = 0; j < i; j++)
                    polilinea_destruir(fig->polis[j]);
                
                lista_destruir(figuras_lista, figura_destruir);
                fclose(f);
                return NULL;
            }
            fig->polis[i] = pol;
        }

        if(!lista_agregar(figuras_lista, fig))
        {                                        
            perror("No se pudo agregar algo a una lista!");
            lista_destruir(figuras_lista, figura_destruir);
            fclose(f);
            return NULL;
        }

    }
    
    fclose(f);
    return figuras_lista;
}

/*figura_t *figura_rotar(figura_t *fig,double radianes){
    for (size_t i = 0; i <= fig->cantidad_polilineas; i++){
        rotar(fig->polis[i]->puntos,fig->polis[i]->n,radianes);
    }
    return fig;

}*/


figura_t *obtener_figura(char *nom, lista_t *l)
{

    lista_iterador_t *li;

    for(
        li = lista_iterador_crear(l);
        !lista_iterador_termino(li);
        lista_iterador_siguiente(li)
    )
    {

        figura_t *dato = lista_iterador_actual(li);

            if (strcmp(*dato->nombre, nom) == 0)
            {
                lista_iterador_destruir(li);
                return dato;
            }
    }

    lista_iterador_destruir(li);
    return NULL;
}

/*bool colision_figuras (figura_t *figuraA,figura_t *figuraB){
    for (size_t i=0;i <= figuraA->cantidad_polilineas; i++){
        for (size_t j=0; j<= figuraB->cantidad_polilineas; j++){
            if (colision_polilineas(figuraA->polis[i]->puntos,figuraA->polis[i]->n,figuraB->polis[j]->puntos,figuraB->polis[j]->n )){
                return true;
            }
        }
    }
    return false;
}*/