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
#include "score.h"
#include <regex>
#include <fstream>
#include <filesystem>
import globals;

std::regex reg(R"([A-Za-z])");
std::vector<Score> wyniki;
Background* background;
Background* menu;
Background* loginn;
Background* Scoreboard;
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
Text* nick;
Text* nick2;
Text* scoreTab0;
Text* scoreTab1;
Text* scoreTab2;
std::string login="user";


const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}
char* StrToStr(std::string data) {


	char* temp = new char[data.length() + 1];
	strcpy(temp, data.c_str());

	return temp;
}
void Game::init(const char* title, int xpos, int ypos, int width, int height)
{
	SDL_StartTextInput();
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
	scoreTab0 = new Text(renderer, "", font, 20, 100);
	scoreTab1 = new Text(renderer, "", font, 20, 200);
	scoreTab2 = new Text(renderer, "", font, 20, 300);
	std::filesystem::path pathh = "score.txt";
	if (is_regular_file(pathh)) {
		std::ifstream plik("score.txt");
		std::string wynikk;
		std::string nickkk;
		std::string timeeee;
		Score tempora(0, "", "");
		while (plik >> wynikk >> nickkk >> timeeee) {
			int wynik_ = std::stoi(wynikk);
			tempora.score_ = wynik_;
			tempora.nick = nickkk;
			tempora.time = timeeee;
			wyniki.push_back(tempora);

		}
	}
	std::string lad1 = wyniki[0].merge();
	std::string lad2 = wyniki[1].merge();
	std::string lad3 = wyniki[2].merge();
	char* ladd1 = StrToStr(lad1);
	char* ladd2 = StrToStr(lad2);
	char* ladd3 = StrToStr(lad3);
	scoreTab0->writeText = ladd1;
	scoreTab1->writeText = ladd2;
	scoreTab2->writeText = ladd3;
	scoreTab0->destRect.w = lad1.size() * 25;
	scoreTab1->destRect.w = lad2.size() * 25;
	scoreTab2->destRect.w = lad3.size() * 25;
	scoreTab0->Update(font);
	scoreTab1->Update(font);
	scoreTab2->Update(font);


	background = new Background(bg_path , renderer);
	menu = new Background(menu_path, renderer);
	loginn = new Background(login_path, renderer);
	Scoreboard = new Background(score_path, renderer);
	birdd = new Bird(bird_path, renderer);
	int yposs = -100;
	int xposs = 1000;

	pipedown1 = new PipeDown(pipedown_path, renderer, yposs + 650, xposs);
	pipeup1 = new PipeUp(pipeup_path, renderer, yposs, xposs);
	yposs += 100;

	pipedown2 = new PipeDown(pipedown_path, renderer, yposs + 650, xposs + 400);
	pipeup2 = new PipeUp(pipeup_path, renderer, yposs, xposs + 400);
	yposs += 100;

	pipedown3 = new PipeDown(pipedown_path, renderer, yposs + 650, xposs + 800);
	pipeup3 = new PipeUp(pipeup_path, renderer, yposs, xposs + 800);
	font = TTF_OpenFont("arial.ttf", 25);
	score = new Text(renderer, "Score: ", font,0 ,0);
	score2 = new Text(renderer, "0", font, 150, 0);
	nick = new Text(renderer, " ", font, 150,250);
	nick2 = new Text(renderer, "aleks", font, 400, 0);
	

	score2->destRect.w = 30;
	

	
	srand(time(NULL));
}


char* intToStr(int data) {
	std::string strData = std::to_string(data);

	char* temp = new char[strData.length() + 1];
	strcpy(temp, strData.c_str());

	return temp;
}
void init2() {
	birdd->destRect.x = 50; 
	birdd->destRect.y = 350;
	birdd->gravity2 = 100;
	scoreCountFinal = scoreCount;
	scoreCount = 0;
	pipedown1->destRect.x = 1000;
	pipedown1->destRect.y = 550;
	pipedown2->destRect.x = 1000+400;
	pipedown2->destRect.y = 550;
	pipedown3->destRect.x = 1000+800;
	pipedown3->destRect.y = 550;

	pipeup1->destRect.x = 1000;
	pipeup1->destRect.y = -100;
	pipeup2->destRect.x = 1000+400;
	pipeup3->destRect.x = 1000+800;
	pipeup2->destRect.y = -100;
	pipeup3->destRect.y = -100;
	char* sc = intToStr(scoreCount);
	score2->writeText = sc;
	score2->Update(font);
}

void Game::update()
{
	int  random = rand() % 8;
	if (!isMenu) {
		birdd->Update();
		pipedown1->Update(random);
		pipedown2->Update(random);
		pipedown3->Update(random);
		pipeup1->Update(random);
		pipeup2->Update(random);
		pipeup3->Update(random);
	}
}



