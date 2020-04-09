#ifndef TREE_SEARCH_CPP
#define TREE_SEARCH_CPP

#include "TreeSearch.h"
#include <iostream>

TreeSearch::TreeSearch(int initial_board[9], int(*heuristic_calc)(int[], int)) {
	heuristic_cal = heuristic_calc;
	nodes_generated = 0;
	//starts the queue
	frontier = new pQueue();
	frontier->node = new Node(initial_board, heuristic_cal, -1);
	//-1 here will initialize the node as having 0 path cost
	frontier->next = nullptr;
	
	bool isDone = false;
	while (!isDone) {
		isDone = this->expand_frontier();
	}
	depth = frontier->node->get_total_cost();
	std::cout << "Depth: " << frontier->node->get_total_cost() << std::endl
		<< "Number of Nodes: " << nodes_generated << std::endl;
}

TreeSearch::~TreeSearch() {
	while (frontier != nullptr) {
		pQueue *iterator = frontier;
		frontier = frontier->next;
		delete iterator->node;
		delete iterator;
	}
}

bool TreeSearch::expand_frontier() {
	if (frontier->node->get_h_val() == 0) {
		std::cout << "Solution found: " << std::endl;
		Node *n = frontier->node;
		while (n != nullptr) {
			n->print_board();
			std::cout << std::endl;
			n = n->get_parent_node();
		}
		
		return true;
		//solution found
	}

	Node* node_to_expand = frontier->node;

	//pops the pQueue
	if (frontier->next != nullptr) {
		frontier = frontier->next;

	}
	else{
		frontier->node = nullptr;
		frontier->next = nullptr;

	}
	//expands the frontier
	nodes_generated += node_to_expand->expand();
	if (nodes_generated > 60000)
		return true;
	Node** children_nodes = node_to_expand->get_children_nodes();

	//adds the children nodes to the frontier

	int i = 0;
	while (children_nodes[i] != nullptr && i < 4) {
		pQueue *newNode = new pQueue();
		newNode->node = children_nodes[i];
		pQueue *iterator = frontier;
		
		if (frontier->node == nullptr) {
			frontier = newNode;
		}
		else if (newNode->node->get_total_cost() < iterator->node->get_total_cost()) {
			newNode->next = iterator;
			frontier = newNode;
		}
		else {
			while (iterator->next != nullptr && newNode->node->get_total_cost() > iterator->node->get_total_cost()) {
				iterator = iterator->next;
			}
			newNode->next = iterator->next;
			iterator->next = newNode;
		}
		
		i++;
	}

	return false;
}

int TreeSearch::get_depth() {
	return depth;
}

int TreeSearch::get_nodes_generated() {
	return this->nodes_generated;
}


#endif // !TREE_SEARCH_CPP
