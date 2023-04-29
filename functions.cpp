#include <SDL.h>
#include <stdio.h>
#include "functions.h"
#include "common_parametrs.h"

void Init(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** screen_surface)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Init Error\n");
		exit(1);
	}

	*window = SDL_CreateWindow("NES", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);


	if (window == NULL)
	{
		printf("Window Error\n");
		exit(1);
	}

	*renderer = SDL_CreateRenderer(*window, -1, 0);

	if (renderer == NULL)
	{
		printf("Renderer Error\n");
		exit(1);
	}

}

void Quit(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** screen_surface) 
{
	if (screen_surface != NULL)
		SDL_FreeSurface(*screen_surface);

	if (renderer != NULL)
		SDL_DestroyRenderer(*renderer);

	if (window != NULL)
		SDL_DestroyWindow(*window);

	SDL_Quit();
}
