#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include "celdas.h"
#include "tabla.h"


#define COLUMNAS 10
#define FILAS 8
#define ANCHO_VENTANA 768
#define ALTO_VENTANA 768
#define ALTURA_HEADER 96
#define ANCHO_CELDA (ANCHO_VENTANA / COLUMNAS)         
#define ALTO_CELDA ((ALTO_VENTANA - ALTURA_HEADER) / FILAS) 
#define TOTAL_MINAS 10


int banderas_utilizadas = 0;

bool winner = false;




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
				.x = col * ANCHO_CELDA + 170,
				.y = ALTURA_HEADER + fila * ALTO_CELDA + 190,
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

        
            SDL_SetRenderDrawColor(renderer, 100, 170, 210, 255); 
            SDL_RenderFillRect(renderer, &celda->hitbox);

	


            if (celda->marcada && celda->bandera) {
                SDL_RenderCopy(renderer, celda->bandera, NULL, &celda->hitbox);
            }


            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  
            SDL_RenderDrawRect(renderer, &celda->hitbox);
	
	if (game_over || winner){
		celda->hitbox = (SDL_Rect){0, 0, 0, 0};
			}
	
        }
    }
}

void check_color(SDL_Renderer* renderer){
	for (int fila = 0; fila < FILAS; fila++){
		for (int col = 0; col < COLUMNAS; col++){
			struct Celdas* celda = &tablero[fila][col];
			if (celda->descubierta){

				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderFillRect(renderer, &celda->hitbox);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  
            			SDL_RenderDrawRect(renderer, &celda->hitbox);
			}
		}
	}
}

void check_mina(SDL_Renderer* renderer){
	for (int fila = 0; fila < FILAS; fila++){
		for (int col = 0; col < COLUMNAS; col++){
			struct Celdas* celda = &tablero[fila][col];
			if (celda->es_mina){

				SDL_SetRenderDrawColor(renderer, 255, 105, 180, 255);
				SDL_RenderFillRect(renderer, &celda->hitbox);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  
            			SDL_RenderDrawRect(renderer, &celda->hitbox);
			}
		}
	}
}

void mostrar_numero_celda(SDL_Renderer* renderer, TTF_Font* fuente, int fila, int col) {

    if (!tablero[fila][col].descubierta && tablero[fila][col].es_mina) return;
    if (tablero[fila][col].minas_cercanas == 0) return;

    
    SDL_Color color = {0, 0, 0};  
    char texto[10];
    snprintf(texto, sizeof(texto), "%d", tablero[fila][col].minas_cercanas);

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
        tablero[fila][col].hitbox.x + ANCHO_CELDA / 3,
        tablero[fila][col].hitbox.y + ALTO_CELDA / 5,
        superficie->w,
        superficie->h
    };

    SDL_RenderCopy(renderer, textura, NULL, &destino);


    SDL_FreeSurface(superficie);
    SDL_DestroyTexture(textura);
}


void cargar_numeros(SDL_Renderer *renderer) {
    if (TTF_Init() == -1) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        exit(1);
    }

    TTF_Font *fuente = TTF_OpenFont("fuentes/Roboto.ttf", 24);
    if (!fuente) {
        printf("Error al cargar fuente: %s\n", TTF_GetError());
        TTF_Quit();
        exit(1);
    }

    for (int fila = 0; fila < FILAS; fila++) {
        for (int col = 0; col < COLUMNAS; col++) {
            if (tablero[fila][col].descubierta && !tablero[fila][col].es_mina) {
                mostrar_numero_celda(renderer, fuente, fila, col);
            }
        }
    }

    TTF_CloseFont(fuente);  
    TTF_Quit();             
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
							
						}
						else{
							
							game_over = true;
						}
					}
				}

				else if (boton == SDL_BUTTON_RIGHT){
					if (!tablero[fila][col].descubierta && banderas_utilizadas != TOTAL_MINAS){						
						if (!tablero[fila][col].marcada){
							banderas_utilizadas++;
							                                    
							
						}
						else{
							banderas_utilizadas--;
						}
						tablero[fila][col].marcada = !tablero[fila][col].marcada;
						click_cooldown(0.15);
						
					}
				}

				return;


			}
		}
	}
	
}

void check_ganador(){

	int correctas = 0;

    for (int fila = 0; fila < FILAS; fila++) {
        for (int col = 0; col < COLUMNAS; col++) {
            struct Celdas* celda = &tablero[fila][col];
            
		if (celda->es_mina && celda->marcada){
			correctas++;
			}
            
            
        }
    }
	if (correctas == 10){
		winner = true;
	}
	
}

