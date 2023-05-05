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
	//����� ����� �� ���
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
void HitBox(SDL_FRect* enemyRect, SDL_FRect* Rect, SDL_FRect* Rect1, SDL_FRect* Rect2, Enemy* enemy, mainPhysics* mainPhys, int& dt);
void PlayerMove(Player* player, float& last_y, float& new_y, float& dy, int& dt, bool& isup,
	bool& isdown, bool& isleft, bool& isright, mainPhysics* mainPhys, SDL_FRect* Rect, SDL_FRect* Rect1, SDL_FRect* Rect2, SDL_FRect* playerRect);

#endif
