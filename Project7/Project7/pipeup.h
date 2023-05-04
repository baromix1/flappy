#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include "SDL_image.h"
#include "Object.h"

class PipeUp: public Object {
public:
	

	PipeUp(const char* texturesheet, SDL_Renderer* ren,int ypos,int xpos);
	void Update(int random);

};
#pragma once
