//header para tablero
#include <SDL2/SDL_render.h>
#include <stdbool.h>

extern bool game_over;


struct Tablero{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
};

void liberar_interfaz(struct Tablero *tablero, int exit_status);
bool sdl_inicio_tablero(struct Tablero *tablero);
bool load_tablero(struct Tablero *tabero);
void dibujar_celdas();
void colocar_contador(SDL_Renderer *renderer);
void colocar_temporizador(SDL_Renderer *renderer);
void iniciar_temp();
void actualizar_temp();
void gameover_check(struct Tablero *tablero, SDL_Renderer *renderer);
void texture_winner(struct Tablero *tablero, SDL_Renderer *renderer);


