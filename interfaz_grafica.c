//interfaz grafica del buscaminas
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_TITLE "buscaminas"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600 
#define IMAGE_FLAGS IMG_INIT_PNG


struct Juego {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
};

bool sdl_inicio(struct Juego *juego);
bool load_media(struct Juego *juego);
void liberar_interfaz(struct Juego *juego, int exit_status);

void liberar_interfaz(struct Juego *juego, int exit_status) {
	SDL_DestroyTexture(juego->background);
	SDL_DestroyRenderer(juego -> renderer);
	SDL_DestroyWindow(juego->window);
	IMG_Quit();
	SDL_Quit();
	exit(exit_status);

}

bool sdl_inicio(struct Juego *juego) {
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		printf("Error de iniciando SDL: %s\n", SDL_GetError());
		return true;
	}

	int img_init = IMG_Init(IMAGE_FLAGS);
	if ((img_init & IMAGE_FLAGS) != IMAGE_FLAGS) {	
		printf("Error iniciando SDL_image: %s\n", IMG_GetError());
		return true;
	}

	juego->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!juego->window){
		printf("Error al crear ventana: %s\n", SDL_GetError());
		return true;
	}

	juego->renderer = SDL_CreateRenderer(juego->window, -1 , 0);
	if (!juego->renderer){
		printf("Error al crear render: %s\n", SDL_GetError());
		return true;
	}

	return false;
}


bool load_media(struct Juego *juego){
	juego->background = IMG_LoadTexture(juego->renderer, "images/background.png");
	
	if (!juego->background) {
		printf("Error al crear textura: %s\n", IMG_GetError());
		return true;
	}
	return false;	
}

int main(){
	struct Juego juego = {
		.window = NULL,
		.renderer = NULL,
		.background = NULL,
	};

	if (sdl_inicio(&juego)) {
		liberar_interfaz(&juego, EXIT_FAILURE);
		printf("no se logro :,[\n");
		exit(1);
	}

	if (load_media(&juego)) {
		liberar_interfaz(&juego, EXIT_FAILURE);
	}
	
	while (true){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch (event.type) {
				case SDL_QUIT:
					liberar_interfaz(&juego, EXIT_SUCCESS);
					break;
				default:
					break;
			}
		}
		SDL_RenderClear(juego.renderer);
		
		SDL_RenderCopy(juego.renderer, juego.background, NULL, NULL);
		
		SDL_RenderPresent(juego.renderer);

		SDL_Delay(16);
	}
	liberar_interfaz(&juego, EXIT_SUCCESS);
	printf("SE LOGRO! :D\n");


	return 0;
};