void Game::events()
{
	if (!isLogin) {
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
			case SDLK_p:
				if (!isLogin) {
					isMenu = false;
					break;
				}
			case SDLK_s:
				if (!isLogin) {
					isScore = true;
					cntt = true;
					break;
				}

			case SDLK_l:
				if (!isLogin) {
					login = "";
					isLogin = true;
					break;
				}

			case SDLK_q:
				if (!isLogin) {
					isRunning = false;
					break;
				}
			case SDLK_RETURN:
				if (!isLogin) {
					if (isScore) {
						isScore = false;
					}
					
				}

			default:
				break;
			}

			break;

		default:
			break;

		}
	}
	if (isLogin) {
		
		
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_TEXTINPUT:
				
				if (std::regex_match(event.text.text, reg)) {
					login += event.text.text;
				}

				if (login == "l") {
					login = "";
				}
				std::cout << login;
				nick->destRect.w = login.size() * 25;
				nickk = StrToStr(login);
				nick->writeText = nickk;
				nick->Update(font);
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_RETURN:
					isLogin = false;
					nickk2 = nickk;
					nick2->writeText = nickk2;
					nick2->Update(font);
					break;

				case SDLK_BACKSPACE:
					if (login.size() > 0) {
						login.pop_back();
						nick->destRect.w = login.size() * 25;
						std::cout << login;
						nickk = StrToStr(login);
						nick->writeText = nickk;
						nick->Update(font);
						
					}
					break;

				default:
					break;
				}
				break;

			default:
				break;
			}
		}
	}

	if (birdd->destRect.x > pipedown1->destRect.x + 100 && birdd->destRect.x < pipedown1->destRect.x + 104)
	{
		scoreCount++;
		char* sc = intToStr(scoreCount);
		std::cout << sc << std::endl;
		score2->writeText = sc;
		score2->Update(font);
	
	}
	if (birdd->destRect.x > pipedown2->destRect.x + 100 && birdd->destRect.x < pipedown2->destRect.x + 104)
	{
		scoreCount++;
		char* sc = intToStr(scoreCount);
		std::cout << sc << std::endl;
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
	
	if (birdd->destRect.y > 836) { isMenu = true; std::string datee = currentDateTime();
	Score score1(scoreCount, nickk2, datee);
	score1.adding(wyniki, score1); for (auto i : wyniki) {
		std::string temp = i.merge();
		char* tempp = StrToStr(temp);
		if (cntSco == 0) {
			scoreTab0->writeText = tempp;
			scoreTab0->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab0->Update(font);
			}
		}
		if (cntSco == 1) {
			scoreTab1->writeText = tempp;
			scoreTab1->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab1->Update(font);
			}
		}
		if (cntSco == 2) {
			scoreTab2->writeText = tempp;
			scoreTab2->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab2->Update(font);
			}
			cntt = false;
			cntSco = -1;
		}
		cntSco++;

	} init2(); }
	if (birdd->destRect.x+64 > pipedown1->destRect.x && birdd->destRect.x + 64 < pipedown1->destRect.x+140 && birdd->destRect.y > pipedown1->destRect.y-50) 
	{ isMenu = true; std::string datee = currentDateTime();
	Score score1(scoreCount, nickk2, datee);
	score1.adding(wyniki, score1); for (auto i : wyniki) {
		std::string temp = i.merge();
		char* tempp = StrToStr(temp);
		if (cntSco == 0) {
			scoreTab0->writeText = tempp;
			scoreTab0->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab0->Update(font);
			}
		}
		if (cntSco == 1) {
			scoreTab1->writeText = tempp;
			scoreTab1->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab1->Update(font);
			}
		}
		if (cntSco == 2) {
			scoreTab2->writeText = tempp;
			scoreTab2->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab2->Update(font);
			}
			cntt = false;
			cntSco = -1;
		}
		cntSco++;

	} init2();
	}
	if (birdd->destRect.x+64 > pipedown2->destRect.x && birdd->destRect.x + 64 < pipedown2->destRect.x + 140 && birdd->destRect.y > pipedown2->destRect.y-50 ) { isMenu = true; std::string datee = currentDateTime();
	Score score1(scoreCount, nickk2, datee);
	score1.adding(wyniki, score1); for (auto i : wyniki) {
		std::string temp = i.merge();
		char* tempp = StrToStr(temp);
		if (cntSco == 0) {
			scoreTab0->writeText = tempp;
			scoreTab0->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab0->Update(font);
			}
		}
		if (cntSco == 1) {
			scoreTab1->writeText = tempp;
			scoreTab1->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab1->Update(font);
			}
		}
		if (cntSco == 2) {
			scoreTab2->writeText = tempp;
			scoreTab2->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab2->Update(font);
			}
			cntt = false;
			cntSco = -1;
		}
		cntSco++;

	} init2();
	}
	if (birdd->destRect.x+64 > pipedown3->destRect.x && birdd->destRect.x + 64 < pipedown3->destRect.x + 140 && birdd->destRect.y > pipedown3->destRect.y-50 ) { isMenu = true; std::string datee = currentDateTime();
	Score score1(scoreCount, nickk2, datee);
	score1.adding(wyniki, score1); for (auto i : wyniki) {
			std::string temp = i.merge();
			char* tempp = StrToStr(temp);
			if (cntSco == 0) {
				scoreTab0->writeText = tempp;
				scoreTab0->destRect.w = temp.size() * 25;
				if (cntt) {
					scoreTab0->Update(font);
				}
			}
			if (cntSco == 1) {
				scoreTab1->writeText = tempp;
				scoreTab1->destRect.w = temp.size() * 25;
				if (cntt) {
					scoreTab1->Update(font);
				}
			}
			if (cntSco == 2) {
				scoreTab2->writeText = tempp;
				scoreTab2->destRect.w = temp.size() * 25;
				if (cntt) {
					scoreTab2->Update(font);
				}
				cntt = false;
				cntSco = -1;
			}
			cntSco++;
			
		}init2();
	}
	if (birdd->destRect.x+64 > pipeup1->destRect.x && birdd->destRect.x + 64 < pipeup1->destRect.x + 140 && birdd->destRect.y < pipeup1->destRect.y + 400) { isMenu = true; std::string datee = currentDateTime();
	Score score1(scoreCount, nickk2, datee);
	score1.adding(wyniki, score1); for (auto i : wyniki) {
		std::string temp = i.merge();
		char* tempp = StrToStr(temp);
		if (cntSco == 0) {
			scoreTab0->writeText = tempp;
			scoreTab0->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab0->Update(font);
			}
		}
		if (cntSco == 1) {
			scoreTab1->writeText = tempp;
			scoreTab1->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab1->Update(font);
			}
		}
		if (cntSco == 2) {
			scoreTab2->writeText = tempp;
			scoreTab2->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab2->Update(font);
			}
			cntt = false;
			cntSco = -1;
		}
		cntSco++;

	} init2();
	}
	if (birdd->destRect.x+64 > pipeup2->destRect.x && birdd->destRect.x + 64 < pipeup2->destRect.x + 140 && birdd->destRect.y < pipeup2->destRect.y+400) { isMenu = true; std::string datee = currentDateTime();
	Score score1(scoreCount, nickk2, datee);
	score1.adding(wyniki, score1); for (auto i : wyniki) {
		std::string temp = i.merge();
		char* tempp = StrToStr(temp);
		if (cntSco == 0) {
			scoreTab0->writeText = tempp;
			scoreTab0->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab0->Update(font);
			}
		}
		if (cntSco == 1) {
			scoreTab1->writeText = tempp;
			scoreTab1->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab1->Update(font);
			}
		}
		if (cntSco == 2) {
			scoreTab2->writeText = tempp;
			scoreTab2->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab2->Update(font);
			}
			cntt = false;
			cntSco = -1;
		}
		cntSco++;

	} init2();
	}
	if (birdd->destRect.x+64 > pipeup3->destRect.x && birdd->destRect.x + 64 < pipeup3->destRect.x + 140 && birdd->destRect.y < pipeup3->destRect.y+400) { isMenu = true; std::string datee = currentDateTime();
	Score score1(scoreCount, nickk2, datee);
	score1.adding(wyniki, score1); for (auto i : wyniki) {
		std::string temp = i.merge();
		char* tempp = StrToStr(temp);
		if (cntSco == 0) {
			scoreTab0->writeText = tempp;
			scoreTab0->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab0->Update(font);
			}
		}
		if (cntSco == 1) {
			scoreTab1->writeText = tempp;
			scoreTab1->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab1->Update(font);
			}
		}
		if (cntSco == 2) {
			scoreTab2->writeText = tempp;
			scoreTab2->destRect.w = temp.size() * 25;
			if (cntt) {
				scoreTab2->Update(font);
			}
			cntt = false;
			cntSco = -1;
		}
		cntSco++;

	} init2();
	}
	
}


void Game::render()
{
	SDL_RenderClear(renderer);
	if (isMenu) {
		menu->Render();
	}
	if (isLogin) {
		loginn->Render();
		nick->Render();
	}
	if (isScore) {
		Scoreboard->Render();
		
		
		scoreTab0->Render();
		scoreTab1->Render();
		scoreTab2->Render();

	}
	if (!isMenu) {
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
		nick2->Render();
		
	}
	
	SDL_RenderPresent(renderer);

}
void zapis(std::string nazwa,std::vector<Score> scores) {
	std::ofstream plik(nazwa);
	if (plik) {
		
		for(auto i: scores) {
			plik << i.score_ << " " << i.nick << " " << i.time << "\n";
		}
	}
}

void Game::clean()
{
	std::cout << wyniki.size();
	zapis("score.txt", wyniki);
	SDL_StopTextInput();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	std::cout << "everything cleaned" << std::endl;
}


