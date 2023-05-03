#include <SDL.h>
#include <stdio.h>
#include "functions.h"
#include "common_parametrs.h"
#include <SDL_image.h>

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

	int res;
	if ((res = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) == 0)
	{
		printf_s("Couldn't init SDL_Image! Error: %s\n", SDL_GetError());
		system("pause");
		Quit(window, renderer, screen_surface);
	}
	if (res & IMG_INIT_JPG) printf_s("Init JPG library.\n"); else printf_s("Can't Init JPG library!\n");
	if (res & IMG_INIT_PNG) printf_s("Init PNG library.\n"); else printf_s("Can't Init PNG library!\n");



}

void Quit(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** screen_surface) 
{
	if (screen_surface != NULL)
		SDL_FreeSurface(*screen_surface);

	if (renderer != NULL)
		SDL_DestroyRenderer(*renderer);

	if (window != NULL)
		SDL_DestroyWindow(*window);
	IMG_Quit();
	SDL_Quit();
}
