#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include "SDL_image.h"
#include "Object.h"

class PipeDown:public Object {
public:
	
	
	PipeDown(const char* texturesheet, SDL_Renderer* ren,int ypos,int xpos);
	void Update(int random);

};
