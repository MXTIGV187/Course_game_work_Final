#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common_parametrs.h"
#include "functions.h"
#include "Player.h"
#include "Weapon.h"
#include "Animation.h"
#include "Level.h"
#include <SDL_mouse.h>




SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* screen_surface = NULL;
frameAnim* Run;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	SDL_Rect dst_rect = { 0,0,0,0 };
	bool running = 0;
	bool main_menu = 1;
	SDL_Rect dst_enem_rect[100] = { 0,0,0,0 };
	Init(&window, &renderer, &screen_surface);

	int direction = 0;


	SDL_Rect player_rect;
	SDL_Texture* player_tex_run = loadTextureFromFile("Run.png", &player_rect, window, renderer, screen_surface);
	player_rect.w = player_rect.h;

	SDL_Texture* player_tex_idle = loadTextureFromFile("Idle.png", &player_rect, window, renderer, screen_surface);
	player_rect.w = player_rect.h;

	SDL_Rect back_rect;
	SDL_Texture* back_tex = loadTextureFromFile("map.jpg", &back_rect, window, renderer, screen_surface);
	//
	Weapon* boomgun = spawn_weapon(Boomgun, 1, "Rifle", 10, 100, 100);
	Weapon* rifle = spawn_weapon(Rifle, 1, "Rifle", 50, 100, 100);
	Weapon* shotgun = spawn_weapon(Shotgun, 1, "Rifle", 10, 100, 100);
	Weapon* flame = spawn_weapon(FlameThrower, 1, "Rifle", 10, 100, 100);
	//
	Player* player = PlayerInit(100, 100, 300, 300, 0, 1, 0, 0, rifle);
	mainPhysics* mainPhys = PhysInit(150, 250);

	Enemy* enemy[100];
	for (int i = 0; i < ZOMBIE_COUNT; i++)
		enemy[i] = EnemyInit(100, rand() % 2000, 350, 0, 0);

	SDL_Rect enemy_rect;
	SDL_Texture* enemy_tex_idle = loadTextureFromFile("Idle_zombie.png", &enemy_rect, window, renderer, screen_surface);
	enemy_rect.w = enemy_rect.h;


	Uint32 lastShotTime = SDL_GetTicks();

	Bullet* bullet[50];
	SDL_FRect* bulletRect[50];

	SDL_Rect bullet_rect;
	SDL_Texture* bullet_tex = loadTextureFromFile("bullet1.png", &bullet_rect, window, renderer, screen_surface);

	SDL_Rect logo_rect;
	SDL_Texture* logo_tex = loadTextureFromFile("contra-logo.png", &logo_rect, window, renderer, screen_surface);

	SDL_Texture* fire_tex = loadTextureFromFile("Shot_1.png", &player_rect, window, renderer, screen_surface);
	player_rect.w = player_rect.h;
	bool LeftButton = 0;
	int mouseX;
	int mouseY;
	SDL_Rect RectPlay;
	SDL_Rect RectExit;
	while (main_menu)
	{
		SDL_RenderCopy(renderer, logo_tex, &logo_rect, NULL);
		RectPlay.x = 860; RectPlay.y = 700; RectPlay.h = 100; RectPlay.w = 400;

		SDL_SetRenderDrawColor(renderer, 100, 200, 5, 2);
		SDL_RenderFillRect(renderer, &RectPlay);
		SDL_RenderDrawRect(renderer, &RectPlay);

		RectExit.x = 860; RectExit.y = 900; RectExit.h = 100; RectExit.w = 400;
		SDL_SetRenderDrawColor(renderer, 100, 200, 5, 2);
		SDL_RenderFillRect(renderer, &RectExit);
		SDL_RenderDrawRect(renderer, &RectExit);


		SDL_Event event_menu;
		while (SDL_PollEvent(&event_menu))
		{
			if (event_menu.type == SDL_QUIT)
			{
				running = 0;
			}

			switch (event_menu.type)
			{
			case SDL_KEYDOWN:
				switch (event_menu.key.keysym.scancode)
				{
				case SDL_SCANCODE_SPACE: LeftButton = 1; break;
				}
				break;
			case SDL_KEYUP:
				switch (event_menu.key.keysym.scancode)
				{
				case SDL_SCANCODE_SPACE: LeftButton = 0; break;
				}
				break;
			}
		}
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Point point;
		point.x = mouseX; point.y = mouseY;

		if (SDL_PointInRect(&point, &RectExit))
		{

			SDL_SetRenderDrawColor(renderer, 100, 300, 5, 2);
			SDL_RenderFillRect(renderer, &RectExit);
		}



		if (SDL_PointInRect(&point, &RectPlay))
		{

			SDL_SetRenderDrawColor(renderer, 100, 300, 5, 2);
			SDL_RenderFillRect(renderer, &RectPlay);

		}


		if (SDL_PointInRect(&point, &RectPlay) && LeftButton == 1)
		{

			main_menu = 0;
			running = 1;
		}
		if (SDL_PointInRect(&point, &RectExit) && LeftButton == 1)
		{
			main_menu = 0;
		}




		SDL_RenderPresent(renderer);


	}

	int n = 0;
	bool shootUp = 0;
	bool shootDown = 0;
	bool shootLeft = 0;
	bool shootRight = 0;

	for (int i = 0; i < 50; i++)
	{
		bullet[i] = NULL;
		bulletRect[i] = NULL;
	}

	bool isup = 0, isdown = 0, isleft = 0, isright = 0, fire = 0;

	float dy = 0, last_y = 0, new_y = 0;
	float last_enemy_y = 0, new_enemy_y = 0, dy_enemy = 0;

	bool animate_run = true;
	bool animate_idle = true;

	int lasttime = SDL_GetTicks();
	int newtime;
	int dt = 0;

	int frame = 0;
	int frame_count = 6;
	int frame_count_shoot = 4;
	int cur_frametime = 0;
	int max_frametime = 1000 / 10;

	bool reload = 0;
	int debug = 1;

	SDL_FRect* CollisArray[100];
	SDL_FRect* playerRect = InitObject(player->x, player->y, 10, 130);
	SDL_FRect* enemyRect[100];
	SDL_FRect* enemyRadius[100];




	for (int i = 0; i < ZOMBIE_COUNT; i++)
	{
		enemyRect[i] = InitObject(enemy[i]->x, enemy[i]->y, 10, 130);
		enemyRadius[i] = InitObject(enemy[i]->x, enemy[i]->y, 300, 300);
	}
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderClear(renderer);

	int sizeArray = 0;

	MassLoad(*CollisArray, "level1.txt", sizeArray);



	while (running)
	{
		playerRect = InitObject(player->x + 50, player->y + 60, 20, 65);
		for (int i = 0; i < ZOMBIE_COUNT; i++)
		{
			if (enemyRect[i] != NULL)
				enemyRect[i] = InitObject(enemy[i]->x + 30, enemy[i]->y + 30, 35, 65);
			if (enemyRadius[i] != NULL)
				enemyRadius[i] = InitObject(enemy[i]->x - 100, enemy[i]->y - 85, 400, 400);
		}


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
				case SDL_SCANCODE_SPACE: fire = 1; break;
				case SDL_SCANCODE_T: debug++; break;
				case SDL_SCANCODE_R: reload = 1; break;
				case SDL_SCANCODE_W: isup = 1; break;
				case SDL_SCANCODE_S: isdown = 1; break;
				case SDL_SCANCODE_A: isleft = 1; direction = DIR_LEFT; break;
				case SDL_SCANCODE_D: isright = 1; direction = DIR_RIGHT; break;
				case SDL_SCANCODE_UP: shootUp = 1; break;
				case SDL_SCANCODE_DOWN: shootDown = 1; break;
				case SDL_SCANCODE_LEFT: shootLeft = 1; break;
				case SDL_SCANCODE_RIGHT: shootRight = 1; break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_SPACE: fire = 0; break;
				case SDL_SCANCODE_W: isup = 0; break;
				case SDL_SCANCODE_S: isdown = 0; break;
				case SDL_SCANCODE_A: isleft = 0; break;
				case SDL_SCANCODE_D: isright = 0; break;
				case SDL_SCANCODE_UP: shootUp = 0; break;
				case SDL_SCANCODE_DOWN: shootDown = 0; break;
				case SDL_SCANCODE_LEFT: shootLeft = 0; break;
				case SDL_SCANCODE_RIGHT: shootRight = 0; break;
				}
				break;
			}
		}

		animate_run = isleft || isright || isup || isdown;
		for (int i = 0; i < ZOMBIE_COUNT; i++)
			if (enemy[i] != NULL)
				dst_enem_rect[i] = { (int)enemy[i]->x,(int)enemy[i]->y,enemy_rect.w,enemy_rect.h };

		dst_rect = { (int)player->x,(int)player->y,player_rect.w,player_rect.h };
		Tickrate(lasttime, newtime, dt);

