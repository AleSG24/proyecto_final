//header para tablero
#include <SDL2/SDL_render.h>


struct Tablero{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
};

void liberar_interfaz(struct Tablero *tablero, int exit_status);
bool sdl_inicio_tablero(struct Tablero *tablero);
bool load_tablero(struct Tablero *tabero);



