#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "caracteres.h"

int **letras[] = {
    [1] =caracter_a;
    [2] =caracter_b;
    [3] =caracter_c;
    [4] =caracter_d;
    [5] =caracter_e;
    [6] =caracter_f;
    [7] =caracter_g;
    [8] =caracter_h;
    [9] =caracter_i;
    [10] =caracter_j;
    [11] =caracter_k;
    [12] =caracter_l;
    [13] =caracter_m;
    [14] =caracter_n;
    [15] =caracter_o;
    [16] =caracter_p;
    [17] =caracter_q;
    [18] =caracter_r;
    [19] =caracter_s;
    [20] =caracter_t;
    [21] =caracter_u;
    [22] =caracter_v;
    [23] =caracter_w;
    [24] =caracter_x;
    [25] =caracter_y;
    [26] =caracter_z;
}

//Solo toma minusculas
int **devolver_letra(char c){
    //Usa ascii por lo tanto a = 97, y al ser letras[0] es apropiado el uso de 97, por lo tanto el ascenso de valores se mantiene igualitario entre la tabla ascii y mi tabla de busqueda.
    int aux = (int) c - 97; 
    return letras[aux];
}

int ***devolver_palabra(char* pal){

    int **l_aux[];
    for (size_t i=0; i<= strlen(pal); i++){
        **l_aux[i] = devolver_letra(pal[i]);
    }
    return l_aux; 
}

#include "caracteres.h"



