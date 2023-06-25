#ifndef _LEVEL_H_
#define _LEVEL_H_

#include<SDL_ttf.h>
#include "Player.h"

#include"Weapon.h"

struct Player;

enum ObjectType
{
	Platform
};

enum BossType
{
	Level1
};

struct Object
{
	float x, y;
	float w, h;
	ObjectType type;
};

struct SlopePlatform {
	float x1; 
	float y1; 
	float x2; 
	float y2; 
};

struct Boss
{
	int hp;
	int damage;
	int stage;
	int x;
	int y;
	BossType type;
};


struct Bullet;
struct Weapon;
struct Bonus;

Boss* BossInit(int hp, int damage, int stage, int x, int y, BossType type);
SDL_FRect* InitObject(float x, float y, float w, float h);
void MassSaveToTXT(SDL_FRect* CollisArray, const char* fileName, int& sizeArray);
SDL_FRect* MassLoad(SDL_FRect*& CollisArray, SlopePlatform*& platform, const char* filename, int& sizeArray, int& sizePoint);
SDL_Texture* Load_Texture_Font(const char* text, TTF_Font* font, SDL_Rect* rect, SDL_Color color, SDL_Renderer* renderer);
void BossFight(Boss* boss, Player* player, SDL_FRect* playerRect, SDL_Renderer* renderer, SDL_Rect bullet_rect, SDL_Texture* bullet_tex, Bullet** bossBullet,
	SDL_FRect** bossBulletRect, int& dt, int& n_boss, int& newtime, Uint32* lastShotTimeBoss, SDL_FRect* bossUpRect, SDL_FRect* bossDownRect, Bullet** bullet, SDL_FRect** bulletRect, bool& running, bool& main_menu);

#endif