#ifndef AGENT_H
#define AGENT_H

#include "State.h"
#include <string>
#include <chrono>

class Agent {

private:
	int MAX_TIME;

	int heuristic(State& s);
	int max(State* s, int alpha, int beta, int depth);
	int min(State* s, int alpha, int beta, int depth);
	int depth_of_search;
	char opponent;
	char player;
	int num_of_plays;
	std::chrono::high_resolution_clock::time_point start_time;
	std::chrono::high_resolution_clock::time_point end_time;
	bool is_first_move;

public:
	Agent(int time, char p);
	int debug(State& s);
	std::string make_move(State initial_state);
	std::string first_move(State initial_state);
};
#endif // !AGENT_H

