#include <SDL.h>
#include <stdio.h>
#include "Player.h"
#include "common_parametrs.h"

Player* PlayerInit(int hp, int score, float x, float y, bool is_die, bool is_jump, bool upToPlatform)
{
	Player* player = (Player*)malloc(sizeof(Player));
	player->hp = hp;
	player->score = score;
	player->x = x;
	player->y = y;
	player->is_jump = is_jump;
	player->is_die = is_die;
	player->upToPlatform = upToPlatform;
	return player;
}

mainPhysics* PhysInit(float speed, float gravity)
{
	mainPhysics* mainPhys = (mainPhysics*)malloc(sizeof(mainPhysics));
	mainPhys->gravity = gravity;
	mainPhys->speed = speed;
	return mainPhys;
}
Enemy* EnemyInit(int hp, float x, float y, bool is_die, bool is_jump)
{
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	enemy->hp = hp;
	enemy->x = x;
	enemy->y = y;
	enemy->is_die = is_die;
	return enemy;
}


void HitBox(SDL_FRect* enemyRect, SDL_FRect* CollisArray, Enemy* enemy, mainPhysics* mainPhys, int& dt, int& sizeArray)
{
	SDL_FRect* CollisRect = checkCollision(enemyRect, CollisArray, sizeArray);
	if (SDL_HasIntersectionF(enemyRect, CollisRect))
	{

		if (enemyRect->y + enemyRect->h - 10 > CollisRect->y)
		{
			enemy->y += mainPhys->gravity * dt / 1000;
			enemy->is_jump = 1;
		}

		enemy->is_jump = 0;
	}
	else enemy->y += mainPhys->gravity * dt / 1000;
}
SDL_FRect* checkCollision(SDL_FRect* playerRect, SDL_FRect* CollisArray, int& sizeArray)
{
	SDL_FRect* CollisRect = NULL;
	for (int i = 0; i < sizeArray; i++)
	{
		if (SDL_HasIntersectionF(playerRect, &CollisArray[i]))
		{
			CollisRect = &CollisArray[i];
			printf("%d ", i);
			break;
		}
	}
	return CollisRect;
}



void PlayerMove(Player* player, float& last_y, float& new_y, float& dy, int& dt, bool& isup,
	bool& isdown, bool& isleft, bool& isright, mainPhysics* mainPhys, SDL_FRect* playerRect, SDL_FRect* CollisArray, int& sizeArray)
{
	SDL_FRect* CollisRect = checkCollision(playerRect, CollisArray, sizeArray);
	if (SDL_HasIntersectionF(playerRect, CollisRect))
	{
		if (CollisRect->h != 5)
		{
			player->upToPlatform = 0;
			if (playerRect->y + playerRect->h - 10 > CollisRect->y)
			{
				player->y += mainPhys->gravity * dt / 1000;
				player->is_jump = 1;
				isup = 0;
			}
			last_y = player->y;
			player->is_jump = 0;
			dy = 0;
		}
		else
		{
			if (playerRect->y + playerRect->h <= CollisRect->y + CollisRect->h && !isup)
			{
				player->upToPlatform = 1;
			}

			if (player->upToPlatform == 1)
			{
				last_y = player->y;
				player->is_jump = 0;
				dy = 0;
				if ((playerRect->y + playerRect->h) - (CollisRect->y + CollisRect->h) > 10)
				{
					player->y += mainPhys->gravity * dt / 1000;
					player->is_jump = 1;
					isup = 0;
				}
			}
		}


	}

	if (isup)
	{
		if (player->is_jump == 0)
		{
			player->y -= mainPhys->gravity * dt / 1000;
			new_y = player->y;
			dy = last_y - new_y;
			if (dy >= 300)
				isup = 0;
		}
		else
		{
			player->y += mainPhys->gravity * dt / 1000;
		}

	}
	else
	{
		player->is_jump = 1;
		if (!SDL_HasIntersectionF(playerRect, CollisRect))
			player->y += mainPhys->gravity * dt / 1000;
	}
	if (isdown)
	{
		if (SDL_HasIntersectionF(playerRect, CollisRect))
			if (CollisRect->h == 5.0)
			{
				player->y += 9;
			}
	}
	if (isleft)
	{
		player->x -= mainPhys->speed * dt / 1000;
		if (SDL_HasIntersectionF(playerRect, CollisRect))
		{
			if (playerRect->y + playerRect->h - 10 > CollisRect->y && CollisRect->h != 5)
			{
				player->x += mainPhys->speed * dt / 1000;
				player->is_jump = 1;
			}
			if (playerRect->x >= CollisRect->x+CollisRect->w)
				player->x += mainPhys->speed * dt / 1000;
		}

	}
	if (isright)
	{
		player->x += mainPhys->speed * dt / 1000;

		if (SDL_HasIntersectionF(playerRect, CollisRect))
		{
			if (playerRect->y + playerRect->h - 10 > CollisRect->y && CollisRect->h != 5)
			{
				player->x -= mainPhys->speed * dt / 1000;
				player->is_jump = 1;
			}
			if (playerRect->x + playerRect->w <= CollisRect->x)
				player->x -= mainPhys->speed * dt / 1000;
		}
	}
	
}
