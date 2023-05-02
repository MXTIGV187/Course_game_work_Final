#include <SDL.h>
#include "common_parametrs.h"
#include "functions.h"
#include "Player.h"
#include "Weapon.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* screen_surface = NULL;

int main(int argc, char* argv[])
{
	bool running = 1;
	Init(&window, &renderer, &screen_surface);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	mainPhysics* physics = (mainPhysics*)malloc(sizeof(mainPhysics));
	Player* player = PlayerInit(100, 100, 500, 500, 0, 1);
	bool isup = 0, isdown = 0, isleft = 0, isright = 0;
	int lasttime = SDL_GetTicks();
	int newtime;
	int dt = 0;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = 0;
			}

			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_W: isup = 1; break;
				case SDL_SCANCODE_S: isdown = 1; break;
				case SDL_SCANCODE_A: isleft = 1; break;
				case SDL_SCANCODE_D: isright = 1; break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_W: isup = 0; break;
				case SDL_SCANCODE_S: isdown = 0; break;
				case SDL_SCANCODE_A: isleft = 0; break;
				case SDL_SCANCODE_D: isright = 0; break;
				}
				break;
			}
		}

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

		if (isup) player->y -= physics->speed * dt / 1000;
		if (isdown) player->y += physics->speed * dt / 1000;
		if (isleft) player->x -= physics->speed * dt / 1000;
		if (isright) player->x += physics->speed * dt / 1000;

		SDL_RenderPresent(renderer);
	}
	Quit(&window, &renderer, &screen_surface);
	return 0;

}