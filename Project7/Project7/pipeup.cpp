#include "game.h"
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Object.h"
#include "pipeup.h"

PipeUp::PipeUp(const char* texturesheet, SDL_Renderer* ren,int y,int x)
	:Object::Object(texturesheet,ren,720,0)
{
	


	srcRect.h = 400;
	srcRect.w = 100;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = x;
	destRect.y = y;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}
void PipeUp::Update(int random) {
	
	destRect.x += -3;
	if (destRect.x < -100) {
		destRect.x += 1200;
		destRect.y = (random*40) -200;
	}
	

}