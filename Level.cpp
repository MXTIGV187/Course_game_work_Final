#include <SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Level.h"


Boss* BossInit(int hp, int damage, int stage, int x, int y, BossType type)
{
	Boss* boss = (Boss*)malloc(sizeof(Boss));
	boss->hp = hp;
	boss->damage = damage;
	boss->stage = stage;
	boss->x = x;
	boss->y = y;
	boss->type = type;
	return boss;
}
SDL_FRect* InitObject(float x, float y, float w, float h)
{
	SDL_FRect* RectColis = (SDL_FRect*)malloc(sizeof(SDL_FRect));
	RectColis->x = x;
	RectColis->y = y;
	RectColis->w = w;
	RectColis->h = h;
	return RectColis;
}

void MassSaveToTXT(SDL_FRect* CollisArray, const char* fileName, int& sizeArray)
{
	FILE* file;
	fopen_s(&file, fileName, "w");

	if (file == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(1);
	}

	fprintf(file, "%d\n", sizeArray);

	for (int i = 0; i < sizeArray; i++)
	{
		fprintf(file, "%f %f %f %f\n", CollisArray[i].x, CollisArray[i].y, CollisArray[i].w, CollisArray[i].h);
	}

	fclose(file);
}

SDL_FRect* MassLoad(SDL_FRect*& CollisArray, SlopePlatform*& platform, const char* filename, int& sizeArray, int& sizePoint)
{
	FILE* file;
	errno_t err = fopen_s(&file, filename, "r");
	if (err != 0 || file == NULL)
	{
		printf("Ошибка при открытии файла\n");
		return NULL;
	}

	fscanf_s(file, "%d", &sizeArray);

	CollisArray = (SDL_FRect*)malloc(sizeArray * sizeof(SDL_FRect));
	if (CollisArray == NULL)
	{
		printf("Ошибка при выделении памяти\n");
		fclose(file);
		return NULL;
	}

	for (int i = 0; i < sizeArray; i++)
	{
		fscanf_s(file, "%f %f %f %f\n", &CollisArray[i].x, &CollisArray[i].y, &CollisArray[i].w, &CollisArray[i].h);
	}

	fscanf_s(file, "%d", &sizePoint);

	platform = (SlopePlatform*)malloc(sizePoint * sizeof(SlopePlatform));
	if (platform == NULL)
	{
		printf("Ошибка при выделении памяти\n");
		free(CollisArray);
		fclose(file);
		return NULL;
	}

	for (int i = 0; i < sizePoint; i++)
	{
		fscanf_s(file, "%f %f %f %f\n", &platform[i].x1, &platform[i].x2, &platform[i].y1, &platform[i].y2);
	}

	fclose(file);

	return CollisArray;
}

