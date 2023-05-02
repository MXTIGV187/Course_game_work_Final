#ifndef _COMMON_PARAMETRS_H_
#define _COMMON_PARAMETRS_H_

#include <SDL.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define SPEED 2.0F


/*
* ��� ����� ������������ ������� ����
* ���������� ���
* ������� �����
* ����������
* ��������
* ����������� ������
* ������������ ��������� �������
* � ������ �����
*/

struct mainPhysics
{
	float speed;
	float gravity;
	float XmoveLeft, XmoveRight, Ymove;
	bool onborder;

};

struct mainWindow
{
	int w, h;
	float scaleX, scaleY;
};

#endif