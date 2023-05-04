#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include "SDL_image.h"
#include "Object.h"
 
class Background: public Object{
public:
	
	Background(const char* texturesheet, SDL_Renderer* ren);
	
	
private:
};