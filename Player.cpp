#include <SDL.h>
#include <stdio.h>
#include "Player.h"
#include "common_parametrs.h"

Player* PlayerInit(int hp, int score, float x, float y)
{
	Player* player = (Player*)malloc(sizeof(Player));
	player->hp = hp;
	player->score = score;
	player->x = x;
	player->y = y;
	return player;
}