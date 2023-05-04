#include <SDL.h>
#include <stdio.h>
#include <string>
#include "game.h"
#include "Object.h"
#include "background.h"

Game* game = nullptr;

int main(int argc, char* args[])
{
	const int FPS =60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	game = new Game();

	game->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 900);
	
	while (game->runing()) {

		frameStart = SDL_GetTicks();

		game->events();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}