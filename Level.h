#ifndef _LEVEL_H_
#define _LEVEL_H_

enum ObjectType
{
	Platform
};

struct Object
{
	float x, y;
	float w, h;
	ObjectType type;
};

SDL_FRect* InitObject(float x, float y, float w, float h);

#endif