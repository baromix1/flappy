#pragma once
#include <chrono>
#include <ctime> 

class Score {
public:
	int score_;
	std::string nick;
	std::string time;

	Score(int score_,std::string nick, std::string time);
	std::string merge();
	void adding(std::vector<Score>& scores, Score scor);
};