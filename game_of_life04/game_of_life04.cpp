// Game of life
// August 22, 2022
// by SM

// Any live cell with fewer than two live neighbours dies, as if by underpopulation.
// Any live cell with two or three live neighbours lives on to the next generation.
// Any live cell with more than three live neighbours dies, as if by overpopulation.
// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
//
// These rules, which compare the behavior of the automaton to real life, can be condensed into the following :
//
// Any live cell with two or three live neighbours survives.
// Any dead cell with three live neighbours becomes a live cell.
// All other live cells die in the next generation.Similarly, all other dead cells stay dead.

// boundary condition
// Cellular automata often use a toroidal topology of the simulation domain.This means that
// opposing edges of the grid are connected.The rightmost column is the neighbor of the leftmost
// columnand the topmost row is the neighbor of the bottommost rowand vice versa.This allows
// the unrestricted transfer of state information across the boundaries.



import <iostream>;
import <vector>;
import <random>;
#include <SFML/Graphics.hpp>
import game_of_life;

// use sf::RectangleShape for cells

// P or Space: Pause or resume execution
// R: randomize cells (in pause mode)
// Up arrow: increase the speed
// Down arrow: decrease the speed
// click the cell to filp (in pause mode)

int main()
{

	/*game_of_life game{ 4, 5 };
	game.set(1, 0);
	game.set(1, 1);
	game.set(1, 2);*/

	/*game_of_life game{ 6, 6 };
	game.set(2, 2);
	game.set(2, 3);
	game.set(2, 4);
	game.set(3, 1);
	game.set(3, 2);
	game.set(3, 3);*/

	game_of_life game{ 50, 100 }; // row, column
	game.set(10, 10);
	game.set(11, 11);
	game.set(11, 12);
	game.set(12, 10);
	game.set(12, 11);

	game.set(20, 31);
	game.set(20, 32);
	game.set(20, 33);
	game.set(20, 34);
	game.set(21, 30);
	game.set(21, 34);
	game.set(22, 34);
	game.set(23, 30);
	game.set(23, 33);


	//game.print();
	//std::cout << std::endl;

	//for (int i{}; i < 4; ++i)
	//{
	//	game.next_state();
	//	game.print();
	//	std::cout << std::endl;
	//}

	int sleep_time{ 100 };
	const int size_of_cell{ 10 };
	bool pause{ false };
	//sf::VertexArray grid{ sf::Points };
	std::vector<sf::RectangleShape> grid{};
	sf::RenderWindow window(sf::VideoMode(game.get_column() * size_of_cell, game.get_row() * size_of_cell), "Game of Life", sf::Style::Titlebar | sf::Style::Close);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Space)
				{
					pause = !pause;
				}
				else if (pause && event.key.code == sf::Keyboard::R)
				{
					game.random();
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					sleep_time -= 5; if (sleep_time <= 5) sleep_time = 15;
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					sleep_time += 5; if (sleep_time > 200) sleep_time = 200;
				}

			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (pause && event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i pos{ sf::Mouse::getPosition(window) };
					//std::cout << pos.x << ' ' << pos.y << std::endl;
					if (pos.x >= 0 && pos.x < game.get_column() * size_of_cell && pos.y >= 0 && pos.y < game.get_row() * size_of_cell)
					{
						int i{ pos.y / size_of_cell }, j{ pos.x / size_of_cell };
						game.flip(i, j);
					}
				}
			}
		}

		window.clear();


		grid.clear();
		for (int i{}; i < game.get_row(); ++i)
			for (int j{}; j < game.get_column(); ++j)
			{
				if (game.at(i, j))
				{
					grid.push_back(sf::RectangleShape{ sf::Vector2f{size_of_cell, size_of_cell } });
					grid.back().setPosition(static_cast<float>(j * size_of_cell), static_cast<float>(i * size_of_cell)); // j: x coord, i: y coord
					grid.back().setFillColor(sf::Color::Yellow);
				}
			}

		for (const auto& x : grid)
			window.draw(x);

		window.display();

		if (!pause) // pause or resume update
			game.next_state();


		sf::sleep(sf::milliseconds(sleep_time));
		if (!window.isOpen())
			std::cout << "window is closed\n";
	}
	std::cout << "See you!\n";
}