#ifndef GAME_H
#define GAME_H

#include <string>
#include "Agent.h"
#include "State.h"

class Game {

private:
	/*board will be represented by an array of chars
	1 char has 8 bytes, each bit for a column
	*/
	State* b;
	//std::string board[8];
	std::string header_of_plays;
	int MAX_TIME;
	std::string moves;
	bool even_turn;
	Agent *AI;
	std::string who_won;
	int num_of_plays;
	
	bool check_win();
	bool make_move(std::string move);

public:
	Game(int whoBegins, int time);
	void show_game();
	bool make_play(std::string move);
	bool AI_play();
};

#endif
