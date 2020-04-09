#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <queue>
#include <chrono>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

const int BOARD_SIZE = 25;

bool generate_random_board(vector<int> &board) {
	try {
		for (int i = 0; i < board.size(); i++)
			board[i] = rand() % BOARD_SIZE; // This will initialize the queens on rows 0 to BOARD_SIZE - 1
		return true;
	}
	catch (...) {
		return false;
	}
}

void debug_print_board(vector<int> board) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[j] == BOARD_SIZE - i - 1)
				cout << "Q\t";
			else
				cout << "*\t";
		}
		cout << endl;
	}
}

int attacking_queen_pairs(vector<int> &board) {
	/*
		This method will compare the pairs as represented in the following diagram

		  /
		 /
		Q------
		 \
		  \
	*/
	int pairs = 0;
	for (int i = 0; i < board.size() - 1; i++) {
		for (int j = i + 1; j < board.size(); j++) {
			if (board[i] == board[j]) //same row
				pairs++; 
			if (board[i] + (j- i) == board[j]) // upper diagonal
				pairs++;
			if	(board[i] - (j - i) == board[j]) // lower diagonal
				pairs++;
		}
	}
	return pairs;
}

//Simulated annealing
vector<int> simulated_anneling(vector<int> board) {
	vector<int> current;
	current = board;
	double t = 0.001f;
	auto start = std::chrono::high_resolution_clock::now();
	int current_pairs_num = attacking_queen_pairs(current);
	while (true) {
		vector<int> next;
		next = current;
		//take a step
		next[rand() % BOARD_SIZE] = rand() % BOARD_SIZE;
		float Temp = -logf(t);

		if (Temp <= 0 || current_pairs_num == 0)
			return current;

		int  next_pairs_num = attacking_queen_pairs(next);
		int E = current_pairs_num - next_pairs_num; // negative is a bad move
		if (E > 0){
			current = next;
			current_pairs_num = next_pairs_num;
		}
		else {
			float p = (float) (rand() % 10000)/10000.000f;
			if (p < exp(E / Temp)) {
				current = next;
				current_pairs_num = next_pairs_num;
			}
		}

		//t = (std::chrono::high_resolution_clock::now() - start).count() / 300000.00f;
		t += 0.000001f;
	}
}

// Genetic algorithm
const int POPULATION_SIZE = 4000;

vector<int> reproduce(vector<int> &p1, vector<int>& p2) {
	vector<int> child;
	child.resize(p1.size());
	int crossover = rand() % (child.size() - 1) + 1; //from 1 to 23
	for (int i = 0; i < child.size(); i++) {
		if (i <= crossover)
			child[i] = p1[i];
		else
			child[i] = p2[i];
	}
	return child;
}

vector<int> genetic_algorithm_helper(vector<vector<int>> pop, int population_count) {
	//defining the priority queue comparing function
	
	auto comp = [] (vector<int>& lhs, vector<int>& rhs) 
	{
		return attacking_queen_pairs(lhs) < attacking_queen_pairs(rhs);
	};
	
	/*priority_queue<vector<int>, vector<vector<int>>, LessThanByFitnessFunction> *ordered_population = 
		new priority_queue<vector<int>, vector<vector<int>>, LessThanByFitnessFunction>();*/
	vector<vector<int>>  population = pop;
	sort(population.begin(), population.end(), comp);

	vector<vector<int>> new_population;

	if (attacking_queen_pairs(population[0]) == 0)
		return population[0];
	for (int i = 0; i < 10; i++) {
		do {

			for (int j = 0; j < POPULATION_SIZE; j++) {
				int x = rand() % 1500;
				int y = rand() % 1500;

				vector<int> parent1 = population[x];

				vector<int> parent2 = population[y];

				vector<int> child = reproduce(parent1, parent2);

				float p = (float)(rand() % 100) / 100.000f;
				if (p <= 0.45f) { //mutation rate
					int location = (rand() % child.size());
					child[location] = (rand() % child.size());
				}
				/*else if (p <= 0.9f){
					int location = (rand() % child.size());
					child[location] = (rand() % child.size());
				}*/
				new_population.push_back(child);
			}
			population_count++;
			population.clear();
			population = new_population;
			new_population.clear();
			sort(population.begin(), population.end(), comp);
		} while (attacking_queen_pairs(population[0]) != 0 && population_count < 200);
		if (attacking_queen_pairs(population[0]) == 0)
			i = 10;
		else {
			population = pop;
			population_count = 0;
		}
	}

	return population[0];
}


vector<int> genetic_algorithm(vector<int> initial_prob) {
	//this generate the inital population
	vector<vector<int>> initial_pop;
	initial_pop.push_back(initial_prob);
	for (int i = 1; i < POPULATION_SIZE; i++) {
		vector<int> toAdd = initial_prob;
		toAdd[rand() % BOARD_SIZE] = rand() % BOARD_SIZE;
		initial_pop.push_back(toAdd);
	}

	return genetic_algorithm_helper(initial_pop, 0);
}

int main() {

	srand(time(NULL));
	vector<int> board;
	board.resize(BOARD_SIZE);
	int menu = 0;

	while (menu != 5) {
		cout << "1) Simulated Annealing: Random board" << endl
			<< "2) Simulated Annealing: input" << endl
			<< "3) Genetic Algorithm: Random board" << endl
			<< "4) Genetic Algorithm: input" << endl
			<< "5) Exit" << endl << endl;
		cin >> menu;
		if (menu == 1) {
			generate_random_board(board);
			for (int i = 0; i < board.size(); i++)
				cout << board[i] << " ";
			cout << endl << "Attacking queen pairs: " << attacking_queen_pairs(board) << endl << endl;
			vector<int> result = simulated_anneling(board);
			for (int i = 0; i < board.size(); i++)
				cout << result[i] << " ";
			cout << endl << "Attacking queen pairs: " << attacking_queen_pairs(result) << endl << endl;
		}
		else if (menu == 2) {
			for (int i = 0; i < board.size(); i++)
				cin >> board[i];
			cout << endl << "Attacking queen pairs: " << attacking_queen_pairs(board) << endl << endl;
			vector<int> result = simulated_anneling(board);
			for (int i = 0; i < board.size(); i++)
				cout << result[i] << " ";
			cout << endl << "Attacking queen pairs: " << attacking_queen_pairs(result) << endl << endl;
		}
		else if (menu == 3) {
			generate_random_board(board);
			for (int i = 0; i < board.size(); i++)
				cout << board[i] << " ";
			cout << endl << "Attacking queen pairs: " << attacking_queen_pairs(board) << endl << endl;
			vector<int> result = genetic_algorithm(board);
			for (int i = 0; i < board.size(); i++)
				cout << result[i] << " ";
			cout << endl << "Attacking queen pairs: " << attacking_queen_pairs(result) << endl << endl;
		}
		else if (menu == 4) {
			for (int i = 0; i < board.size(); i++)
				cin >> board[i];
			cout << endl << "Attacking queen pairs: " << attacking_queen_pairs(board) << endl << endl;
			vector<int> result = genetic_algorithm(board);
			for (int i = 0; i < board.size(); i++)
				cout << result[i] << " ";
			cout << endl << "Attacking queen pairs: " << attacking_queen_pairs(result)<< endl << endl;
		}
		else if(menu != 5)
			cout << "Option not specified" << endl;
	}
	

	return 0;
}
