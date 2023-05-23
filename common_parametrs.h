#ifndef _COMMON_PARAMETRS_H_
#define _COMMON_PARAMETRS_H_

#include <SDL.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080


#define DIR_RIGHT 1
#define DIR_LEFT  2
#define DIR_LEFT 2
#define DIR_RIGHT 1

#define ZOMBIE_COUNT 10

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

struct mainWindow
{
	int w, h;
	float scaleX, scaleY;
};

struct mainRenderer
{
	SDL_Texture* texture;
	SDL_Rect textureSize;

};

#endif