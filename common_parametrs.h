#ifndef _COMMON_PARAMETRS_H_
#define _COMMON_PARAMETRS_H_

#include <SDL.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define SPEED 2.0F


/*
* рср мсфмн опндхтюимхрэ пюулепш нймю
* йнкхвеярбн тоя
* пюглепш цепнъ
* цпюбхрюжхч
* яйнпнярэ
* ярюрхвеяйсч йюлепс
* пюяонкнфемхъ оепянмюфю еаюмнцн
* х бяъйсч усимч
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

struct mainRenderer
{
	SDL_Texture* texture;
	SDL_Rect textureSize;
};

struct mainHero
{
	SDL_Point position;
	mainPhysics physic;
	mainRenderer render;
};
#endif