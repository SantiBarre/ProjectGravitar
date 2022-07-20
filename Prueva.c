#include "figuras.h" 
#include "lista.h"
#include <stdio.h>

int main(int argc, char *argv[])
{

    if(argc != 2)
    {
        fprintf(stderr, "El programa se ejecuta como :  ./%s <archivo> /n", argv[0]);
        return 1;
    }

    lista_t *figuras = guardar_figuras(argv[1]);
    if(figuras == NULL)
    {
        fprintf(stderr, "Error de memoria /n");
        return 1;
    }

    

    return 0;
}