#pragma once

#include <SDL.h>
#include <stdio.h>
#include <string>
#include "SDL_image.h"

class Object {

public:
	SDL_Texture* texture;
	SDL_Rect srcRect,destRect;
	SDL_Renderer* renderer;
	int xpos, ypos;
	static SDL_Texture* LoadTexture(const char* path, SDL_Renderer* ren);
	Object(const char* texturesheet, SDL_Renderer* ren, int xpos, int ypos);
	~Object();
	Object();
	virtual void Update();
	void Render();
private:
	
};

