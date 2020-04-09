#ifndef NODE
#define NODE

class Node {

private:
	int board[9];
	int heuristic_val;
	int path_cost;
	Node *parent_node;
	Node *children_nodes[4];
	int(*heuristic_cal)(int[], int);
	//one node can have at most 4 children

	void move_right(int z_location);
	void move_up(int z_location);
	void move_left(int z_location);
	void move_down(int z_location);
	
public:
	int get_path_cost();
	int get_h_val();
	int* get_board();
	Node* get_parent_node();
	Node** get_children_nodes();
	int expand();
	int get_total_cost();
	void set_parent_node(Node*);
	void print_board();
	bool operator==(Node& n);
	bool operator!=(Node& n);

	Node(int b[9], int (*heuristic_calc)(int[], int), int);
	~Node();

};


#endif // !NODE
