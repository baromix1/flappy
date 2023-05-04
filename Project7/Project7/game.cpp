#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Object.h"
#include "background.h"
#include "bird.h"
#include "pipedown.h"
#include "pipeup.h"
#include <cstdlib>
#include "text.h"
#include "SDL_ttf.h"


Background* background;
Background* background2;
TTF_Font* font;
Bird* birdd;

Game::Game()
{}

Game::~Game()
{}

PipeUp* pipeup1;
PipeDown* pipedown1;
PipeUp* pipeup2;
PipeDown* pipedown2;
PipeUp* pipeup3;
PipeDown* pipedown3;
Text* score;
Text* score2;
int scoreCount=0;

void Game::init(const char* title, int xpos, int ypos, int width, int height)
{
	int flags = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		TTF_Init();
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
	
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
		}
		 
		isRunning = true;

	}
	
	
	
	background = new Background("images/bg_5.png", renderer);
	
	birdd = new Bird("images/bird.png", renderer);
	int yposs = -100;
	int xposs = 1000;

	pipedown1 = new PipeDown("images/pipedown.png", renderer, yposs + 650, xposs);
	pipeup1 = new PipeUp("images/pipeup.png", renderer, yposs, xposs); 
	yposs += 100;

	pipedown2 = new PipeDown("images/pipedown.png", renderer, yposs + 650, xposs + 400);
	pipeup2 = new PipeUp("images/pipeup.png", renderer, yposs, xposs + 400);
	yposs += 100;

	pipedown3 = new PipeDown("images/pipedown.png", renderer, yposs + 650, xposs + 800);
	pipeup3 = new PipeUp("images/pipeup.png", renderer, yposs, xposs + 800);
	font = TTF_OpenFont("arial.ttf", 25);
	score = new Text(renderer, "Score: ", font,0 ,0);
	score2 = new Text(renderer, "0", font, 150, 0);
	score2->destRect.w = 30;
	

	score->Update(font);
	srand(time(NULL));
}





void Game::update()
{

	
	
	
	int  random = rand() % 10;
	
	birdd->Update(); 
	pipedown1->Update(random);
	pipedown2->Update(random);
	pipedown3->Update(random);
	pipeup1->Update(random);
	pipeup2->Update(random);
	pipeup3->Update(random);
	

}
char* intToStr(int data) {
	std::string strData = std::to_string(data);

	char* temp = new char[strData.length() + 1];
	strcpy(temp, strData.c_str());

	return temp;
}

void Game::events()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_SPACE:
			if (birdd->isJumping == false) {
				birdd->gravity = 50;
				birdd->isJumping = true;
			}
			break;
		}
		
		break;
	
	default:
		break;

	}
	
	if (birdd->destRect.x > pipedown1->destRect.x + 100 && birdd->destRect.x < pipedown1->destRect.x + 104)
	{
		scoreCount++;
		char* sc = intToStr(scoreCount);
		 score2->writeText = sc; 
		 score2->Update(font);
	}
	if (birdd->destRect.x > pipedown2->destRect.x + 100 && birdd->destRect.x < pipedown2->destRect.x + 104)
	{
		scoreCount++;
		char* sc = intToStr(scoreCount);
		 score2->writeText = sc;
		 score2->Update(font);
	}
	if (birdd->destRect.x > pipedown3->destRect.x + 100 && birdd->destRect.x < pipedown3->destRect.x + 104)
	{
		scoreCount++;
		char* sc = intToStr(scoreCount);
		std::cout << sc << std::endl;
		 score2->writeText = sc;
		 score2->Update(font);
	}
	
	if (birdd->destRect.y > 836) { isRunning = false; }
	if (birdd->destRect.x+64 > pipedown1->destRect.x && birdd->destRect.x + 64 < pipedown1->destRect.x+140 && birdd->destRect.y > pipedown1->destRect.y-50) { isRunning = false; }
	if (birdd->destRect.x+64 > pipedown2->destRect.x && birdd->destRect.x + 64 < pipedown2->destRect.x + 140 && birdd->destRect.y > pipedown2->destRect.y-50 ) { isRunning = false; }
	if (birdd->destRect.x+64 > pipedown3->destRect.x && birdd->destRect.x + 64 < pipedown3->destRect.x + 140 && birdd->destRect.y > pipedown3->destRect.y-50 ) { isRunning = false; }
	if (birdd->destRect.x+64 > pipeup1->destRect.x && birdd->destRect.x + 64 < pipeup1->destRect.x + 140 && birdd->destRect.y < pipeup1->destRect.y + 400) { isRunning = false; }
	if (birdd->destRect.x+64 > pipeup2->destRect.x && birdd->destRect.x + 64 < pipeup2->destRect.x + 140 && birdd->destRect.y < pipeup2->destRect.y+400) { isRunning = false; }
	if (birdd->destRect.x+64 > pipeup3->destRect.x && birdd->destRect.x + 64 < pipeup3->destRect.x + 140 && birdd->destRect.y < pipeup3->destRect.y+400) { isRunning = false; } 
}

void Game::pipes() {
	

}
void Game::render()
{
	SDL_RenderClear(renderer);
	background->Render();
	birdd->Render();
	pipedown1->Render();
	pipeup1->Render();
	pipedown2->Render();
	pipeup2->Render();
	pipedown3->Render();
	pipeup3->Render();
	score->Render();
	score2->Render();
	SDL_RenderPresent(renderer);

}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	std::cout << "everything cleaned" << std::endl;
}


