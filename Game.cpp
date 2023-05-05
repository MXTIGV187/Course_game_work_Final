#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "common_parametrs.h"
#include "functions.h"
#include "Player.h"
#include "Weapon.h"
#include "Animation.h"
#include "Level.h"

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
	SDL_Texture* back_tex = loadTextureFromFile("map.jpg", &back_rect, window, renderer, screen_surface);

	Player* player = PlayerInit(100, 100, 300, 300, 0, 1);
	mainPhysics* mainPhys = PhysInit(150, 250);

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
	int max_frametime = 1000 / 10;

	bool reload = 0;
	int debug = 1;

	SDL_FRect* CollisRect;
	SDL_FRect* Rect = InitObject(0, WINDOW_HEIGHT / 1.47, WINDOW_WIDTH / 3, 1000);
	SDL_FRect* Rect1 = InitObject(WINDOW_WIDTH / 2.36, WINDOW_HEIGHT / 1.6, WINDOW_WIDTH / 5.96, 1000);
	SDL_FRect* Rect2 = InitObject(WINDOW_WIDTH / 1.49, WINDOW_HEIGHT / 1.24, WINDOW_WIDTH / 5.96, 1000);
	SDL_FRect* playerRect = InitObject(player->x, player->y, 10, 130);

	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderClear(renderer);

	//Â ÊÎÌÌÅÍÒÀÕ ÌÅÃÀ ÄÅÁÀÃ ÌÎÄ!
	while (running)
	{
		playerRect = InitObject(player->x + 50, player->y + 60, 20, 65);


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
				case SDL_SCANCODE_T: debug++; break;
				case SDL_SCANCODE_R: reload = 1; break;
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
		if (animate_run == false)
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


		PlayerMove(player, last_y, new_y, dy, dt, isup, isdown, isleft, isright, mainPhys, Rect, Rect1, Rect2, playerRect);
		if (reload == 1)
		{
			free(player);
			player = PlayerInit(100, 100, 300, 300, 0, 1);
			reload = 0;
		}
		if (debug % 2 == 0)
		{
			SDL_SetRenderDrawColor(renderer, 200, 0, 200, 255);
			SDL_RenderFillRectF(renderer, Rect);

			SDL_RenderDrawRectF(renderer, Rect); 
			SDL_RenderFillRectF(renderer, Rect1);

			SDL_RenderDrawRectF(renderer, Rect1); 
			SDL_RenderFillRectF(renderer, Rect2);

			SDL_RenderDrawRectF(renderer, Rect2);
			SDL_RenderFillRectF(renderer, playerRect);
			
			SDL_RenderDrawRectF(renderer, playerRect);
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(player_tex_run);
	SDL_DestroyTexture(back_tex);
	Quit(&window, &renderer, &screen_surface);
	return 0;

}