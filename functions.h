#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

void Quit(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** screen_surface);
void Init(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** screen_surface);
SDL_Texture* loadTextureFromFile(const char* filename, SDL_Rect* rect, SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* screen_surface);
void Tickrate(int& lasttime, int& newtime, int& dt);

#endif
