#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include "SDL_image.h"
#include "Object.h"

class Bird :public Object{
public:
	Object* bird;
	double gravity;
	double gravity2=100;
	double a;
	bool isJumping = false;
	Bird(const char* texturesheet, SDL_Renderer* ren);
	~Bird();
	void Update();
};