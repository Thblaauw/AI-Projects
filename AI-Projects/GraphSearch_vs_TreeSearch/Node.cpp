#ifndef NODE_CPP
#define NODE_CPP

#include "Node.h"
#include <iostream>

Node::Node(int b[9], int (*heuristic_calc)(int[] , int ), int pc) {
	for (int i = 0; i < 9; i++) {
		board[i] = b[i];
	}
	for (int i = 0; i < 4; i++) {
		children_nodes[i] = nullptr;
	}
	heuristic_val = heuristic_calc(b, 9);
	path_cost = pc + 1;
	heuristic_cal = heuristic_calc;
	parent_node = nullptr;
}
Node::~Node() {
	if(children_nodes[0] != nullptr)
		delete[] children_nodes;
}

int* Node::get_board() {
	return board;
}
Node* Node::get_parent_node() {
	return parent_node;
}
Node** Node::get_children_nodes() {
	return children_nodes;
}

int Node::get_path_cost() {
	return path_cost;
}
int Node::get_h_val() {
	return heuristic_val;
}

int Node::expand() {
	/*
	this function will expand nodes based on the location of 0
	0th-> right and down
	1st-> right, down, left
	2nd-> down, left
	3rd-> up, right, down
	4th-> up, right, down, left
	5th-> up, down, left
	6th-> up, right
	7th-> up, right, left
	8th-> up, left
	*/

	int zero_location = 0;
	while (board[zero_location] != 0)
		zero_location++;

	if (zero_location == 0) {
		this->children_nodes[0] = new Node(board, heuristic_cal, path_cost);
		children_nodes[0]->move_right(zero_location);
		children_nodes[0]->set_parent_node(this);

		this->children_nodes[1] = new Node(board, heuristic_cal, path_cost);
		children_nodes[1]->move_down(zero_location);
		children_nodes[1]->set_parent_node(this);

		return 2;
	}
	else if (zero_location == 1) {
		this->children_nodes[0] = new Node(board, heuristic_cal, path_cost);
		children_nodes[0]->move_right(zero_location);
		children_nodes[0]->set_parent_node(this);

		this->children_nodes[1] = new Node(board, heuristic_cal, path_cost);
		children_nodes[1]->move_down(zero_location);
		children_nodes[1]->set_parent_node(this);

		this->children_nodes[2] = new Node(board, heuristic_cal, path_cost);
		children_nodes[2]->move_left(zero_location);
		children_nodes[2]->set_parent_node(this);

		return 3;
	}
	else if (zero_location == 2) {
		this->children_nodes[0] = new Node(board, heuristic_cal, path_cost);
		children_nodes[0]->move_down(zero_location);
		children_nodes[0]->set_parent_node(this);

		this->children_nodes[1] = new Node(board, heuristic_cal, path_cost);
		children_nodes[1]->move_left(zero_location);
		children_nodes[1]->set_parent_node(this);

		return 2;
	}
	else if (zero_location == 3) {
		this->children_nodes[0] = new Node(board, heuristic_cal, path_cost);
		children_nodes[0]->move_up(zero_location);
		children_nodes[0]->set_parent_node(this);

		this->children_nodes[1] = new Node(board, heuristic_cal, path_cost);
		children_nodes[1]->move_right(zero_location);
		children_nodes[1]->set_parent_node(this);

		this->children_nodes[2] = new Node(board, heuristic_cal, path_cost);
		children_nodes[2]->move_down(zero_location);
		children_nodes[2]->set_parent_node(this);


		return 3;

	}
	else if (zero_location == 4) {
		this->children_nodes[0] = new Node(board, heuristic_cal, path_cost);
		children_nodes[0]->move_up(zero_location);
		children_nodes[0]->set_parent_node(this);

		this->children_nodes[1] = new Node(board, heuristic_cal, path_cost);
		children_nodes[1]->move_right(zero_location);
		children_nodes[1]->set_parent_node(this);

		this->children_nodes[2] = new Node(board, heuristic_cal, path_cost);
		children_nodes[2]->move_down(zero_location);
		children_nodes[2]->set_parent_node(this);

		this->children_nodes[3] = new Node(board, heuristic_cal, path_cost);
		children_nodes[3]->move_left(zero_location);
		children_nodes[3]->set_parent_node(this);

		return 4;
	}
	else if (zero_location == 5) {
		this->children_nodes[0] = new Node(board, heuristic_cal, path_cost);
		children_nodes[0]->move_up(zero_location);
		children_nodes[0]->set_parent_node(this);

		this->children_nodes[1] = new Node(board, heuristic_cal, path_cost);
		children_nodes[1]->move_down(zero_location);
		children_nodes[1]->set_parent_node(this);

		this->children_nodes[2] = new Node(board, heuristic_cal, path_cost);
		children_nodes[2]->move_left(zero_location);
		children_nodes[2]->set_parent_node(this);

		return 3;
	}
	else if (zero_location == 6) {
		this->children_nodes[0] = new Node(board, heuristic_cal, path_cost);
		children_nodes[0]->move_up(zero_location);
		children_nodes[0]->set_parent_node(this);

		this->children_nodes[1] = new Node(board, heuristic_cal, path_cost);
		children_nodes[1]->move_right(zero_location);
		children_nodes[1]->set_parent_node(this);

		return 2;
	}
	else if (zero_location == 7) {
		this->children_nodes[0] = new Node(board, heuristic_cal, path_cost);
		children_nodes[0]->move_up(zero_location);
		children_nodes[0]->set_parent_node(this);

		this->children_nodes[1] = new Node(board, heuristic_cal, path_cost);
		children_nodes[1]->move_right(zero_location);
		children_nodes[1]->set_parent_node(this);

		this->children_nodes[2] = new Node(board, heuristic_cal, path_cost);
		children_nodes[2]->move_left(zero_location);
		children_nodes[2]->set_parent_node(this);

		return 3;
	}
	else if (zero_location == 8) {
		this->children_nodes[0] = new Node(board, heuristic_cal, path_cost);
		children_nodes[0]->move_up(zero_location);
		children_nodes[0]->set_parent_node(this);

		this->children_nodes[1] = new Node(board, heuristic_cal, path_cost);
		children_nodes[1]->move_left(zero_location);
		children_nodes[1]->set_parent_node(this);

		return 2;
	}
	else {
		return 0;
	}
	
}
int Node::get_total_cost() {
	return path_cost + heuristic_val;
}

