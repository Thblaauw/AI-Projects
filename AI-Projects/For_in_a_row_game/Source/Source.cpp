#include <iostream>
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>

using namespace std;

int main() {
	cout << "Welcome to 4-in-line" << endl
		<< "Who is going to start playing?" << endl
		<< "   0- Agent" << endl
		<< "   1- Opponent" << endl;
	int player;
	cin >> player;

	cout << "How long does the agent have to make its move?" << endl;
	int time;
	cin >> time;

	system("cls");

	Game g(player, time);
	string input = "";
	bool win = false;

	

	if(player == 0)
		while (input != "0" && !win) {
			g.AI_play();
			g.show_game();
			cin >> input;
			system("cls");
			win = g.make_play(input);
			g.show_game();
			//system("cls");
		}
	else
		while (input != "0" && !win) {
			g.show_game();
			cin >> input;
			//system("cls");
			win = g.make_play(input);
			g.show_game();
			g.AI_play();
			system("cls");
			
		}
	//g.show_game();
	system("pause");
	return 0;
}
