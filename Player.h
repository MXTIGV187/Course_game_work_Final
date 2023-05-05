#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL.h>
struct Player
{
	int hp;
	int score;
	float x;
	float y;
	bool is_die;
	bool is_jump;
	//Скины хуины че ещё
};

struct mainPhysics
{
	float speed;
	float gravity;
};


Player* PlayerInit(int hp, int score, float x, float y, bool is_die, bool is_jump);
mainPhysics* PhysInit(float speed, float gravity);
SDL_FRect* IsCollis(int number_object, SDL_FRect* playerRect, SDL_FRect* CollisRect);
void PlayerMove(Player* player, float& last_y, float& new_y, float& dy, int& dt, bool& isup,
	bool& isdown, bool& isleft, bool& isright, mainPhysics* mainPhys, SDL_FRect* Rect, SDL_FRect* Rect1, SDL_FRect* Rect2, SDL_FRect* playerRect);

#endif
