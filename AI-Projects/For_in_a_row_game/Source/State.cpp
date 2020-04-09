#ifndef STATE_CPP
#define STATE_CPP

#include "State.h"

State::State(std::string b[8]){
	for(int i = 0; i < 8; i++)
		board[i] = b[i]; 
}

State::State(){
	for(int i = 0; i < 8; i++)
		board[i] = "--------"; 
}

State::State(const State* s){
	const std::string* st = s->get_board();
	for(int i = 0; i < 8; i++)
		board[i] = st[i]; 
	this->parent_state = s;
}

State::~State(){}

bool State::check_win() {
	//This method will check the if a win is reached, either X or O
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (board[row][col] != '-') {
				char player = board[row][col];
				//check for horizontal win
				//since the code checks from right to left, it will
				// never be a left side win
				if (col < 5) {
					bool win = true;
					for (int i = col; i < col + 4; i++) {
						if (board[row][i] != player)
							win = false;
					}
					if (win) {
						return true;
					}
				}

				//check for vertical win
				//since the code is always check from up towards down
				//it will never need to check low to high
				if (row < 5) {
					bool win = true;
					for (int i = row; i < row + 4; i++) {
						if (board[i][col] != player)
							win = false;
					}
					if (win) {
						return true;
					}
				}
			}
		}//end of for-col
	}//end of for-row
	return false;

}

bool State::make_move(std::string move, char player) {
	if (move.length() > 3)
		return false;

	try {
		/*
		int row;
		if (move[0] == 'a') { row = 0; }
		else if (move[0] == 'b') { row = 1; }
		else if (move[0] == 'c') { row = 2; }
		else if (move[0] == 'd') { row = 3; }
		else if (move[0] == 'e') { row = 4; }
		else if (move[0] == 'f') { row = 5; }
		else if (move[0] == 'g') { row = 6; }
		else if (move[0] == 'h') { row = 7; }
		else { return false; } // out of bounds

		if (move[1] == '1' && board[row][0] == '-') {
			board[row][0] = player;
		}

		else if (move[1] == '2' && board[row][1] == '-') {
			board[row][1] = player;
		}

		else if (move[1] == '3' && board[row][2] == '-') {
			board[row][2] = player;
		}

		else if (move[1] == '4' && board[row][3] == '-') {
			board[row][3] = player;
		}

		else if (move[1] == '5' && board[row][4] == '-') {
			board[row][4] = player;
		}

		else if (move[1] == '6' && board[row][5] == '-') {
			board[row][5] = player;
		}

		else if (move[1] == '7' && board[row][6] == '-') {
			board[row][6] = player;
		}

		else if (move[1] == '8' && board[row][7] == '-') {
			board[row][7] = player;
		}

		else { return false; } // out of bounds
		*/

		int row = move[0] - 'a';
		int col = move[1] - '1';

		if (row >= 0 && row < 8 && col >= 0 && col < 8){
			if(board[row][col] == 'X' || board[row][col] == 'O')
				return false;
			board[row][col] = player;
			return true;
		}
		return false;

	}
	catch (...) {
		return false;
	}
	return true;
}

const std::string* State::get_board() const{
	return board;
}

bool State::undo(std::string move){
	int row = move[0] - 'a';
	int col = move[1] - '1';
	board[row][col] = '-';
	return true;
}

std::vector<State*>* State::branch(char player) {
	std::vector<State*>* vect = new std::vector<State*>();
	std::string s = "";
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			std::string s = "";
			char row = ('a' + i);
			char col = ('1' + j);
			s += row;
			s += col;
			State* st = new State(*this);
			if (st->make_move(s, player)) 
				vect->push_back(st);
		}

	}

	return vect;
}

#endif
