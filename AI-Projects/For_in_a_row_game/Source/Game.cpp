#ifndef GAME_CPP
#define GAME_CPP
#include <iostream>

#include "Game.h"

Game::Game(int whoBegins, int time) {
	MAX_TIME = time;
	if (whoBegins == 0) {
		header_of_plays = "Player vs. Opponent";
		AI = new Agent(time, 'X');
	}
	
	else {
		header_of_plays = "Opponent vs. Player";
		AI = new Agent(time, 'O');
	}
	
	b = new State();
	even_turn = true;
	moves = "";
	who_won = "";
	num_of_plays = 1;
	//AI = new Agent(time, 'X');
}

bool Game::make_move(std::string move) {
	if (move.length() > 3)
		return false;

	bool success = false;
	if(even_turn){
		success =  b->make_move(move, 'X');
		if(success){
			moves += move;
			moves += " ";
			even_turn = false;
			return success;
		}
	}
	else{
		num_of_plays++;
		success = b->make_move(move, 'O');
		if(success){
			moves += move;
			even_turn = true;
			return success;
		}
	}

	return false;
}
void Game::show_game() {
	const std::string* board = b->get_board();

	std::cout << "  1 " << "2 " << "3 " << "4 " << "5 " << "6 " << "7 " << "8 "
		<< "\t" << header_of_plays << "\n";
	for (int i = 0; i < 8 || i <= (moves.length() / 5); i++) {
		if (i < 8) {//this will print the board
			char row = '0';
			if (i == 0) { row = 'A'; }
			else if (i == 1) { row = 'B'; }
			else if (i == 2) { row = 'C'; }
			else if (i == 3) { row = 'D'; }
			else if (i == 4) { row = 'E'; }
			else if (i == 5) { row = 'F'; }
			else if (i == 6) { row = 'G'; }
			else if (i == 7){ row = 'H'; }
			
			std::cout << row << " ";
				for (int j = 0; j < 8; j++) {
				std::cout << board[i][j] << " ";
			}
		}
		else{
			std::cout << "\t\t";
		}
		try {
			if(i*5 + 1 < moves.size())
				std::cout << "\t   " << i+1 << ". " << moves.substr(i * 5, 5);
			if((i+1)*5 == moves.size() || (i * 5 + 3) == moves.size())
				std::cout << " " << who_won;
		}
		catch (...) {
			if (i * 5 + 3 <= moves.length()) 
				std::cout << "\t   " << i+1 << ". " << moves.substr(i * 5, 3);
			//if( (i*5 + 3) == moves.size() -1)
				//std::cout << " " << who_won;
		}
		
		std::cout << "\n";
	} 
}

bool Game::check_win(){
	const std::string* board = b->get_board();
	//This method will check the if a win is reached, either X or O
	for(int row = 0; row < 8; row++){
		for(int col = 0; col < 8; col++){
			if(board[row][col] != '-'){
				char player = board[row][col];
				//check for horizontal win
				//since the code checks from right to left, it will
				// never be a left side win
				if(col <5){
					bool win = true;
					for(int i = col; i < col + 4; i++){
						if(board[row][i] != player)
							win = false;
					}
					if(win){
						who_won += player;
						who_won += " Won";
						return true;
					}
				}

				//check for vertical win
				//since the code is always check from up towards down
				//it will never need to check low to high
				if(row < 5){
					bool win = true;
					for(int i = row; i < row + 4; i++){
						if(board[i][col] != player)
							win = false;
					}
					if(win){
						who_won += player;
						who_won += " Won";
						return true;
					}
				}
			}
		}//end of for-col
	}//end of for-row
	return false;
}

bool Game::make_play(std::string move){
	return make_move(move) && check_win();
	
}

bool Game::AI_play() {
	//std::cout << AI->debug(*b) << std::endl;
	return make_move( AI->make_move(*b) ) && check_win();
}

#endif