void BossFight(Boss* boss, Player* player, SDL_FRect* playerRect, SDL_Renderer* renderer, SDL_Rect bullet_rect, SDL_Texture* bullet_tex, Bullet** bossBullet,
	SDL_FRect** bossBulletRect, int& dt, int& n_boss, int& newtime, Uint32* lastShotTimeBoss, SDL_FRect* bossUpRect, SDL_FRect* bossDownRect, Bullet** bullet, SDL_FRect** bulletRect)
{
	if ((boss->x - player->x <= 1100 || player->bossFight == 1))
	{
		player->bossFight = 1;
		if (boss != NULL && player != NULL)
			if (boss->type == Level1)
			{

				if (newtime - lastShotTimeBoss[0] >= 5000)
				{
					if (boss->stage == 1)
						for (int j = 0; j < 40; j++)
							bossBullet[n_boss++] = BulletInit(1500, rand() % 800 + 200, 300, 0, 1, 0, 0, true, 0, 0);
					if (boss->stage == 2)
						for (int j = 0; j < 40; j++)
							bossBullet[n_boss++] = BulletInit(1500, rand() % 400 + 600, 300, 0, 1, 0, 0, true, 0, 0);
					lastShotTimeBoss[0] = SDL_GetTicks();
				}
				if (boss->stage == 1)
					if (newtime - lastShotTimeBoss[1] >= 10000)
					{
						for (int j = 0; j < 50; j++)
							bossBullet[n_boss++] = BulletInit(rand() % 1260 + 200, 0, 300, 0, 0, 0, 1, true, 0, 0);

						lastShotTimeBoss[1] = SDL_GetTicks();
					}
				if (boss->stage == 2)
					if (newtime - lastShotTimeBoss[1] >= 7000)
					{
						for (int j = 0; j < 50; j++)
							bossBullet[n_boss++] = BulletInit(rand() % 1260 + 200, 0, 300, 0, 0, 0, 1, true, 0, 0);

						lastShotTimeBoss[1] = SDL_GetTicks();
					}

			}
		for (int i = 0; i < 200; i++)
			if (bossBullet[i] != NULL && player != NULL)
			{
				bossBulletRect[i] = InitObject(bossBullet[i]->x, bossBullet[i]->y, 10, 10);
				if (bossBullet[i]->right == 1)
				{
					bossBullet[i]->x += bossBullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bossBulletRect[i]->x,(int)bossBulletRect[i]->y, (int)bossBulletRect[i]->w, (int)bossBulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bossBullet[i]->up == 1)
					{
						bossBullet[i]->y -= bossBullet[i]->speed * dt / 1000;
						bossBullet[i]->x += 500 * dt / 1000;
					}
					bullet_rect = { (int)bossBulletRect[i]->x,(int)bossBulletRect[i]->y, (int)bossBulletRect[i]->w, (int)bossBulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bossBullet[i]->down == 1)
					{
						bossBullet[i]->y += bossBullet[i]->speed * dt / 1000;
						bossBullet[i]->x += 500 * dt / 1000;
					}
					bullet_rect = { (int)bossBulletRect[i]->x,(int)bossBulletRect[i]->y, (int)bossBulletRect[i]->w, (int)bossBulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bossBullet[i]->left == 1)
				{
					bossBullet[i]->x -= bossBullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bossBulletRect[i]->x,(int)bossBulletRect[i]->y, (int)bossBulletRect[i]->w, (int)bossBulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bossBullet[i]->up == 1)
					{
						bossBullet[i]->y -= bossBullet[i]->speed * dt / 1000;
						bossBullet[i]->x -= 500 * dt / 1000;
					}
					bullet_rect = { (int)bossBulletRect[i]->x,(int)bossBulletRect[i]->y, (int)bossBulletRect[i]->w, (int)bossBulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
					if (bossBullet[i]->down == 1)
					{
						bossBullet[i]->y += bossBullet[i]->speed * dt / 1000;
						bossBullet[i]->x -= 500 * dt / 1000;
					}
					bullet_rect = { (int)bossBulletRect[i]->x,(int)bossBulletRect[i]->y, (int)bossBulletRect[i]->w, (int)bossBulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bossBullet[i]->up == 1)
				{
					bossBullet[i]->y -= bossBullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bossBulletRect[i]->x,(int)bossBulletRect[i]->y, (int)bossBulletRect[i]->w, (int)bossBulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				if (bossBullet[i]->down == 1)
				{
					bossBullet[i]->y += bossBullet[i]->speed * dt / 1000;
					bullet_rect = { (int)bossBulletRect[i]->x,(int)bossBulletRect[i]->y, (int)bossBulletRect[i]->w, (int)bossBulletRect[i]->h };
					SDL_RenderCopy(renderer, bullet_tex, NULL, &bullet_rect);
				}
				////////////////////////////////////
				if ((player->x - bossBullet[i]->x) >= 1000 && (bossBullet[i]->left == 1))
				{
					bossBullet[i] = NULL;
					bossBulletRect[i] = NULL;
					free(bossBullet[i]);
					free(bossBulletRect[i]);
				}
				else if (((bossBullet[i]->x - player->x) >= 1150) && bossBullet[i]->right == 1)
				{
					bossBullet[i] = NULL;
					bossBulletRect[i] = NULL;
					free(bossBullet[i]);
					free(bossBulletRect[i]);
				}
				else if (((bossBullet[i]->y - player->y) >= 1500) && bossBullet[i]->down == 1)
				{
					bossBullet[i] = NULL;
					bossBulletRect[i] = NULL;
					free(bossBullet[i]);
					free(bossBulletRect[i]);
				}
				else if (((player->y - bossBullet[i]->y) >= 1500) && bossBullet[i]->up == 1)
				{
					bossBullet[i] = NULL;
					bossBulletRect[i] = NULL;
					free(bossBullet[i]);
					free(bossBulletRect[i]);
				}

				if (SDL_HasIntersectionF(bossBulletRect[i], playerRect))
				{
					player->hp -= 20;
					bossBullet[i] = NULL;
					bossBulletRect[i] = NULL;
					free(bossBullet[i]);
					free(bossBulletRect[i]);
				}

			}

		if (boss != nullptr)
		{
			for (int i = 0; i < 50; i++)
				if (bullet[i] != NULL)
				{

					if (boss->stage == 1)
						if (SDL_HasIntersectionF(bulletRect[i], bossUpRect))
						{
							boss->hp -= player->weapon->damage;

							bullet[i] = NULL;
							bulletRect[i] = NULL;
							free(bullet[i]);
							free(bulletRect[i]);

							if (boss->hp <= 500)
							{
								boss->stage = 2;
								free(bossUpRect);
							}
						}
					if (boss->stage == 2)
						if (SDL_HasIntersectionF(bulletRect[i], bossDownRect))
						{
							boss->hp -= player->weapon->damage;

							bullet[i] = NULL;
							bulletRect[i] = NULL;
							free(bullet[i]);
							free(bulletRect[i]);

							if (boss->hp <= 0)
							{
								boss->stage = 0;
								free(bossDownRect);
								//level complete
							}
						}
				}
		}
		if (boss->stage == 0)
			if (player->x >= 1600)
				player->level1_complete = 1;
	}

	if (n_boss >= 100)
	{
		n_boss = 0;
	}

}




