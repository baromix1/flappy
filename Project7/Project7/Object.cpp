#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Object.h"
#include "background.h"

SDL_Texture* Object::LoadTexture(const char* texture, SDL_Renderer* ren) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}
Object::Object(const char* texturesheet, SDL_Renderer* ren,int x, int y) {
	renderer = ren;
	texture = LoadTexture(texturesheet, ren);
	xpos = x;
	ypos = y;
}
Object::Object() {
	renderer = nullptr;
}
void Object::Update() {

}
void Object::Render() {
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}