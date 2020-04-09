#ifndef GRAPH_SEARCH_CPP
#define GRAPH_SEARCH_CPP

#include "GraphSearch.h"
#include <iostream>

GraphSearch::GraphSearch(int initial_board[9], int(*heuristic_calc)(int[], int)) {
	this->explored_set = new Set();
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

GraphSearch::~GraphSearch() {
	while (frontier != nullptr) {
		pQueue *iterator = frontier;
		frontier = frontier->next;
		delete iterator->node;
		delete iterator;
	}

	/*while (explored_set != nullptr) {
		Set *iterator = explored_set;
		explored_set = explored_set->next;
		delete iterator->node;
		delete iterator;
	}*/
}

bool GraphSearch::is_in_explored_set(Node *n) {
	Set *iterator = explored_set;

	if (iterator == nullptr || iterator->node == nullptr)
		return false;//explored

	else {
		while (iterator != nullptr && iterator->node != nullptr && *(iterator->node) != *n) {
			iterator = iterator->next;
		}
		if (iterator != nullptr && iterator->node != nullptr)//has not reached the end
			return true;
		else
			return false;//has reached the end
	}
	
}

bool GraphSearch::add_to_explored_set(Node *n) {
	//this method add to the front of the set, in no particular order
	Set *s = new Set();
	s->node = n;
	s->next = explored_set;
	explored_set = s;
	return true;
}

bool GraphSearch::expand_frontier() {
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
	else {
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
		//if the children node is not already in the explored set, then it will add to the pQueue
		if (!is_in_explored_set(children_nodes[i])) {
			pQueue *newNode = new pQueue();
			newNode->node = children_nodes[i];
			pQueue *iterator = frontier;

			add_to_explored_set(children_nodes[i]);

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

		}
		else {//this will delete the nodes that have already been expanded and would be added again
			delete children_nodes[i];
			children_nodes[i] = nullptr;
			nodes_generated--;
		}

		i++;
	}

	return false;
}

int GraphSearch::get_nodes_generated() {
	return nodes_generated;
}

int GraphSearch::get_depth() {
	return this->depth;
}
#endif
