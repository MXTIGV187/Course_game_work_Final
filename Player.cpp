
#include <stdio.h>
#include "Player.h"
#include "common_parametrs.h"

Player* PlayerInit(int hp, int score, float x, float y, bool is_die, bool is_jump, bool upToPlatform, int killEnemy, Weapon* weapon)
{
	Player* player = (Player*)malloc(sizeof(Player));
	player->hp = hp;
	player->score = score;
	player->killEnemy = killEnemy;
	player->x = x;
	player->y = y;
	player->is_jump = is_jump;
	player->is_die = is_die;
	player->upToPlatform = upToPlatform;
	player->weapon = weapon;
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
	enemy->is_jump = is_jump;
	return enemy;
}

Bullet* BulletInit(float x, float y, float speed, bool right, bool left, bool up, bool down)
{
	Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
	bullet->x = x;
	bullet->y = y;
	bullet->up = up;
	bullet->right = right;
	bullet->left = left;
	bullet->down = down;
	bullet->speed = speed;
	return bullet;
}

SDL_FRect* checkCollision(SDL_FRect* playerRect, SDL_FRect* CollisArray, int& sizeArray)
{
	SDL_FRect* CollisRect = NULL;
	for (int i = 0; i < sizeArray; i++)
	{
		if (SDL_HasIntersectionF(playerRect, &CollisArray[i]))
		{
			CollisRect = &CollisArray[i];
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
		if (SDL_HasIntersectionF(playerRect, CollisRect))
			if (CollisRect->h == 5)
				if (playerRect->y + playerRect->h >= CollisRect->y + CollisRect->h)
					player->y -= mainPhys->gravity * dt / 1000;

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
		}
	}

}

void EnemyMove(Enemy* enemy, SDL_FRect* enemyRadius, SDL_FRect* playerRect, SDL_FRect* enemyRect, mainPhysics* mainPhys, SDL_FRect* CollisArray, int& sizeArray, int& dt,
	float& last_enemy_y, float& new_enemy_y, float& dy_enemy)
{
	SDL_FRect* CollisRect = checkCollision(enemyRect, CollisArray, sizeArray);
	if (SDL_HasIntersectionF(enemyRect, CollisRect))
	{
		if (enemyRect->y + enemyRect->h - 10 > CollisRect->y)
		{
			enemy->y += mainPhys->gravity * dt / 1000;
			enemy->is_jump = 1;
		}
		else
		{
			enemy->is_jump = 0;
			last_enemy_y = enemy->y;
			dy_enemy = 0;
			enemy->is_jump_right = 0;
			enemy->is_jump_left = 0;
		}

		if (enemyRect->x + enemyRect->w >= CollisRect->x + CollisRect->w)
		{
			enemy->x += (mainPhys->speed - 50) * dt / 1000;
			enemy->y -= mainPhys->gravity * dt / 1000;
			enemy->is_jump_right = 1;
			enemy->is_jump = 1;
		}
		if (enemyRect->x <= CollisRect->x)
		{
			enemy->x -= (mainPhys->speed - 50) * dt / 1000;
			enemy->y -= mainPhys->gravity * dt / 1000;
			enemy->is_jump_left = 1;
			enemy->is_jump = 1;
		}
	}
	else if (enemy->is_jump == 0) enemy->y += mainPhys->gravity * dt / 1000;

	if (enemy->is_jump == 1)
	{
		enemy->y -= mainPhys->gravity * dt / 1000;
		new_enemy_y = enemy->y;
		dy_enemy = last_enemy_y - new_enemy_y;
		if (dy_enemy >= 300)
		{
			enemy->is_jump = 0;
		}
	}
	if (enemy->is_jump_right)
	{
		enemy->x += (mainPhys->speed - 50) * dt / 1000;
	}
	if (enemy->is_jump_left)
	{
		enemy->x -= (mainPhys->speed - 50) * dt / 1000;
	}
	if (!enemy->is_jump_right && !enemy->is_jump_left)
		if (SDL_HasIntersectionF(enemyRadius, playerRect))
		{
			if (playerRect->x + playerRect->w <= enemyRect->x)
				enemy->x -= (mainPhys->speed - 50) * dt / 1000;
			if (playerRect->x + playerRect->w >= enemyRect->x + enemyRect->w)
				enemy->x += (mainPhys->speed - 50) * dt / 1000;
		}
}

void BackGround_move(SDL_FRect* CollisArray, Player* player, int& sizeArray, bool& isleft, bool& isright) {

	if (isleft) {
		for (int i = 0; i < sizeArray; i++) {
			CollisArray[i].x++;

		}
	}
	if (isright) {
		for (int i = 0; i < sizeArray; i++) {
			CollisArray[i].x--;

		}
	}
}
