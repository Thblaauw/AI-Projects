#include <iostream>	
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <chrono>

#include "Node.h"
#include "TreeSearch.h"
#include "GraphSearch.h"

using namespace std;

void generate_random_board( int board[], int size) {
	for (int i = 0; i < size; i++) {
		board[i] = -1; // resets the board
	}

	for (int i = 0; i < size; i++) {
		int location;
		bool isDone = false;

		// this loop will keep tryin to find a location that is not used and then it will exit
		// -1 means the location is ot being used and is open for a piece
		do {
			location = rand() % size;
			if (board[location] == -1) {
				board[location] = i;
				isDone = true;
			}
		} while (!isDone);
	}
}

bool isSolvable(int board[], int size) {
	int num_of_invertions = 0;
	for (int i = 0; i < size ; i++) {
		if (board[i] < 0 && board[i] > 8)
			return false;
	}
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) 
			if (board[i] > board[j] && board[i] != 0 && board[j] != 0)
				num_of_invertions++;
	}

	if (num_of_invertions % 2 == 0)
		return true;
	return false;
}

int h_1(int board[], int size) {
	int heuristic = 0;
	for (int i = 0; i < 9; i++) {
		//starts at 1 so it does not count 0
		if (board[i] != i && board[i] != 0)
			heuristic++;
	}
	return heuristic;
}

int h_2(int board[], int size) {
	/*
		The distance calculated here is an absolute value. Therefore is 7 is on the
		i = 1, the distance will be 6 (6 blocks away) and vertical movement is 
		prioritized. the same will happen if 1 is on i = 7, same distance and movement. 
		On the board, 7 should move down while 1 should move up, but the distances are the same
	*/
	int heuristic = 0;
	for (int i = 0; i < 9; i++) {
		if (board[i] != 0) {
			if (board[i] > i) {
				int distance = board[i] - i;
				while (distance > 0) {
					if (distance >= 3) { // distance >= 3 - vertical movement
						distance -= 3;
						heuristic++;
					}
					else {// distance < 3 - horizontal movement
						distance--;
						heuristic++;
					}
				}
				
			}//--------------------------------------------
			else if (board[i] < i) {
				int distance = i - board[i];
				while (distance > 0) {
					if (distance >= 3) {  // distance >= 3 - vertical movement
						distance -= 3;
						heuristic++;
					}
					else {// distance < 3 - horizontal movement
						distance--;
						heuristic++;
					}
				}

			}//end of else if
			
		}// end of if
	}// end of for

	return heuristic;
}

int main() {
	int board[9];
	srand(time(NULL));
	int menu_option = 0;

	do {
		std::cout << "1) Create a random 8-puzzle" << std::endl
			<< "2) Input an 8-puzzle" << std::endl
			<< "3) Exit" << std::endl;
		cin >> menu_option;

		if (menu_option == 1) {
			generate_random_board(board, 9);
			for (int i = 0; i < 9; i++) {
				cout << board[i] << " ";
			}
			cout << endl;
			if (isSolvable(board, 9)) {
				cout << "Is Solvable" << endl;

				cout << endl << "Tree Search with h1" << endl;
				TreeSearch *t1 = new TreeSearch(board, h_1);

				cout << endl << "Tree Search with h2" << endl;
				TreeSearch *t2 = new TreeSearch(board, h_2);

				cout << endl << "Graph Search with h1" << endl;
				GraphSearch *g1 = new GraphSearch(board, h_1);

				cout << endl<< "Graph Search with h2" << endl;
				GraphSearch *g2 = new GraphSearch(board, h_2);

				delete g1;
				delete g2;

				delete t1;
				delete t2;
			}
			else
				cout << "Not Solvable" << endl;
			
			

		}//----------------------------------------------------
		else if (menu_option == 2) {
			int fboard[] = { 3, 1, 2, 6, 4, 5, 0, 7, 8 };
			
			for (int i = 0; i < 9; i++) {
				cin >> board[i];
			}
			cout << endl;
			if (isSolvable(board, 9)) {
				cout << "Is Solvable" << endl;
				
				cout << endl << "Tree Search with h1" << endl;
				TreeSearch *t1 = new TreeSearch(board, h_1);

				cout << endl << "Tree Search with h2" << endl;
				TreeSearch *t2 = new TreeSearch(board, h_2);

				cout << endl << "Graph Search with h1" << endl;
				GraphSearch *g1 = new GraphSearch(board, h_1);

				cout << endl << "Graph Search with h2" << endl;
				GraphSearch *g2 = new GraphSearch(board, h_2);

				delete g1;
				delete g2;

				delete t1;
				delete t2;
			}
			else
				cout << "Not Solvable" << endl;
			
			
		}//------------------------------------------------------------
		
	} while (menu_option != 3);

	return 0;
}