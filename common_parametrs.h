#pragma once

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