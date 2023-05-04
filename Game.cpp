#include <SDL.h>
#include "common_parametrs.h"
#include "functions.h"
#include "Player.h"
#include "Weapon.h"
#include <SDL_image.h>
#include <stdio.h>
#include "Animation.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* screen_surface = NULL;
frameAnim* Run;


int main(int argc, char* argv[])
{
	SDL_Rect dst_rect = { 0,0,0,0 };
	bool running = 1;
	Init(&window, &renderer, &screen_surface);


	SDL_Rect player_rect;
	SDL_Texture* player_tex_run = loadTextureFromFile("Run.png", &player_rect, window, renderer, screen_surface);
	player_rect.w = player_rect.h;

	SDL_Texture* player_tex_idle = loadTextureFromFile("Idle.png", &player_rect, window, renderer, screen_surface);
	player_rect.w = player_rect.h;

	SDL_Rect back_rect;
	SDL_Texture* back_tex = loadTextureFromFile("ass.jpg", &back_rect, window, renderer, screen_surface);

	Player* player = PlayerInit(100, 100, 500, 200, 0, 1);
	mainPhysics* mainPhys = PhysInit(100, 100);

	bool isup = 0, isdown = 0, isleft = 0, isright = 0;

	float dy = 0, last_y = 0, new_y = 0;

	bool animate_run = true;
	bool animate_idle = true;

	int lasttime = SDL_GetTicks();
	int newtime;
	int dt = 0;

	int frame = 0;
	int frame_count = 5;
	int cur_frametime = 0;
	int max_frametime = 1000/10;




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

		


		animate_run = isleft || isright;

		dst_rect = { (int)player->x,(int)player->y,player_rect.w,player_rect.h };
		Tickrate(lasttime, newtime, dt);

#pragma region DRAWING
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, back_tex, &back_rect, NULL);
		if (animate_run) {
			SDL_RenderCopy(renderer, player_tex_run, &player_rect, &dst_rect);
			cur_frametime += dt;
			if (cur_frametime >= max_frametime)
			{
				cur_frametime -= max_frametime;
				frame = (frame + 1) % frame_count;
				player_rect.x = player_rect.w * frame;
			}

		}
		if (animate_run==false)
		{
			SDL_RenderCopy(renderer, player_tex_idle, &player_rect, &dst_rect);
			cur_frametime += dt;
			if (cur_frametime >= max_frametime)
			{
				cur_frametime -= max_frametime;
				frame = (frame + 1) % frame_count;
				player_rect.x = player_rect.w * frame;
			}
		}

		
#pragma endregion


		PlayerMove(player->x, player->y, last_y, player->is_jump, new_y, dy, dt, isup, isdown, isleft, isright, mainPhys->gravity, mainPhys->speed);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(player_tex_run);
	SDL_DestroyTexture(back_tex);
	Quit(&window, &renderer, &screen_surface);
	return 0;

}