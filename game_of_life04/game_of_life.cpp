module game_of_life;

import <iostream>;
import <random>;

int game_of_life::check_neighbors(int i, int j)
{
	int count{};
	int r{}, c{}; // row and column, respectively

	for (int a{ -1 }; a < 2; ++a)
	{
		r = i + a;

		// wrap around the boundary
		if (r < 0) r = row - 1;
		if (r >= row) r = 0;

		for (int b{ -1 }; b < 2; ++b)
		{
			if (count == 4) return count;

			if (a == 0 && b == 0) continue; // skip for oneself

			c = j + b;

			// wrap around the boundary
			if (c < 0) c = column - 1;
			if (c >= column) c = 0;

			if (at(r, c)) ++count;
		}
	}

	return count;
}


void game_of_life::next_state()
{
	int count{};

	for (int i{}; i < row; ++i)
		for (int j{}; j < column; ++j)
		{
			count = check_neighbors(i, j);

			if (at(i, j) && (count == 2 || count == 3))
				set_next_step_cells(i, j); // Any live cell with two or three live neighbours survives.
			else if (!at(i, j) && count == 3)
				set_next_step_cells(i, j); // Any dead cell with three live neighbours becomes a live cell.
			else
				reset_next_step_cells(i, j); // All other live cells die in the next generation.Similarly, all other dead cells stay dead.
		}

	cells = next_step_cells; // update
}

void game_of_life::print()
{
	int last{ row * column - 1 };
	for (int i{}; i <= last; ++i)
	{
		std::cout << cells[i];
		if ((i + 1) % column == 0)
			std::cout << std::endl;
	}
}

void game_of_life::random()
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(0, 2);
	int end{ row * column };
	for (int i{}; i < end; ++i)
		cells.set(i, distrib(gen));
}