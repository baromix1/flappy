#pragma once
#include <SDL.h>
#include <stdio.h>

#include "SDL_image.h"
#include "Object.h"
#include "SDL_ttf.h"
#include <string>

class Text:public Object{
public:
	
	char* writeText=NULL;
	Text( SDL_Renderer* ren, const char* textu, TTF_Font* font,int xpos,int ypos);
	void Update(TTF_Font* font);
};