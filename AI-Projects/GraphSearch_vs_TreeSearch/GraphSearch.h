#ifndef GRAPH_SEARCH
#define GRAPH_SEARCH

#include "TreeSearch.h"

class GraphSearch {
protected:
	struct Set {
		Node* node;
		Set* next;
	};
	int(*heuristic_cal)(int[], int);
	int nodes_generated;
	struct pQueue {
		Node* node;
		pQueue* next;
	};
	pQueue *frontier;
	Set * explored_set;
	bool is_in_explored_set(Node *n);
	bool add_to_explored_set(Node *n);
	int depth;

public:
	bool expand_frontier();
	GraphSearch(int initial_board[9], int(*heuristic_calc)(int[], int));
	~GraphSearch();
	int get_nodes_generated();
	int get_depth();
};

#endif
