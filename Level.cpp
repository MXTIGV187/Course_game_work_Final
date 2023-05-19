#include <SDL.h>
#include <stdio.h>
#include <math.h>
#include "Level.h"
#include "Player.h"

SDL_FRect* InitObject(float x, float y, float w, float h)
{
	SDL_FRect* RectColis = (SDL_FRect*)malloc(sizeof(SDL_FRect));
	RectColis->x = x;
	RectColis->y = y;
	RectColis->w = w;
	RectColis->h = h;
	return RectColis;
}

void MassSaveToTXT(SDL_FRect* CollisArray, const char* fileName, int& sizeArray)
{
	FILE* file;
	fopen_s(&file, fileName, "w");

	if (file == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(1);
	}

	fprintf(file, "%d\n", sizeArray);

	for (int i = 0; i < sizeArray; i++)
	{	
		fprintf(file, "%f %f %f %f\n", CollisArray[i].x, CollisArray[i].y, CollisArray[i].w, CollisArray[i].h);
	}

	fclose(file);
}

SDL_FRect* MassLoad(SDL_FRect*& CollisArray, const char* filename, int& sizeArray)
{
	FILE* file;
	errno_t err = fopen_s(&file, filename, "r");
	if (err != 0 || file == NULL)
	{
		printf("Ошибка при открытии файла\n");
		return NULL;
	}

	fscanf_s(file, "%d", &sizeArray);

	CollisArray = (SDL_FRect*)malloc(sizeArray * sizeof(SDL_FRect));
	if (CollisArray == NULL) 
	{
		printf("Ошибка при выделении памяти\n");
		fclose(file);
		return NULL;
	}

	for (int i = 0; i < sizeArray; i++)
	{
		fscanf_s(file, "%f %f %f %f\n", &CollisArray[i].x, &CollisArray[i].y, &CollisArray[i].w, &CollisArray[i].h);
	}

	fclose(file);

	return CollisArray;
}


