#ifndef TREE_SEARCH
#define TREE_SEARCH

#include "Node.h"


class TreeSearch {
protected:
	int (*heuristic_cal)(int[], int);
	int nodes_generated;
	int depth;
	struct pQueue {
		Node* node;
		pQueue* next;
	};
	
	pQueue *frontier;
public:
	bool expand_frontier();
	TreeSearch(int initial_board[9], int(*heuristic_calc)(int[], int));
	~TreeSearch();
	int get_depth();
	int get_nodes_generated();
};

#endif // !TREE_SEARCH

