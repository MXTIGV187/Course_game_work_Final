#ifndef _COMMON_PARAMETRS_H_
#define _COMMON_PARAMETRS_H_

#include <SDL.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800


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