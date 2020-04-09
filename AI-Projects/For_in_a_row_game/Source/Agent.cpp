#ifndef AGENT_CPP
#define AGENT_CPP

#include "Agent.h"

#include <iostream>
#include <algorithm>
#include <chrono>
#include <stdlib.h>
#include <time.h>  

Agent::Agent(int timer, char p) {
	srand(time(NULL));
	MAX_TIME = timer;

	if (p == 'X')
		opponent = 'O';
	else
		opponent = 'X';

	player = p;

	num_of_plays = 0;
	is_first_move = true;
}

std::string Agent::first_move(State initial_state) {
	bool done = false;
	std::string mov = "";
	while (!done) {
		int col = rand() % 2;
		int row = rand() % 2;
		if (initial_state.get_board()[3 + col][3 + row] == '-') {
			char row_c = ('d' + col);
			char col_c = ('4' + row);
			mov += row_c;
			mov += col_c;
			is_first_move = false;
			done = true;
		}
	}
	return mov;
}
std::string Agent::make_move(State initial_state){
	//This state will call the MinMax search and return a string contatining the move
	if (is_first_move)
		return first_move(initial_state);
	std::string best_mov = "";
	std::string best_mov_run = "";
	int depth = 2;
	start_time = std::chrono::high_resolution_clock::now();
	try{
		depth_of_search = depth;
		int alpha = -10000;
		int beta = 10000;
		int best_value = alpha;
		
		while(true){
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					std::string mov = "";
					char row = ('a' + i);
					char col = ('1' + j);
					mov += row;
					mov += col;
					//std::cout << i << std::endl;
					//State* st = new State(&initial_state);
					if (initial_state.make_move(mov, player)) {
						int val = min(&initial_state, best_value, beta, depth-1);
						//std::cout << mov << "-" << val << " ";
						if(val > best_value){
							best_value = val;
							best_mov_run = mov;
						}
						initial_state.undo(mov);
					}
						
				}//end of for-j
				//std::cout << std::endl;
			}//end of for-i
			best_mov = best_mov_run;
			best_value = alpha;
			if (depth == 2)
				depth = 5;
			else {
				depth++;
				depth_of_search++;
			}
		}//end of while
	}//end of try
	catch(...){
		std::cout << std::endl;
		return best_mov;
	}//end of catch
	return best_mov;
}

int Agent::max(State* s, int alpha, int beta, int depth){
	if (s->check_win())
		return -10000 + (depth_of_search - depth);

	if (depth <= 0) {
		return heuristic(*s);
	}
	int val;
	int best_value = -10000;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::string mov = "";
			char row = ('a' + i);
			char col = ('1' + j);
			mov += row;
			mov += col;
			//State* st = new State(s);
			if (s->make_move(mov, player)) {
				val = min(s, alpha, beta, depth - 1);
				best_value = std::max(best_value, val);
				alpha = std::max(alpha, best_value);
				//pruning section
				if (alpha >= beta){
					i = 8;
					j = 8;
				}
				s->undo(mov);
			}
		}
	}
	return best_value;
}

int Agent::min(State* s, int alpha, int beta, int depth){
	if (s->check_win())
		return 10000 - (depth_of_search - depth);

	if (depth <= 0) {
		return heuristic(*s);
	}
	

	int best_value = 10000;
	int val;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::string mov = "";
			char row = ('a' + i);
			char col = ('1' + j);
			mov += row;
			mov += col;
			//State* st = new State(s);
			if (s->make_move(mov, opponent)) {
				val = max(s, alpha, beta, depth - 1);
				best_value = std::min(best_value, val);
				beta = std::min(beta, best_value);
				//pruning section
				if (alpha >= beta) {
					i = 8;
					j = 8;
				}
				s->undo(mov);	
			}
		}

	}
	
	return best_value;
}

int Agent::debug(State& s){
	return heuristic(s);
}

int Agent::heuristic(State& s){

	end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(end_time - start_time);
	if (time_span.count() > MAX_TIME)
		throw "Time out";

	int h_value = 0;
	const std::string* s_board = s.get_board();

	//possibility of winning X
	for(int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++) {
			// each vertical possibility for X = +1
			// each vertical possibility for O = -1
			if (s_board[i][j] != '-'){
				if (i < 5) {
					bool x_col = true;
					bool o_col = true;

					int x_count = 1;
					int o_count = 1;
					for (int k = i; k < i + 4; k++) {
						if (s_board[k][j] == opponent) {// O in the col
							x_col = false;
							h_value -= 2;
							o_count = o_count + 1;
						}
						else if (s_board[k][j] == player) { // X in the col
							o_col = false;
							h_value += 2;
							x_count = x_count + 1;
						}
						
					}
					if (x_col)
						h_value += (1 + x_count);
					if (o_col)
						h_value -= (1 + o_count);
				}//end if

				if (i > 2) {
					bool x_col = true;
					bool o_col = true;

					int x_count = 1;
					int o_count = 1;
					for (int k = i; k > i - 4; k--) {
						if (s_board[k][j] == opponent) {// O in the col
							x_col = false;
							h_value -= 2;
							o_count = o_count + 1;
						}
						else if (s_board[k][j] == player) { // X in the col
							o_col = false;
							h_value += 2;
							x_count = x_count + 1;
						}
						
					}
					if (x_col)
						h_value += (1 + x_count);
					if (o_col)
						h_value -= (1 + o_count);
				}//end if
				//each horizontal possibility for X = +1
				//each horizontal possibility for O = -1;
				if (j < 5) {
					bool x_row = true;
					bool o_row = true;

					int x_count = 1;
					int o_count = 1;
					for (int k = j; k < j + 4; k++) {
						if (s_board[i][k] == opponent) {//no O in the row
							x_row = false;
							h_value -= 2;
							o_count = o_count + 1;
						}
						else if (s_board[i][k] == player) { // no X in the row
							o_row = false;
							h_value += 2;
							x_count = x_count + 1;
						}
						
					}
					if (x_row)
						h_value += (1 + x_count);
					if (o_row)
						h_value -= (1 + o_count);
				}//end if
				if (j > 2) {
					bool x_row = true;
					bool o_row = true;

					int x_count = 1;
					int o_count = 1;
					for (int k = j; k > j - 4; k--) {
						if (s_board[i][k] == opponent) {//no O in the row
							x_row = false;
							h_value -= 2;
							o_count = o_count + 1;
						}
						else if (s_board[i][k] == player) { // no X in the row
							o_row = false;
							h_value += 2;
							x_count = x_count + 1;
						}
					}
					if (x_row)
						h_value += (1 + x_count);
					if (o_row)
						h_value -= (1 + o_count);
				}//end if
			}//end if
		}//end for-j
	}//end for-i

	return h_value;
}

#endif // AGENT_CPP
