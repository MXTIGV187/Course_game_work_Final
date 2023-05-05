#include <SDL.h>
#include <stdio.h>
#include "Player.h"
#include "common_parametrs.h"

Player* PlayerInit(int hp, int score, float x, float y, bool is_die, bool is_jump)
{
	Player* player = (Player*)malloc(sizeof(Player));
	player->hp = hp;
	player->score = score;
	player->x = x;
	player->y = y;
	player->is_jump = is_jump;
	player->is_die = is_die;
	return player;
}

mainPhysics* PhysInit(float speed, float gravity)
{
	mainPhysics* mainPhys = (mainPhysics*)malloc(sizeof(mainPhysics));
	mainPhys->gravity = gravity;
	mainPhys->speed = speed;
	return mainPhys;
}

//void HitBox(SDL_FRect* enemyRect, SDL_FRect* Rect, SDL_FRect* Rect1, SDL_FRect* Rect2, Enemy* enemy, mainPhysics* mainPhys, int& dt)
//{
//	if (SDL_HasIntersectionF(enemyRect, Rect) || SDL_HasIntersectionF(enemyRect, Rect1) || SDL_HasIntersectionF(enemyRect, Rect2))
//	{
//
//		enemy->is_jump = 0;
//		if (SDL_HasIntersectionF(enemyRect, Rect))
//		{
//			if (enemyRect->y + enemyRect->h - 10 < Rect->y)
//				enemy->y -= mainPhys->gravity * dt / 1000;
//			else
//			{
//				enemy->y += mainPhys->gravity * dt / 1000;
//			}
//		}
//		if (SDL_HasIntersectionF(enemyRect, Rect1))
//		{
//			if (enemyRect->y + enemyRect->h - 10 < Rect1->y)
//				enemy->y -= mainPhys->gravity * dt / 1000;
//			else
//			{
//				enemy->y += mainPhys->gravity * dt / 1000;
//			}
//		}
//		if (SDL_HasIntersectionF(enemyRect, Rect2))
//		{
//			if (enemyRect->y + enemyRect->h - 10 < Rect2->y)
//				enemy->y -= mainPhys->gravity * dt / 1000;
//			else
//			{
//				enemy->y += mainPhys->gravity * dt / 1000;
//			}
//		}
//	}
//	else enemy->y += mainPhys->gravity * dt / 1000;
//}


void PlayerMove(Player* player, float& last_y, float& new_y, float& dy, int& dt, bool& isup,
	bool& isdown, bool& isleft, bool& isright, mainPhysics* mainPhys, SDL_FRect* Rect, SDL_FRect* Rect1, SDL_FRect* Rect2, SDL_FRect* playerRect)
{

	// Тут сдлеаю пробег по массиву в три строчки чтобы понять с каким прям. столкнулись.
	if (SDL_HasIntersectionF(playerRect, Rect) || SDL_HasIntersectionF(playerRect, Rect1) || SDL_HasIntersectionF(playerRect, Rect2))
	{
		
		player->is_jump = 0;
		if (SDL_HasIntersectionF(playerRect, Rect))
		{
			if (playerRect->y + playerRect->h - 10 < Rect->y)
				player->y -= mainPhys->gravity * dt / 1000;
			else
			{
				player->y += mainPhys->gravity * dt / 1000;
				player->is_jump = 1;
			}
		}
		if (SDL_HasIntersectionF(playerRect, Rect1))
		{
			if (playerRect->y + playerRect->h - 10 < Rect1->y)
				player->y -= mainPhys->gravity * dt / 1000;
			else
			{
				player->y += mainPhys->gravity * dt / 1000;
				player->is_jump = 1;
			}
		}
		if (SDL_HasIntersectionF(playerRect, Rect2))
		{
			if (playerRect->y + playerRect->h - 10 < Rect2->y)
				player->y -= mainPhys->gravity * dt / 1000;
			else
			{
				player->y += mainPhys->gravity * dt / 1000;
				player->is_jump = 1;
			}
		}
		last_y = player->y;
		dy = 0;
	}

	if (isup)
	{
		if (player->is_jump == 0)
		{
			player->y -= mainPhys->gravity * dt / 1000;
			new_y = player->y;
			dy = last_y - new_y;
			if (dy >= 300)
			{
				isup = 0;
				player->is_jump = 1;
				player->y += mainPhys->gravity * dt / 1000;
			}
		}
		else
		{
				player->y += mainPhys->gravity * dt / 1000;
		}

	}
	else
	{
		player->is_jump = 1;
		if (!SDL_HasIntersectionF(playerRect, Rect) || !SDL_HasIntersectionF(playerRect, Rect1) || !SDL_HasIntersectionF(playerRect, Rect2))
			player->y += mainPhys->gravity * dt / 1000;
	}
	if (isdown) player->y += mainPhys->gravity * dt / 1000;
	if (isleft)
	{
		player->x -= mainPhys->speed * dt / 1000;
		if (SDL_HasIntersectionF(playerRect, Rect))
			if (playerRect->y + playerRect->h - 10 > Rect->y)
			{
				player->x += mainPhys->speed * dt / 1000;
				player->is_jump = 1;
			}
		if (SDL_HasIntersectionF(playerRect, Rect1))
			if (playerRect->y + playerRect->h - 10 > Rect1->y)
			{
				player->x += mainPhys->speed * dt / 1000;
				player->is_jump = 1;
			}
		if (SDL_HasIntersectionF(playerRect, Rect2))
			if (playerRect->y + playerRect->h - 10 > Rect2->y)
			{
				player->x += mainPhys->speed * dt / 1000;
				player->is_jump = 1;
			}
	}
	if (isright)
	{
		player->x += mainPhys->speed * dt / 1000;

		if (SDL_HasIntersectionF(playerRect, Rect))
			if (playerRect->y + playerRect->h - 10 > Rect->y)
			{
				player->x -= mainPhys->speed * dt / 1000;
				player->is_jump = 1;
			}
		if (SDL_HasIntersectionF(playerRect, Rect1))
			if (playerRect->y + playerRect->h - 10 > Rect1->y)
			{
				player->x -= mainPhys->speed * dt / 1000;
				player->is_jump = 1;
			}
		if (SDL_HasIntersectionF(playerRect, Rect2))
			if (playerRect->y + playerRect->h - 10 > Rect2->y)
			{
				player->x -= mainPhys->speed * dt / 1000;
				player->is_jump = 1;
			}
	}
}
