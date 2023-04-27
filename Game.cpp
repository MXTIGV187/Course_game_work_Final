#include <SDL.h>
#include "common_parametrs.h"


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);


	SDL_Window* window = SDL_CreateWindow("Orbiting Square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);


	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);



	float window_width = WINDOW_WIDTH;
	float window_height = WINDOW_HEIGHT;

	int lasttime = SDL_GetTicks();
	int newtime;
	int dt = 0;

	SDL_Delay(9000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
	// eto v igrovoi chikl nado.
	//newtime = SDL_GetTicks();
	//delta_time = nemtime - lasttime;
	//lastlime = newtime;
}