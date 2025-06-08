//interfaz grafica del buscaminas
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_TITLE "buscaminas"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600 


struct Juego {
	SDL_Window *window;
	SDL_Renderer *renderer;
};

bool sdl_inicio(struct Juego *juego);
void liberar_interfaz(struct Juego *juego, int exit_status);

void liberar_interfaz(struct Juego *juego, int exit_status) {
	SDL_DestroyRenderer(juego -> renderer);
	SDL_DestroyWindow(juego->window);
	SDL_Quit();
	exit(exit_status);

}

bool sdl_inicio(struct Juego *juego) {
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		printf("Error de iniciando SDL: %s\n", SDL_GetError());
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

int main(){
	struct Juego juego = {
		.window = NULL,
		.renderer = NULL,	
	};

	if (sdl_inicio(&juego)) {
		liberar_interfaz(&juego, EXIT_FAILURE);
		printf("no se logro :,[\n");
		exit(1);
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
		SDL_RenderPresent(juego.renderer);
		SDL_Delay(16);
	}
	liberar_interfaz(&juego, EXIT_SUCCESS);
	printf("SE LOGRO! :D\n");


	return 0;
};
