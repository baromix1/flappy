#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height);
	void update();
	void update2();
	void render();
	void clean();
	void events();
	void pipes();
	bool runing() { return isRunning; };
	SDL_Renderer* renderer;

private:
	bool isRunning;
	SDL_Window* window;
	
	int count=0;

};