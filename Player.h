#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL.h>
#include "Weapon.h"
#include "Level.h"
struct Weapon;
struct Bonus;
struct SlopePlatform;

enum EnemyType
{
	Zombie,
	Shooter,
	Rocket_man
};

	struct Player
	{
		int hp;
		int score;
		int life;
		int killEnemy;
		float x;
		float y;
		bool is_die;
		bool is_jump;
		bool upToPlatform;
		bool bossFight;
		Weapon* weapon;
		Bonus* bonus;
		bool level1_complete;
		bool level2_complete;
		bool level3_complete;
	};

struct Enemy
{
	EnemyType type;
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
	bool firstBullet;
	bool shotAngleDown;
	bool shotAngleUp;
	SDL_Texture* texture;
};

struct Rocket {
	
	float x;
	float y;
	float speed;
	


};

struct Score
{
	int life;
	int score;
	int killEnemy;
};

Player* PlayerInit(int hp, int score, int life, float x, float y, bool is_die, bool is_jump, bool upToPlatform, bool bossFight, int killEnemy, Weapon* weapon, Bonus* bonus, bool level1_complete, bool level2_complete, bool level3_complete);
mainPhysics* PhysInit(float speed, float gravity);
Enemy* EnemyInit(int hp, float x, float y, bool is_die, bool is_jump, EnemyType type);
Bullet* BulletInit(float x, float y, float speed, bool right, bool left, bool up, bool down, bool firstBullet, bool shotAngleUp, bool shotAngleDown);
void EnemyMove(Enemy* enemy, SDL_FRect* enemyRadius, SDL_FRect* playerRect, SDL_FRect* enemyRect, mainPhysics* mainPhys, SDL_FRect* CollisArray, int& sizeArray, int& dt,
	float& last_enemy_y, float& new_enemy_y, float& dy_enemy, Player* player, int& newtime, int direction_enemy);
SDL_FRect* checkCollision(SDL_FRect* playerRect, SDL_FRect* CollisArray, int& sizeArray);
void PlayerMove(Player* player, float& last_y, float& new_y, float& dy, int& dt, bool& isup,
	bool& isdown, bool& isleft, bool& isright, mainPhysics* mainPhys, SDL_FRect* playerRect, SDL_FRect* CollisArray, int& sizeArray, SlopePlatform* platform, int& sizePoint);
void IsPlayerDie(Player* player, int& respawn_x, int& respawn_y, Weapon* rifle, bool& running, bool& main_menu);
void BackGround_move(SDL_FRect* CollisArray, Player* player, int& sizeArray, bool& isleft, bool& isright);
void SaveScoreTable(Player* player, const char* fileName);
Score* PrintScoreTable(const char* fileName);
void EnemySave(Enemy** enemy, const char* fileName, int ZOMBIE_COUNT, int SHOOTER_COUNT);
void EnemyLoad(Enemy** enemy, const char* fileName, int& ZOMBIE_COUNT, int& SHOOTER_COUNT);
void SaveProgress(Player* player, Weapon* weapon, const char* fileName);
Player* LoadProgress(const char* fileName);

#endif
