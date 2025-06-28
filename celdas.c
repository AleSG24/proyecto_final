#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "celdas.h"


#define COLUMNAS 9
#define FILAS 7
#define ANCHO_VENTANA 768
#define ALTO_VENTANA 768
#define ALTURA_HEADER 96
#define ANCHO_CELDA (ANCHO_VENTANA / COLUMNAS)         
#define ALTO_CELDA ((ALTO_VENTANA - ALTURA_HEADER) / FILAS) 
#define TOTAL_MINAS 10

bool game_over = false;




struct Celdas{
	int pos_fila;
	int pos_columna;
	bool es_mina;
	bool descubierta;
	bool marcada;
	int minas_cercanas;
	SDL_Rect hitbox;
	SDL_Texture *bandera;
	
	
};

struct Celdas tablero[FILAS][COLUMNAS];


void crear_celdas(){
	for (int fila = 0; fila < FILAS; fila++){
		for (int col = 0; col < COLUMNAS; col++){
			tablero[fila][col].pos_fila = fila;
			tablero[fila][col].pos_columna = col;
			tablero[fila][col].hitbox = (SDL_Rect){
				.x = col * ANCHO_CELDA,
				.y = ALTURA_HEADER + fila * ALTO_CELDA,
				.w = ANCHO_CELDA,
				.h = ALTO_CELDA

			};
			tablero[fila][col].descubierta = false;
			tablero[fila][col].marcada = false;
			tablero[fila][col].es_mina = false;
			tablero[fila][col].minas_cercanas = 0;


		};
	};
	

}

void colocar_minas(){
	int minas_colocadas = 0;

	static int inicializando = 0;
	if (!inicializando){
		srand(time(NULL));
		inicializando = 1;
	}

	while (minas_colocadas < TOTAL_MINAS){
		int fila = rand() % FILAS;
		int col = rand() % COLUMNAS;

		if (!tablero[fila][col].es_mina){
			tablero[fila][col].es_mina = true;
			minas_colocadas++;
		}
	}
}

void minas_vecinas(){
	for (int fila = 0; fila < FILAS; fila++){
		for(int col = 0; col < COLUMNAS; col++){
			if (tablero[fila][col].es_mina) continue;

			int conteo = 0;
                        for (int dy = -1; dy <= 1; dy++) {
                          for (int dx = -1; dx <= 1; dx++) {
                            int ny = fila + dy;
                            int nx = col + dx;

                            if (nx >= 0 && nx < COLUMNAS && ny >= 0 &&
                                ny < FILAS) {
                              if (tablero[ny][nx].es_mina)
                                conteo++;
                            }
                          }
                        }

                        tablero[fila][col].minas_cercanas = conteo;
		}

	}
}

void renderizar_celdas(SDL_Renderer* renderer) {
    for (int fila = 0; fila < FILAS; fila++) {
        for (int col = 0; col < COLUMNAS; col++) {
            struct Celdas* celda = &tablero[fila][col];

        
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
            SDL_RenderFillRect(renderer, &celda->hitbox);


            if (celda->marcada && celda->bandera) {
                SDL_RenderCopy(renderer, celda->bandera, NULL, &celda->hitbox);
            }


            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  
            SDL_RenderDrawRect(renderer, &celda->hitbox);
        }
    }
}

void load_bandera(SDL_Renderer* renderer) {
    for (int fila = 0; fila < FILAS; fila++) {
        for (int col = 0; col < COLUMNAS; col++) {
            struct Celdas* celda = &tablero[fila][col];
            
            celda->bandera = IMG_LoadTexture(renderer, "images/bandera.png");
            
            if (!celda->bandera) {
                printf("Error al cargar bandera: %s\n", IMG_GetError());
            }
        }
    }
}

void click_cooldown(float seconds){
	clock_t start = clock();
	clock_t period = seconds * CLOCKS_PER_SEC;
	clock_t elapsed = 0;

	while (elapsed < period){
		elapsed = clock() - start;
	}
}

void detect_click(int mouse_x, int mouse_y, Uint8 boton){
	for (int fila = 0; fila < FILAS; fila++){
		for (int col = 0; col < COLUMNAS; col++){
			SDL_Rect r = tablero[fila][col].hitbox;
			if (SDL_PointInRect(&(SDL_Point){mouse_x, mouse_y}, &r)){
				
				if (boton == SDL_BUTTON_LEFT){
					if (!tablero[fila][col].descubierta && !tablero[fila][col].marcada){
						tablero[fila][col].descubierta = true;
						
						if (!tablero[fila][col].es_mina){
							printf("descubierta\n");
						}
						else{
							printf("tocaste mina\n");
							game_over = true;
						}
					}
				}

				else if (boton == SDL_BUTTON_RIGHT){
					if (!tablero[fila][col].descubierta){
						tablero[fila][col].marcada = !tablero[fila][col].marcada;
						click_cooldown(0.10);
						
					}
				}

				return;


			}
		}
	}
	
}



