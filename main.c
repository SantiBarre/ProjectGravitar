#include <SDL2/SDL.h>
#include <stdbool.h>

#include "nave.h"
#include "polilinea.h"
#include "lista.h"
#include "config.h"
#include "figuras.h"
#include "dibujado.h"

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
    if (figuras_lista == NULL){
        perror("No se pudo guardar las figuras!");
        return 1;
    }
    nivel_t elegir_nivel; //ACA PARA EL SWITCH CASE
    elegir_nivel = 1;
    // Mi nave:
    
    nave_t *nave = nave_crear();
    
    



    // Queremos que todo se dibuje escalado por f:
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
                        nave->chorro = true;
                        
                        break;
                    case SDLK_DOWN:

                        break;
                    case SDLK_RIGHT:
                        
                        break;
                    case SDLK_LEFT:
                        
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Apagamos el chorro:
                        nave->chorro = false;
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
        
        //dibujar_figura(estrella, f, VENTANA_ANCHO/2, VENTANA_ALTO/2, 0, renderer);
        /*for (size_t i=0; i < estrella->cantidad_polilineas; i++){
            dibujar_polilinea(estrella->polis[i],f,VENTANA_ANCHO/2,VENTANA_ALTO/2,renderer);
        }*/

        dibujado_de_nivel(figuras_lista,nave,elegir_nivel,renderer);
        

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

