#include "game.h"
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Object.h"
#include "background.h"

Background::Background(const char* texturesheet, SDL_Renderer* ren)
	:Object::Object(texturesheet,ren,0,0)
{
	
	

	srcRect.h = 900;
	srcRect.w = 700;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = 0;
	destRect.y = 0;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}


