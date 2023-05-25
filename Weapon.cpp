#include <stdlib.h>
#include <math.h>
#include "Weapon.h"
#include "common_parametrs.h"
#include "Level.h"

Weapon* spawn_weapon(WeaponType type, int id, const char* name, int damage, float x, float y)
{
	Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
	weapon->id = id;
	weapon->type = type;
	weapon->name = name;
	weapon->damage = damage;
	weapon->x = x;
	weapon->y = y;
	return weapon;
}

void Shoot(int& newtime, Uint32& lastShotTime, bool& fire, bool& shootRight, bool& shootLeft, bool& shootUp, bool& shootDown, int& direction, int& n, Bullet** bullet, SDL_FRect* playerRect,
	int& dt, SDL_FRect** bulletRect, Enemy** enemy, SDL_FRect** enemyRect, SDL_FRect** enemyRadius, Player* player, SDL_Renderer* renderer, SDL_Rect bullet_rect, SDL_Texture* bullet_tex)
{
	if (fire)
	{
		if (newtime - lastShotTime >= 300)
			if (player->weapon->type == Rifle)
			{
				if (shootRight || shootLeft || shootUp || shootDown)
				{
					if (shootRight == 1)
					{
						direction = DIR_RIGHT;
						if (shootUp == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 1, 0, true, 0, 0);
						else if (shootDown == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 1, true, 0, 0);
						else
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 0, true, 0, 0);

					}
					else if (shootLeft == 1)
					{
						direction = DIR_LEFT;
						if (shootUp == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 1, 0, true, 0, 0);
						else if (shootDown == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 1, true, 0, 0);
						else
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 0, true, 0, 0);
					}
					else if (shootUp == 1)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 0, 1, 0, true, 0, 0);
					else if (shootDown == 1)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 0, 0, 1, true, 0, 0);
				}
				else
				{
					if (direction == DIR_LEFT)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 0, true, 0, 0);
					if (direction == DIR_RIGHT)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 0, true, 0, 0);
				}
				lastShotTime = SDL_GetTicks();
			}
		if (newtime - lastShotTime >= 1000)
			if (player->weapon->type == Shotgun)
			{
				if (shootRight || shootLeft || shootUp || shootDown)
				{
					if (shootRight == 1)
					{
						direction = DIR_RIGHT;

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 1, 0, 0, 0, true, 1, 0);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 1, 0, 0, 0, true, 0, 1);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 1, 0, 0, 0, true, 0, 0);

					}
					else if (shootLeft == 1)
					{
						direction = DIR_LEFT;

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 0, 1, 0, 0, true, 1, 0);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 0, 1, 0, 0, true, 0, 1);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 0, 1, 0, 0, true, 0, 0);
					}
					else if (shootUp == 1)
					{
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 0, 1, 1, 0, true, 1, 0);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 1, 0, 1, 0, true, 1, 0);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 0, 0, 1, 0, true, 1, 0);
					}
					else if (shootDown == 1)
					{
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 0, 1, 0, 1, true, 0, 1);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 1, 0, 0, 1, true, 0, 1);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 0, 0, 0, 1, true, 0, 1);
					}
				}
				else
				{
					if (direction == DIR_LEFT)
					{
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 0, 1, 0, 0, true, 1, 0);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 0, 1, 0, 0, true, 0, 1);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 0, 1, 0, 0, true, 0, 0);
					}
					if (direction == DIR_RIGHT)
					{
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 1, 0, 0, 0, true, 1, 0);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 1, 0, 0, 0, true, 0, 1);

						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 400, 1, 0, 0, 0, true, 0, 0);
					}

				}

				lastShotTime = SDL_GetTicks();
			}
		if (newtime - lastShotTime >= 300)
			if (player->weapon->type == FlameThrower)
			{
				if (shootRight || shootLeft || shootUp || shootDown)
				{
					if (shootRight == 1)
					{
						direction = DIR_RIGHT;
						if (shootUp == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 1, 0, true, 0, 0);
						else if (shootDown == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 1, true, 0, 0);
						else
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 0, true, 0, 0);

					}
					else if (shootLeft == 1)
					{
						direction = DIR_LEFT;
						if (shootUp == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 1, 0, true, 0, 0);
						else if (shootDown == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 1, true, 0, 0);
						else
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 0, true, 0, 0);
					}
					else if (shootUp == 1)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 0, 1, 0, true, 0, 0);
					else if (shootDown == 1)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 0, 0, 1, true, 0, 0);
				}
				else
				{
					if (direction == DIR_LEFT)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 0, true, 0, 0);
					if (direction == DIR_RIGHT)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 0, true, 0, 0);
				}
				lastShotTime = SDL_GetTicks();
			}
		if (newtime - lastShotTime >= 1000)
			if (player->weapon->type == Boomgun)
			{
				if (shootRight || shootLeft || shootUp || shootDown)
				{
					if (shootRight == 1)
					{
						direction = DIR_RIGHT;
						if (shootUp == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 1, 0, true, 0, 0);
						else if (shootDown == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 1, true, 0, 0);
						else
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 0, true, 0, 0);

					}
					else if (shootLeft == 1)
					{
						direction = DIR_LEFT;
						if (shootUp == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 1, 0, true, 0, 0);
						else if (shootDown == 1)
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 1, true, 0, 0);
						else
							bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 0, true, 0, 0);
					}
					else if (shootUp == 1)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 0, 1, 0, true, 0, 0);
					else if (shootDown == 1)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 0, 0, 1, true, 0, 0);
				}
				else
				{
					if (direction == DIR_LEFT)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 0, true, 0, 0);
					if (direction == DIR_RIGHT)
						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 0, true, 0, 0);
				}
				lastShotTime = SDL_GetTicks();
			}

	}
	for (int i = 0; i < 50; i++)
		if (bullet[i] != NULL)
		{
			if (player->weapon->type == Rifle)
			{
				bulletRect[i] = InitObject(bullet[i]->x, bullet[i]->y, 10, 10);
				if (bullet[i]->right == 1)
				{
					bullet[i]->x += bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->up == 1)
					{
						bullet[i]->y -= bullet[i]->speed * dt / 1000;
						bullet[i]->x += 500 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->down == 1)
					{
						bullet[i]->y += bullet[i]->speed * dt / 1000;
						bullet[i]->x += 500 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bullet[i]->left == 1)
				{
					bullet[i]->x -= bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->up == 1)
					{
						bullet[i]->y -= bullet[i]->speed * dt / 1000;
						bullet[i]->x -= 500 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->down == 1)
					{
						bullet[i]->y += bullet[i]->speed * dt / 1000;
						bullet[i]->x -= 500 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bullet[i]->up == 1)
				{
					bullet[i]->y -= bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bullet[i]->down == 1)
				{
					bullet[i]->y += bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				////////////////////////////////////
				if ((player->x - bullet[i]->x) >= 1000 && (bullet[i]->left == 1))
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if (((bullet[i]->x - player->x) >= 1150) && bullet[i]->right == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if (((bullet[i]->y - player->y) >= 1500) && bullet[i]->down == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if (((player->y - bullet[i]->y) >= 1500) && bullet[i]->up == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
			}
			if (player->weapon->type == Shotgun)
			{
				bulletRect[i] = InitObject(bullet[i]->x, bullet[i]->y, 10, 10);
				if (bullet[i]->up == 1)
				{
					bullet[i]->y -= bullet[i]->speed * dt / 1000;
					if (bullet[i]->left == 1)
					{
						bullet[i]->y -= 50 * dt / 1000;
						bullet[i]->x -= 200 * dt / 1000;
					}
					if (bullet[i]->right == 1)
					{
						bullet[i]->y -= 50 * dt / 1000;
						bullet[i]->x += 200 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				else if (bullet[i]->down == 1)
				{
					bullet[i]->y += bullet[i]->speed * dt / 1000;
					if (bullet[i]->left == 1)
					{
						bullet[i]->y -= 50 * dt / 1000;
						bullet[i]->x -= 200 * dt / 1000;
					}
					if (bullet[i]->right == 1)
					{
						bullet[i]->y -= 50 * dt / 1000;
						bullet[i]->x += 200 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				else if (bullet[i]->right == 1)
				{
					bullet[i]->x += bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->shotAngleUp == 1)
					{
						bullet[i]->y -= 200 * dt / 1000;
						bullet[i]->x += 50 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->shotAngleDown == 1)
					{
						bullet[i]->y += 200 * dt / 1000;
						bullet[i]->x += 50 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				else if (bullet[i]->left == 1)
				{
					bullet[i]->x -= bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->shotAngleUp == 1)
					{
						bullet[i]->y -= 200 * dt / 1000;
						bullet[i]->x += 50 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->shotAngleDown == 1)
					{
						bullet[i]->y += 200 * dt / 1000;
						bullet[i]->x += 50 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				///////////////////////////////////////////////////////////////////////////////
				if (((bullet[i]->y - player->y) >= 350) && bullet[i]->down == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if (((player->y - bullet[i]->y) >= 150) && bullet[i]->up == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if ((player->x - bullet[i]->x) >= 150 && (bullet[i]->left == 1))
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if (((bullet[i]->x - player->x) >= 300) && bullet[i]->right == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
			}
			if (player->weapon->type == FlameThrower)
			{
				bulletRect[i] = InitObject(bullet[i]->x, bullet[i]->y, 10, 10);
				if (bullet[i]->right == 1)
				{
					bullet[i]->x += bullet[i]->speed * dt / 1000;
					if ((int)(bullet[i]->x - player->x) % 2 == 0)
					{
						bullet[i]->y -= bullet[i]->speed * dt / 1000;
					}
					else
						bullet[i]->y += bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->up == 1)
					{
						bullet[i]->x += 250 * dt / 1000;
						bullet[i]->y -= bullet[i]->speed / 2 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->down == 1)
					{
						bullet[i]->x += 250 * dt / 1000;
						bullet[i]->y += bullet[i]->speed / 2 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bullet[i]->left == 1)
				{
					bullet[i]->x -= bullet[i]->speed * dt / 1000;
					if ((int)(player->x - bullet[i]->x) % 2 == 0)
					{
						bullet[i]->y -= bullet[i]->speed * dt / 1000;
					}
					else
						bullet[i]->y += bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->up == 1)
					{
						bullet[i]->x -= 250 * dt / 1000;
						bullet[i]->y -= bullet[i]->speed / 2 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->down == 1)
					{
						bullet[i]->x -= 250 * dt / 1000;
						bullet[i]->y += bullet[i]->speed / 2 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bullet[i]->up == 1)
				{
					bullet[i]->y -= bullet[i]->speed * dt / 1000;
					if ((int)(player->y - bullet[i]->y) % 2 == 0)
					{
						bullet[i]->x -= bullet[i]->speed / 2 * dt / 1000;
					}
					else
						bullet[i]->x += bullet[i]->speed / 2 * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bullet[i]->down == 1)
				{
					bullet[i]->y += bullet[i]->speed * dt / 1000;
					if ((int)(bullet[i]->y - player->y) % 2 == 0)
					{
						bullet[i]->x -= bullet[i]->speed / 2 * dt / 1000;
					}
					else
						bullet[i]->x += bullet[i]->speed / 2 * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				////////////////////////////////////
				if ((player->x - bullet[i]->x) >= 1000 && (bullet[i]->left == 1))
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if (((bullet[i]->x - player->x) >= 1150) && bullet[i]->right == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if (((bullet[i]->y - player->y) >= 1500) && bullet[i]->down == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if (((player->y - bullet[i]->y) >= 1500) && bullet[i]->up == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
			}
			if (player->weapon->type == Boomgun)
			{
				bulletRect[i] = InitObject(bullet[i]->x, bullet[i]->y, 10, 10);
				if (bullet[i]->right == 1)
				{
					bullet[i]->x += bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->up == 1)
					{
						bullet[i]->y -= bullet[i]->speed * dt / 1000;
						bullet[i]->x += 500 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->down == 1)
					{
						bullet[i]->y += bullet[i]->speed * dt / 1000;
						bullet[i]->x += 500 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bullet[i]->left == 1)
				{
					bullet[i]->x -= bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->up == 1)
					{
						bullet[i]->y -= bullet[i]->speed * dt / 1000;
						bullet[i]->x -= 500 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bullet[i]->down == 1)
					{
						bullet[i]->y += bullet[i]->speed * dt / 1000;
						bullet[i]->x -= 500 * dt / 1000;
					}
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bullet[i]->up == 1)
				{
					bullet[i]->y -= bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bullet[i]->down == 1)
				{
					bullet[i]->y += bullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bulletRect[i]->x,(int)bulletRect[i]->y, (int)bulletRect[i]->w, (int)bulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				////////////////////////////////////
				if ((player->x - bullet[i]->x) >= 1000 && (bullet[i]->left == 1))
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if (((bullet[i]->x - player->x) >= 1150) && bullet[i]->right == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if (((bullet[i]->y - player->y) >= 1500) && bullet[i]->down == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
				else if (((player->y - bullet[i]->y) >= 1500) && bullet[i]->up == 1)
				{
					bullet[i] = NULL;
					bulletRect[i] = NULL;
					free(bullet[i]);
					free(bulletRect[i]);
				}
			}
			for (int j = 0; j < ZOMBIE_COUNT; j++)
				if (enemy[j] != NULL)
				{
					if (SDL_HasIntersectionF(bulletRect[i], enemyRect[j]))
					{
						enemy[j]->hp -= player->weapon->damage;
							if (player->weapon->type == Boomgun && bullet[i]->firstBullet == true)
							{
								bullet[n++] = BulletInit(enemyRect[j]->x + enemyRect[j]->w, enemyRect[j]->y + 30, 500, 1, 0, 0, 0, false, 0, 0);
								bullet[n++] = BulletInit(enemyRect[j]->x + enemyRect[j]->w, enemyRect[j]->y + 30, 500, 0, 1, 0, 0, false, 0, 0);
								bullet[n++] = BulletInit(enemyRect[j]->x + enemyRect[j]->w, enemyRect[j]->y + 30, 500, 0, 0, 1, 0, false, 0, 0);
								bullet[n++] = BulletInit(enemyRect[j]->x + enemyRect[j]->w, enemyRect[j]->y + 30, 500, 0, 0, 0, 1, false, 0, 0);
								bullet[n++] = BulletInit(enemyRect[j]->x + enemyRect[j]->w, enemyRect[j]->y + 30, 500, 1, 0, 1, 0, false, 0, 0);
								bullet[n++] = BulletInit(enemyRect[j]->x + enemyRect[j]->w, enemyRect[j]->y + 30, 500, 1, 0, 0, 1, false, 0, 0);
								bullet[n++] = BulletInit(enemyRect[j]->x + enemyRect[j]->w, enemyRect[j]->y + 30, 500, 0, 1, 1, 0, false, 0, 0);
								bullet[n++] = BulletInit(enemyRect[j]->x + enemyRect[j]->w, enemyRect[j]->y + 30, 500, 0, 1, 0, 1, false, 0, 0);
							}
						bullet[i] = NULL;
						bulletRect[i] = NULL;
						free(bullet[i]);
						free(bulletRect[i]);

						if (enemy[j]->hp <= 0)
						{
							enemy[j]->is_die = 1;
							player->score += 50;
							player->killEnemy++;
							enemy[j] = NULL;
							enemyRect[j] = NULL;
							enemyRadius[j] = NULL;
							free(enemy[j]);
							free(enemyRect[j]);
							free(enemyRadius[j]);
						}
					}
					else if (enemy[j]->y >= 2000)
					{
						enemy[j] = NULL;
						enemyRect[j] = NULL;
						enemyRadius[j] = NULL;
						free(enemy[j]);
						free(enemyRect[j]);
						free(enemyRadius[j]);
					}
				}

		}



	if (n >= 41)
	{
		n = 0;
	}
}
