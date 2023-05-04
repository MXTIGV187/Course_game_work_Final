#include <stdio.h>
#include <SDL.h>
#include "functions.h"
#include "Animation.h"
void playerAnimInit(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* screen_surface,SDL_Rect* player_rect, SDL_Rect* back_rect) {
	SDL_Texture* player_tex_run = loadTextureFromFile("R", player_rect, window, renderer, screen_surface);
	player_rect->w = player_rect->h;

	SDL_Texture* player_tex_idle = loadTextureFromFile("john_idle.png", player_rect, window, renderer, screen_surface);
	player_rect->w = player_rect->h;


	SDL_Texture* back_tex = loadTextureFromFile("back.jpg", back_rect, window, renderer, screen_surface);

}

