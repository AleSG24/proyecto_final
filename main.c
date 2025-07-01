#include "tabla.h"
#include "celdas.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Renderer *rend;

int main(){
	

	struct Tablero tablero = {
		.window = NULL,
		.renderer = NULL,
		.background = NULL,
	};





	if (sdl_inicio_tablero(&tablero)){
		liberar_interfaz(&tablero, EXIT_FAILURE);
	
	}

	if (load_tablero(&tablero)){
		liberar_interfaz(&tablero, EXIT_FAILURE);
	}




	
	crear_celdas();
	colocar_minas();
	minas_vecinas();
	load_bandera(tablero.renderer);
	iniciar_temp();



		
	

	while (true){
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					liberar_interfaz(&tablero, EXIT_SUCCESS);
					break;
				default:
					break;
			}
		}

		if (event.type == SDL_MOUSEBUTTONDOWN){
			detect_click(event.button.x, event.button.y, event.button.button);
		}

		SDL_RenderClear(tablero.renderer);

		
		SDL_RenderCopy(tablero.renderer, tablero.background, NULL, NULL);

		actualizar_temp();

		renderizar_celdas(tablero.renderer);

		check_color(tablero.renderer);

	//	check_mina(tablero.renderer); //esto era solamente para mostrar la aleatoriedad de las minas y la pantalla de victoria

		cargar_numeros(tablero.renderer);

		colocar_contador(tablero.renderer);

		colocar_temporizador(tablero.renderer);

		gameover_check(&tablero, tablero.renderer);

		check_ganador();
		
		texture_winner(&tablero, tablero.renderer);

	
	
		
		SDL_RenderPresent(tablero.renderer);
	

		
		SDL_Delay(16);
		
	}
	

	liberar_interfaz(&tablero, EXIT_SUCCESS);

	printf("BIEEEEEN\n");
	
	return 0;
}
