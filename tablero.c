#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include "tabla.h"
#include "celdas.h"


#define WINDOW_TITLE "buscaminas"
#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 1000
#define IMAGE_FLAGS IMG_INIT_PNG
#define TOTAL_MINAS 10

bool game_over = false;


struct Tablero{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
};


time_t tiempo_inicio;
int segundos_transcurridos = 0;

bool sdl_inicio_tablero(struct Tablero *tablero);
bool load_tablero(struct Tablero *tablero);
void liberar_interfaz(struct Tablero *tablero, int exit_status);


void iniciar_temp() {
    tiempo_inicio = time(NULL);
}

void actualizar_temp(){

	
    if (!game_over && !winner) {
        segundos_transcurridos = (int)difftime(time(NULL), tiempo_inicio);
    
	}

}

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

void colocar_contador(SDL_Renderer *renderer){
	if (TTF_Init() == -1){
		printf("Error al inicializar %s\n", TTF_GetError());
		exit(1);
	}

	TTF_Font *fuente = TTF_OpenFont("fuentes/RubikSprayPaint-Regular.ttf", 24);
	SDL_Color color = {0, 0, 0};
	char texto[12];
	snprintf(texto, sizeof(texto), "%d", TOTAL_MINAS - banderas_utilizadas);



    SDL_Surface* superficie = TTF_RenderText_Solid(fuente, texto, color);
    if (!superficie) {
        printf("Error al renderizar texto: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, superficie);
    if (!textura) {
        printf("Error al crear textura: %s\n", SDL_GetError());
        SDL_FreeSurface(superficie);
        return;
    }

    SDL_Rect destino = {
        .x = 300,
	.y = 150,
	.w = 90,
	.h = 90
    };

    SDL_RenderCopy(renderer, textura, NULL, &destino);


    SDL_FreeSurface(superficie);
    SDL_DestroyTexture(textura);

	TTF_CloseFont(fuente);
	TTF_Quit();

	
}

void colocar_temporizador(SDL_Renderer *renderer){
	if (TTF_Init() == -1){
		printf("Error al inicializar %s\n", TTF_GetError());
		exit(1);
	}

	TTF_Font *fuente = TTF_OpenFont("fuentes/Bitcount.ttf", 24);
	SDL_Color color = {255, 0, 0, 255};
	char texto[12];
	snprintf(texto, sizeof(texto), "%d", segundos_transcurridos);





    SDL_Surface* superficie = TTF_RenderText_Solid(fuente, texto, color);
    if (!superficie) {
        printf("Error al renderizar texto: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, superficie);
    if (!textura) {
        printf("Error al crear textura: %s\n", SDL_GetError());
        SDL_FreeSurface(superficie);
        return;
    }

    SDL_Rect destino = {
        .x = 800,
	.y = 150,
	.w = 90,
	.h = 90
    };

	if (game_over || winner){
		SDL_Rect destino = {
			.x = 510,
			.y = 750,
			.w = 90,
			.h = 90
	
		};
		SDL_RenderCopy(renderer, textura, NULL, &destino);
		SDL_FreeSurface(superficie);
    		SDL_DestroyTexture(textura);

		TTF_CloseFont(fuente);
		TTF_Quit();


	}
	else{

   	 	SDL_RenderCopy(renderer, textura, NULL, &destino);


   	 	SDL_FreeSurface(superficie);
    		SDL_DestroyTexture(textura);

		TTF_CloseFont(fuente);
		TTF_Quit();

	}
	
}

void gameover_check(struct Tablero *tablero, SDL_Renderer *renderer){
	if (game_over){
		tablero->background = IMG_LoadTexture(tablero->renderer, "images/gameover.png");
	
	}
}

void texture_winner(struct Tablero *tablero, SDL_Renderer *renderer){
	if (winner){
		tablero->background = IMG_LoadTexture(tablero->renderer, "images/winner.png");
	}
}

