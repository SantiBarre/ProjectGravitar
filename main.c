#include <SDL2/SDL.h>
#include <stdbool.h>

#include "nave.h"
#include "polilinea.h"
#include "lista.h"
#include "config.h"
#include "figuras.h"

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    int dormir = 0;

    // BEGIN código del alumno
    
    //ESTO COMENTADO ACA ES EL GUARDADO DE FIGURAS EN EL MAIN QUE POR EL MOMENTO NO ME SALE
    lista_t *figuras_lista = guardar_figuras("figuras.bin"); //Esta funcion crea una lista "figuras_lista"
    // Mi nave:
    double nave[][2] = {{8, 0}, {-1, 6}, {-4, 4}, {-4, 2}, {-2, 0}, {-4, -2}, {-4, -4}, {-1, -6}, {8, 0}};
    size_t nave_tam = 9;

    // El chorro de la nave:
    double chorro[][2] = {{-4, 2}, {-8, 0}, {-4, -2}};
    size_t chorro_tam = 3;

    bool chorro_prendido = false;

    // Queremos que todo se dibuje escalado por f:
    float f = 10;
    float prueba_switch = 10;
    float dd=1;
    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Prendemos el chorro:
                        chorro_prendido = true;
                        printf("%f \n",prueba_switch);
                        prueba_switch = 2;
                        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
                        for(int i = 0; i < nave_tam - 1; i++)
                            SDL_RenderDrawLine(
                                renderer,
                                nave[i][0] * f,
                                -nave[i][1] * f ,
                                nave[i+1][0] * f,
                                -nave[i+1][1] * f
                            );

                        trasladar(nave,nave_tam,0,dd);
                        trasladar(chorro,chorro_tam,0,dd);
                        break;
                    case SDLK_DOWN:
                        trasladar(nave,nave_tam,0,-dd);
                        trasladar(chorro,chorro_tam,0,-dd);
                        break;
                    case SDLK_RIGHT:
                        rotar(nave,nave_tam, -PI/4);
                        rotar(chorro,chorro_tam, -PI/4);
                        break;
                    case SDLK_LEFT:
                        rotar(nave,nave_tam, PI/4);
                        rotar(chorro,chorro_tam, PI/4);
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Apagamos el chorro:
                        chorro_prendido = false;
                        break;
                }
            }
            // END código del alumno
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        // BEGIN código del alumno
        // Dibujamos la nave escalada por f en el centro de la pantalla:
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
        for(int i = 0; i < nave_tam - 1; i++)
            SDL_RenderDrawLine(
                renderer,
                nave[i][0] * f + VENTANA_ANCHO/2,
                -nave[i][1] * f + VENTANA_ALTO/2 ,
                nave[i+1][0] * f +VENTANA_ANCHO/2,
                -nave[i+1][1] * f + VENTANA_ALTO/2
            );

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
        for(int i = 0; i < nave_tam - 1; i++)
            SDL_RenderDrawLine(
                renderer,
                nave[i][0] * f ,
                -nave[i][1] * f ,
                nave[i+1][0] * f ,
                -nave[i+1][1] * f
            );

        if(chorro_prendido) {
            // Dibujamos el chorro escalado por f en el centro de la pantalla:
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
            for(int i = 0; i < chorro_tam - 1; i++)
                SDL_RenderDrawLine(
                    renderer,
                    chorro[i][0] * f + VENTANA_ANCHO/2,
                    -chorro[i][1] * f + VENTANA_ALTO/2,
                    chorro[i+1][0] * f + VENTANA_ANCHO/2,
                    -chorro[i+1][1] * f + VENTANA_ALTO/2
                );
        }
        

        // END código del alumno

        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);
        ticks = SDL_GetTicks();
    }

    // BEGIN código del alumno
    
    //ESTO COMENTADO ACA ES LA LIBERACION DE LA MEMORIA DE FIGURAS EN EL MAIN QUE POR EL MOMENTO SALE PERO CON FUGAS
    // Aca se ponen las cosas a destruir / memoria a liberar.
    lista_destruir(figuras_lista, figura_destruir);
    
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

