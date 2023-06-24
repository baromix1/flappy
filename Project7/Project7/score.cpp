#define _CRT_SECURE_NO_WARNINGS
#include "score.h"
#include <chrono>
#include <ctime> 
#include <iostream>
#include <ranges>

Score::Score(int score__, std::string nick_, std::string time_) {
	score_ = score__;
	nick = nick_;
	time = time_;
}
std::string Score::merge() {
	std::string merged = std::to_string(score_) + " " + nick + " " + time;
	return merged;
}
void Score::adding(std::vector<Score> &scores, Score scor) {
	/*Score temp(0,"","");
	for (auto i : scores) {
		if (i.score_ < scor.score_) {
			temp = i;
			i = scor;
			scor = temp;
		}
	}*/

	scores.push_back(scor);
	std::ranges::sort(scores, [](Score &i, Score &j) {return i.score_ > j.score_; });
	scores.pop_back();
}