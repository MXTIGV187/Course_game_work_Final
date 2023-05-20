#include <stdlib.h>
#include "Weapon.h"
#include "common_parametrs.h"
#include "Player.h"
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

//void Shoot(int& newtime, Uint32& lastShotTime, bool& fire, bool& shootRight, bool& shootLeft, bool& shootUp, bool& shootDown, int& direction, int& n, Bullet** bullet, SDL_FRect* playerRect,
//	int& dt, SDL_FRect** bulletRect, Enemy** enemy, SDL_FRect** enemyRect, SDL_FRect** enemyRadius, Player* player)
//{
//	if (newtime - lastShotTime >= 300)
//		if (fire)
//		{
//			if (shootRight || shootLeft || shootUp || shootDown)
//			{
//				if (shootRight == 1)
//				{
//					direction = DIR_RIGHT;
//					if (shootUp == 1)
//						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 1, 0);
//					else if (shootDown == 1)
//						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 1);
//					else
//						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 0);
//
//				}
//				else if (shootLeft == 1)
//				{
//					direction = DIR_LEFT;
//					if (shootUp == 1)
//						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 1, 0);
//					else if (shootDown == 1)
//						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 1);
//					else
//						bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 0);
//				}
//				else if (shootUp == 1)
//					bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 0, 1, 0);
//				else if (shootDown == 1)
//					bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 0, 0, 1);
//			}
//			else
//			{
//				if (direction == DIR_LEFT)
//					bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 0, 1, 0, 0);
//				if (direction == DIR_RIGHT)
//					bullet[n++] = BulletInit(playerRect->x + playerRect->w, playerRect->y + 30, 500, 1, 0, 0, 0);
//			}
//			lastShotTime = SDL_GetTicks();
//		}
//	for (int i = 1; i < 10; i++)
//		if (bullet[i] != NULL)
//		{
//			if (bullet[i]->right == 1)
//			{
//				bullet[i]->x += bullet[i]->speed * dt / 1000;
//				if (bullet[i]->up == 1)
//					bullet[i]->y -= bullet[i]->speed * dt / 1000;
//				if (bullet[i]->down == 1)
//					bullet[i]->y += bullet[i]->speed * dt / 1000;
//			}
//			if (bullet[i]->left == 1)
//			{
//				bullet[i]->x -= bullet[i]->speed * dt / 1000;
//				if (bullet[i]->up == 1)
//					bullet[i]->y -= bullet[i]->speed * dt / 1000;
//				if (bullet[i]->down == 1)
//					bullet[i]->y += bullet[i]->speed * dt / 1000;
//			}
//			if (bullet[i]->up == 1)
//				bullet[i]->y -= bullet[i]->speed * dt / 1000;
//			if (bullet[i]->down == 1)
//				bullet[i]->y += bullet[i]->speed * dt / 1000;
//			bulletRect[i] = InitObject(bullet[i]->x, bullet[i]->y, 10, 10);
//			for (int j = 0; j < 5; j++)
//				if (enemy[j] != NULL)
//				{
//					if (SDL_HasIntersectionF(bulletRect[i], enemyRect[j]))
//					{
//						enemy[j]->hp -= 30;
//						bullet[i] = NULL;
//						bulletRect[i] = NULL;
//						free(bullet[i]);
//						free(bulletRect[i]);
//
//						if (enemy[j]->hp <= 0)
//						{
//							enemy[j]->is_die = 1;
//							player->score += 50;
//							player->killEnemy++;
//							enemy[j] = NULL;
//							enemyRect[j] = NULL;
//							enemyRadius[j] = NULL;
//							free(enemy[j]);
//							free(enemyRect[j]);
//							free(enemyRadius[j]);
//						}
//					}
//				}
//		}
//
//	if (n >= 9)
//		n = 1;
//}