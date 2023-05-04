#ifndef _PLAYER_H_
#define _PLAYER_H_

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
void PlayerMove(float& x, float& y, float& last_y, bool& is_jump, float& new_y, float& dy, int& dt, bool& isup, bool& isdown, bool& isleft, bool& isright, float& gravity, float& speed);

#endif
