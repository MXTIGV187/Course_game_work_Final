#include <SDL.h>
#include "common_parametrs.h"
#include "functions.h"
#include "Player.h"
#include "Weapon.h"
#include <SDL_image.h>
#include <stdio.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* screen_surface = NULL;


SDL_Texture* loadTextureFromFile(const char* filename, SDL_Rect* rect) {
	
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

int main(int argc, char* argv[])
{
	SDL_Rect dst_rect = { 0,0,0,0 };
	bool running = 1;
	Init(&window, &renderer, &screen_surface);


	SDL_Rect player_rect;
	SDL_Texture* player_tex = loadTextureFromFile("Idle.png", &player_rect);
	player_rect.w = player_rect.h;


	SDL_Rect back_rect;
	SDL_Texture* back_tex = loadTextureFromFile("ass.jpg", &back_rect);


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

		dst_rect = { (int)player->x,(int)player->y,100,100};

#pragma region DRAWING
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, back_tex, &back_rect, NULL);
		SDL_RenderCopy(renderer, player_tex, &player_rect, &dst_rect);
#pragma endregion

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

		if (isup) player->y -= 100  * dt / 1000;
		if (isdown) player->y += 100 * dt / 1000;
		if (isleft) player->x -= 100 * dt / 1000;
		if (isright) player->x += 100 * dt / 1000;

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(player_tex);
	SDL_DestroyTexture(back_tex);
	Quit(&window, &renderer, &screen_surface);
	return 0;

}