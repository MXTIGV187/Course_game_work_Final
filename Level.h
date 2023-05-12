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
void MassSaveToTXT(SDL_FRect* CollisArray, const char* fileName, int& sizeArray);
SDL_FRect* MassLoad(SDL_FRect*& CollisArray, const char* filename, int& sizeArray);

#endif