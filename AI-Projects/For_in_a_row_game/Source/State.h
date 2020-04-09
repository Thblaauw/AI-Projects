#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>

class State {

private:
	std::string board[8];
	//std::vector<state_handle> next_moves;
	const State *parent_state;
public:
	State();
	State(const State* s);
	~State();
	State(std::string b[8]);
	const std::string* get_board() const;
	bool make_move(std::string move, char player);
	std::vector<State*>* branch(char player);
	bool check_win();
	bool undo(std::string move);
};
#endif // !STATE_H
