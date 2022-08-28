module;

#include <boost/dynamic_bitset.hpp>

export module game_of_life;

// represents two dimensional array as a one dimensional array

export class game_of_life
{
public:
	game_of_life(int r, int c) : row{ r }, column{ c }
	{
		cells.resize(r * c);
		next_step_cells.resize(r * c);
	}
	bool at(int i, int j) { return cells[i * column + j]; }
	void set(int i, int j) { cells.set(i * column + j); }
	void flip(int i, int j) { cells.flip(i * column + j); }
	void set_next_step_cells(int i, int j) { next_step_cells.set(i * column + j); }
	void reset_next_step_cells(int i, int j) { next_step_cells.reset(i * column + j); }
	int check_neighbors(int i, int j);
	void next_state();
	void print();
	int get_row() { return row; }
	int get_column() { return column; }
	void random();
private:
	boost::dynamic_bitset<> cells;
	boost::dynamic_bitset<> next_step_cells;
	int row{};
	int column{};
};