#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include "tabla.h"
#include "celdas.h"


#define WINDOW_TITLE "buscaminas"
#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 900
#define IMAGE_FLAGS IMG_INIT_PNG

struct Tablero{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
};








bool sdl_inicio_tablero(struct Tablero *tablero);
bool load_tablero(struct Tablero *tablero);
void liberar_interfaz(struct Tablero *tablero, int exit_status);

void liberar_interfaz(struct Tablero *tablero, int exit_status){
	SDL_DestroyTexture(tablero->background);
	SDL_DestroyWindow(tablero->window);
	SDL_DestroyRenderer(tablero->renderer);
	IMG_Quit();
	SDL_Quit();
	exit(exit_status);

}

bool sdl_inicio_tablero(struct Tablero *tablero){
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		printf("SDL_Tablero fallo: %s\n", SDL_GetError());
		return true;
	}

	int img_init = IMG_Init(IMAGE_FLAGS);

        if ((img_init & IMG_INIT_PNG) != IMAGE_FLAGS) {
          printf("Error Image TAblero: %s\n", IMG_GetError());
          return true;
        }

        tablero->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	
	if (!tablero->window){
		printf("No cargo el tablero :[");
		return true;
	}

	tablero->renderer = SDL_CreateRenderer(tablero->window, -1, 0);
	if (!tablero->renderer){
		printf("no renderizo el tablero :[");
		return true;
	}

	return false;
}

bool load_tablero(struct Tablero *tablero){
	tablero->background = IMG_LoadTexture(tablero->renderer, "images/tablero.png");
	
	if (!tablero->background){
		printf("no cargo la imagen :[");
		return true;
	}
	return false;
}



