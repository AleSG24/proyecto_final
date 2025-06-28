#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

void crear_celdas();
void colocar_minas();
void minas_vecinas();
void renderizar_celdas(SDL_Renderer *renderer);
void load_bandera(SDL_Renderer *renderer);
void detect_click(int mouse_x, int mouse_y, Uint8 boton);

