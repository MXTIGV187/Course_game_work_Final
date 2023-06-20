#include <SDL.h>
#include <stdio.h>
#include "functions.h"
#include "common_parametrs.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

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

	if (TTF_Init())
	{
		printf_s("Couldn't init SDL_TTF! Error: %s\n", SDL_GetError());
		system("pause");
		Quit(window, renderer, screen_surface);
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
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Tickrate(int& lasttime, int& newtime, int& dt)
{
	newtime = SDL_GetTicks();
	dt = newtime - lasttime;
	lasttime = newtime;
	if (dt < 16)
	{
		SDL_Delay(16 - dt);
		newtime = SDL_GetTicks();
		dt = newtime - lasttime;
	}
	lasttime = newtime;
}

SDL_Texture* loadTextureFromFile(const char* filename, SDL_Rect* rect, SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* screen_surface) {

	SDL_Surface* surface = IMG_Load(filename);
	if (surface == NULL)
	{

		printf("colndt load image eror %s", filename, SDL_GetError());
		system("pause");
		Quit(&window, &renderer, &screen_surface);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	*rect = { 0,0,surface->w,surface->h };
	SDL_FreeSurface(surface);
	return texture;
	}
SDL_Texture* Load_Texture_Font(const char* text, TTF_Font* font, SDL_Rect* rect, SDL_Color color, SDL_Renderer* renderer)
{
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    *rect = { 0, 0, surface->w, surface->h };
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

