#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL.h>
#include "Weapon.h"
struct Weapon;
struct Player
{
	int hp;
	int score;
	int killEnemy;
	float x;
	float y;
	bool is_die;
	bool is_jump;
	bool upToPlatform;
	Weapon* weapon;
};

struct Enemy
{
	int hp;
	float x;
	float y;
	bool is_die;
	bool is_jump;
	bool is_jump_right;
	bool is_jump_left;
};

struct mainPhysics
{
	float speed;
	float gravity;
};

struct Bullet
{
	float x;
	float y;
	float speed;
	bool right;
	bool left;
	bool up;
	bool down;
	SDL_Texture* texture;
};


Player* PlayerInit(int hp, int score, float x, float y, bool is_die, bool is_jump, bool upToPlatform, int killEnemy, Weapon* weapon);
mainPhysics* PhysInit(float speed, float gravity);
Enemy* EnemyInit(int hp, float x, float y, bool is_die, bool is_jump);
Bullet* BulletInit(float x, float y, float speed, bool right, bool left, bool up, bool down);
void EnemyMove(Enemy* enemy, SDL_FRect* enemyRadius, SDL_FRect* playerRect, SDL_FRect* enemyRect, mainPhysics* mainPhys, SDL_FRect* CollisArray, int& sizeArray, int& dt,
	float& last_enemy_y, float& new_enemy_y, float& dy_enemy);
SDL_FRect* checkCollision(SDL_FRect* playerRect, SDL_FRect* CollisArray, int& sizeArray);
void PlayerMove(Player* player, float& last_y, float& new_y, float& dy, int& dt, bool& isup,
	bool& isdown, bool& isleft, bool& isright, mainPhysics* mainPhys, SDL_FRect* playerRect, SDL_FRect* CollisArray, int& sizeArray);

void BackGround_move(SDL_FRect* CollisArray, Player* player, int& sizeArray, bool& isleft, bool& isright);

#endif
