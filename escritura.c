#include <stddef.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

#include "escritura.h"
#include "caracteres.h"
#include "nave.h"
#include "config.h"

typedef struct{
    const int (*puntos)[2];
    size_t n;
}car_t;

// Función para intercambiar dos números
void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
// Función para invertir `buffer[i…j]`
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}
 
// Función iterativa para implementar la función `itoa()` en C
char* itoa(int value, char* buffer, int base)
{
    // entrada inválida
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // considera el valor absoluto del número
    int n = abs(value);
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // si el numero es 0
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // Si la base es 10 y el valor es negativo, la string resultante
    // va precedido de un signo menos (-)
    // Con cualquier otra base, el valor siempre se considera sin firmar
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // string de terminación nula
 
    // invertir la string y devolverla
    return reverse(buffer, 0, i - 1);
}


car_t letras[] = {

    [32] = {caracter_espacio, 1},

    [48] = {caracter_0 , 5},
	[49] = {caracter_1 , 2},
	[50] = {caracter_2 , 6},
	[51] = {caracter_3 , 7},
	[52] = {caracter_4 , 5},
	[53] = {caracter_5 , 6},
	[54] = {caracter_6 , 5},
	[55] = {caracter_7 , 3},
	[56] = {caracter_8 , 7},
	[57] = {caracter_9 , 5},

    [65] = {caracter_a , 7},
	[66] = {caracter_b , 12},
	[67] = {caracter_c , 4},
	[68] = {caracter_d , 7},
	[69] = {caracter_e , 7},
	[70] = {caracter_f , 6},
	[71] = {caracter_g , 7},
	[72] = {caracter_h , 6},
	[73] = {caracter_i , 6},
	[74] = {caracter_j , 4},
	[75] = {caracter_k , 6},
	[76] = {caracter_l , 3},
	[77] = {caracter_m , 5},
	[78] = {caracter_n , 4},
	[79] = {caracter_o , 5},
	[80] = {caracter_p , 5},
	[81] = {caracter_q , 9},
	[82] = {caracter_r , 7},
	[83] = {caracter_s , 6},
	[84] = {caracter_t , 4},
	[85] = {caracter_u , 4},
	[86] = {caracter_v , 3},
	[87] = {caracter_w , 5},
	[88] = {caracter_x , 5},
	[89] = {caracter_y , 5},
	[90] = {caracter_z , 4},

};

//Solo toma minusculas
bool dibujar_texto(char *texto, bool color, float escala, float posx, float posy, SDL_Renderer *renderer)
{
    car_t *let;
    
    if(color)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0x00);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
    }
    
    size_t i = 0;
    int c;
    while (texto[i] != '\0')
    {
        c = texto[i];
        let = &letras[c];

        for (size_t i = 0; (i + 1) < let->n; i++)
        {
        
            if (SDL_RenderDrawLine(
                renderer,
                let->puntos[i][0] * escala + posx,
                -let->puntos[i][1] * escala + posy,
                let->puntos[i+1][0] * escala + posx,
                -let->puntos[i+1][1] * escala + posy
                    ) != 0)
            {
                perror("No se pudo dibujar el texto!");
                return false;
            }
        }
        posx += 6 * escala;
        i++;
    }
    return true;
}

bool textos(nave_t *n,  SDL_Renderer *renderer)
{
    bool error = false;

    error += dibujar_texto("SCORE", true, 2.5, 365, 30 , renderer);
    error += dibujar_texto("FUEL", true, 2.5, 375, 55 , renderer);
    error += dibujar_texto("NEXT SHIP", true, 2.5, 300, 80 , renderer);
 
    char combus[10];
    itoa((int)n->combustible, combus, 10);
    error += dibujar_texto(combus, false, 2.5, 200, 55, renderer);

    char puntos[10];
    itoa((int)n->puntos, puntos, 10);
    error += dibujar_texto(puntos, false, 2.5, 450, 80, renderer);

    if(error)
        return false;
    return true;
}

bool punto_mundo(SDL_Renderer *renderer)
{
    bool error = false;

    error += dibujar_texto("2000", true, 2, 680, 110 , renderer); //Mundo 1
    error += dibujar_texto("4000", true, 2, 690, 480 , renderer); //mundo 2
    error += dibujar_texto("6000", true, 2, 125, 550 , renderer); //Mundo 3
    error += dibujar_texto("9000", true, 2, 150, 350 , renderer); //mundo 4
    error += dibujar_texto("8000", true, 2, 120, 125 , renderer); //mundo 5

    if(error)
        return false;
    return true;
}

bool punto_del_mundo(int puntos, SDL_Renderer *renderer)
{
    bool error = false;

    char p[5];
    itoa(puntos, p, 10);

    error += dibujar_texto(p, true, 2, 680, 30 , renderer); //Mundo 1
    error += dibujar_texto("BONUS", false, 2.5, 680, 55 , renderer); //Mundo 1


    if(error)
        return false;
    return true;
}