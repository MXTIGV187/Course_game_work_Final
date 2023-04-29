#ifndef _PLAYER_H_
#define _PLAYER_H_

struct Player
{
	int hp;
	int score;
	float x;
	float y;
	//Скины хуины че ещё
};

Player* PlayerInit(int hp, int score, float x, float y);

#endif