#pragma region DRAWING
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, back_tex, &back_rect, NULL);


		if (animate_run) {

			cur_frametime += dt;
			if (cur_frametime >= max_frametime)
			{
				cur_frametime -= max_frametime;
				frame = (frame + 1) % frame_count;
				player_rect.x = player_rect.w * frame;
			}
			if (direction == DIR_RIGHT)
				SDL_RenderCopy(renderer, player_tex_run, &player_rect, &dst_rect);
			else
				SDL_RenderCopyEx(renderer, player_tex_run, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

		}

		else if (fire && animate_run)
		{
			cur_frametime += dt;
			if (cur_frametime >= max_frametime)
			{
				cur_frametime -= max_frametime;
				frame = (frame + 1) % frame_count_shoot;
				player_rect.x = player_rect.w * frame;
			}
			if (direction == DIR_RIGHT)
				SDL_RenderCopy(renderer, fire_tex, &player_rect, &dst_rect);
			else
				SDL_RenderCopyEx(renderer, fire_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

		}

		else if ((animate_run || fire) == false)
		{

			cur_frametime += dt;
			if (cur_frametime >= max_frametime)
			{
				cur_frametime -= max_frametime;
				frame = (frame + 1) % frame_count;
				player_rect.x = player_rect.w * frame;
			}
			if (direction == DIR_RIGHT)
				SDL_RenderCopy(renderer, player_tex_idle, &player_rect, &dst_rect);
			else
				SDL_RenderCopyEx(renderer, player_tex_idle, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

		}
		else if (fire != NULL)
		{

			cur_frametime += dt;
			if (cur_frametime >= max_frametime)
			{
				cur_frametime -= max_frametime;
				frame = (frame + 1) % frame_count_shoot;
				player_rect.x = player_rect.w * frame;
			}
			if (direction == DIR_RIGHT)
				SDL_RenderCopy(renderer, fire_tex, &player_rect, &dst_rect);
			else
				SDL_RenderCopyEx(renderer, fire_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

		}
		if (running) {
			for (int i = 0; i < ZOMBIE_COUNT; i++)
				if (enemy[i] != NULL)
				{
					if (running) {

						cur_frametime += dt;
						SDL_RenderCopy(renderer, enemy_tex_idle, &enemy_rect, &dst_enem_rect[i]);
						if (cur_frametime >= max_frametime)
						{
							cur_frametime -= max_frametime;
							frame = (frame + 1) % frame_count;
							enemy_rect.x = enemy_rect.w * frame;
						}
					}
				}


#pragma endregion


			PlayerMove(player, last_y, new_y, dy, dt, isup, isdown, isleft, isright, mainPhys, playerRect, *CollisArray, sizeArray);
			for (int i = 0; i < ZOMBIE_COUNT; i++)
				if (enemy[i] != NULL)
					EnemyMove(enemy[i], enemyRadius[i], playerRect, enemyRect[i], mainPhys, *CollisArray, sizeArray, dt, last_enemy_y, new_enemy_y, dy_enemy);
			Shoot(newtime, lastShotTime, fire, shootRight, shootLeft, shootUp, shootDown, direction, n, bullet, playerRect, dt, bulletRect, enemy, enemyRect, enemyRadius, player, renderer, bullet_rect, bullet_tex);
			if (reload == 1)
			{
				free(player);
				player = PlayerInit(100, 100, 300, 300, 0, 1, 0, 0, boomgun);
				reload = 0;
			}
			if (debug % 2 == 0)
			{
				SDL_SetRenderDrawColor(renderer, 200, 0, 200, 255);
				for (int i = 0; i < sizeArray; i++)
				{
					SDL_RenderFillRectF(renderer, *CollisArray + i);
					SDL_RenderDrawRectF(renderer, *CollisArray + i);
				}
				//SDL_RenderFillRectF(renderer, playerRect);
				SDL_SetRenderDrawColor(renderer, 200, 150, 200, 255);
				for (int i = 0; i < ZOMBIE_COUNT; i++)
					if (enemyRadius[i] != NULL)
					{
						SDL_RenderFillRectF(renderer, enemyRadius[i]);
						SDL_RenderDrawRectF(renderer, enemyRadius[i]);
					}
				SDL_SetRenderDrawColor(renderer, 200, 0, 200, 255);
				for (int i = 0; i < ZOMBIE_COUNT; i++)
					if (enemyRect[i] != NULL)
					{
						SDL_RenderFillRectF(renderer, enemyRect[i]);
						SDL_RenderDrawRectF(renderer, enemyRect[i]);
					}
				for (int i = 1; i < 10; i++)
				{
					if (bulletRect[i] != NULL)
					{
						SDL_RenderFillRectF(renderer, bulletRect[i]);
						SDL_RenderDrawRectF(renderer, bulletRect[i]);
					}
				}
			}
			SDL_RenderPresent(renderer);
		}


	}

	SDL_DestroyTexture(player_tex_run);
	SDL_DestroyTexture(player_tex_idle);
	SDL_DestroyTexture(enemy_tex_idle);
	SDL_DestroyTexture(back_tex);
	Quit(&window, &renderer, &screen_surface);
	return 0;
}
/*
ПН: Виды 4 оружия, виды 3 противников
ВТ: 3 уровня, всё в файлы перенести
ЧТ: Сейвы и запись рекордов

ПТ: Босс, точки уязвимрсти.
Подбираемые бонусы оружия
*/