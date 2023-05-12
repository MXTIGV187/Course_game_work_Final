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

struct Enemy
{
	int hp;
	float x;
	float y;
	bool is_die;
	bool is_jump;

};

struct mainPhysics
{
	float speed;
	float gravity;
};


Player* PlayerInit(int hp, int score, float x, float y, bool is_die, bool is_jump);
mainPhysics* PhysInit(float speed, float gravity);
Enemy* EnemyInit(int hp, float x, float y, bool is_die, bool is_jump);
void HitBox(SDL_FRect* enemyRect, SDL_FRect* CollisArray, Enemy* enemy, mainPhysics* mainPhys, int& dt, int& sizeArray);
SDL_FRect* checkCollision(SDL_FRect* playerRect, SDL_FRect* CollisArray, int& sizeArray);
void PlayerMove(Player* player, float& last_y, float& new_y, float& dy, int& dt, bool& isup,
	bool& isdown, bool& isleft, bool& isright, mainPhysics* mainPhys, SDL_FRect* playerRect, SDL_FRect* CollisArray, int& sizeArray);

#endif
