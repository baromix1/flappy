#include "game.h"
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Object.h"
#include "bird.h"
#include "text.h"
Text::Text(SDL_Renderer* ren, const char* write, TTF_Font* font, int xp, int yp)
:Object::Object()
{
	
	SDL_Color color = { 0, 0, 0 };
	SDL_Surface* textSur = TTF_RenderText_Solid(font, write, color);
	xpos = xp;
	ypos = yp;
	writeText = (char*)write;
	renderer = ren;
	texture = SDL_CreateTextureFromSurface(ren, textSur);
	SDL_FreeSurface(textSur);
	srcRect.w = 150;
	srcRect.h = 100;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.w = 150;
	destRect.h = 100;
	destRect.x = xp;
	destRect.y = yp;


}
void Text::Render() {
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
void Text::Update(TTF_Font* font) {
	SDL_Color color = { 0, 0, 0 };
	const char* textu = writeText;
	SDL_Surface* textSur = TTF_RenderText_Solid(font, textu, color);
	
	
	texture = SDL_CreateTextureFromSurface(renderer, textSur);

	SDL_FreeSurface(textSur);
	
	destRect.x = xpos;
	destRect.y = ypos;
}