void Node::set_parent_node(Node* parent) {
	this->parent_node = parent;
}

void Node::move_right(int z_location) {
	int temp = board[z_location + 1];
	board[z_location + 1] = 0;
	board[z_location] = temp;
	this->heuristic_val = heuristic_cal(board, 9);
}
void Node::move_up(int z_location) {
	int temp = board[z_location - 3];
	board[z_location - 3] = 0;
	board[z_location] = temp;
	this->heuristic_val = heuristic_cal(board, 9);
}
void Node::move_left(int z_location) {
	int temp = board[z_location - 1];
	board[z_location - 1] = 0;
	board[z_location] = temp;
	this->heuristic_val = heuristic_cal(board, 9);
}
void Node::move_down(int z_location) {
	int temp = board[z_location + 3];
	board[z_location + 3] = 0;
	board[z_location] = temp;
	this->heuristic_val = heuristic_cal(board, 9);
}

void Node::print_board() {
	for (int i = 0; i < 9; i++)
		std::cout << board[i] << " ";
}

bool Node::operator==(Node& n) {
	for (int i = 0; i < 9; i++) {
		if (this->board[i] != n.get_board()[i])
			return false;
	}
	return true;
}

bool Node::operator!=(Node& n) {
	return !operator==(n);
}

#endif // !NODE
