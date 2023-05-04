#include "game.h"
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Object.h"
#include "bird.h"

Bird::Bird(const char* texturesheet, SDL_Renderer* ren) 
	:Object::Object(texturesheet,ren,50,350)
{

	/*bird = new Object(texturesheet, ren,50,350);*/


	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = 50;
	destRect.y = 350;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}
void Bird::Update(){
	
	if (destRect.x <= 350) {
		destRect.x += 1;
	}
	if (gravity >= 0) {
		if (destRect.y > 0) {
			gravity2 = 100;
			destRect.y += -0.2 * gravity;
			gravity -= 3;
		}
	}
	else {
		destRect.y += 0.03 * gravity2;
		gravity2 +=5;
		isJumping = false;
	}
	
}
