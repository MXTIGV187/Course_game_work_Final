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

void PlayerMove(float& x, float& y, float& last_y, bool& is_jump, float& new_y, float& dy, int& dt, bool& isup, bool& isdown, bool& isleft, bool& isright, float& gravity, float& speed)
{
	if (y >= 300)
	{
		last_y = y;
		dy = 0;
		is_jump = 0;
	}

	if (isup)
	{
		if (is_jump == 0)
		{
			y -= gravity * dt / 1000;
			new_y = y;
			dy = last_y - new_y;
			if (dy >= 150)
			{
				isup = 0;
				is_jump = 1;
				y += gravity * dt / 1000;
			}
		}
		else
		{
			if (y < 300)
			{
				y += gravity * dt / 1000;
			}
		}

	}
	else
	{
		is_jump = 1;
		if (y < 300)
		y += gravity * dt / 1000;
	}
	if (isdown) y += gravity * dt / 1000;
	if (isleft) x -= speed * dt / 1000;
	if (isright) x += speed * dt / 1000;
}