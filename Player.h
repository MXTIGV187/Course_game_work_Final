#ifndef _PLAYER_H_
#define _PLAYER_H_

struct Player
{
	int hp;
	int score;
	float x;
	float y;
	bool is_die;
	bool can_jump;
	//����� ����� �� ���
};

Player* PlayerInit(int hp, int score, float x, float y, bool is_die, bool can_jump);

#endif
