#include <SDL.h>
#include "Level.h"

SDL_FRect* InitObject(float x, float y, float w, float h)
{
	SDL_FRect* RectColis = (SDL_FRect*)malloc(sizeof(SDL_FRect));
	RectColis->x = x;
	RectColis->y = y;
	RectColis->w = w;
	RectColis->h = h;
	return RectColis;
}