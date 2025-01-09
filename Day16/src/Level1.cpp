#include "../../utils.hpp"

#define MAP_SIZE 141

//static std::vector<std::pair<int, int>>	visited;
static std::string	map[MAP_SIZE];
static int_vec		scores;

enum	e_direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

static void	parse_data(std::pair<int, int> &start)
{
	std::ifstream	f("../input");
	std::string		line = "";
	auto			counter = 0;
	auto			index = 0;
	while (std::getline(f, line))
	{
		map[counter] = line;
		if ((index = line.find('S')) != std::string::npos) {
			start.first = counter;
			start.second = index;
		}
		counter++;
	}
}

static bool	is_visited(int y, int x, std::vector<std::pair<int, int>> visited)
{

	if (visited.empty())
		return false;
	for (auto &a: visited)
		if (a.first == y && a.second == x)
			return true;
	return false;
}

static void	maze_runner(int y, int x, int amount, e_direction dir, std::vector<std::pair<int, int>>	visited)
{
	if (map[y][x] == 'E') {
		std::cout << amount << std::endl;
		scores.push_back(amount);
		return ;
	}
	std::pair<int, int>	p = {y, x};
	visited.push_back(p);
	if (dir == NORTH)
	{
		if (map[y - 1][x] != '#' && !is_visited(y - 1, x, visited))
			maze_runner(y - 1, x, amount + 1, NORTH, visited);
		if (map[y][x - 1] != '#' && !is_visited(y, x - 1, visited))
			maze_runner(y, x - 1, amount + 1001, WEST, visited);
		if (map[y][x + 1] != '#' && !is_visited(y, x + 1, visited))
			maze_runner(y, x + 1, amount + 1001, EAST, visited);
	}
	else if (dir == SOUTH)
	{
		if (map[y + 1][x] != '#' && !is_visited(y + 1, x, visited))
			maze_runner(y + 1, x, amount + 1, SOUTH, visited);
		if (map[y][x - 1] != '#' && !is_visited(y, x - 1, visited))
			maze_runner(y, x - 1, amount + 1001, WEST, visited);
		if (map[y][x + 1] != '#' && !is_visited(y, x + 1, visited))
			maze_runner(y, x + 1, amount + 1001, EAST, visited);
	}
	else if (dir == EAST)
	{
		if (map[y][x + 1] != '#' && !is_visited(y, x + 1, visited))
			maze_runner(y, x + 1, amount + 1, EAST, visited);
		if (map[y - 1][x] != '#' && !is_visited(y - 1, x, visited))
			maze_runner(y - 1, x, amount + 1001, NORTH, visited);
		if (map[y + 1][x] != '#' && !is_visited(y + 1, x, visited))
			maze_runner(y + 1, x, amount + 1001, SOUTH, visited);
	}
	else
	{
		if (map[y][x - 1] != '#' && !is_visited(y, x - 1, visited))
			maze_runner(y, x - 1, amount + 1, WEST, visited);
		if (map[y - 1][x] != '#' && !is_visited(y - 1, x, visited))
			maze_runner(y - 1, x, amount + 1001, NORTH, visited);
		if (map[y + 1][x] != '#' && !is_visited(y + 1, x, visited))
			maze_runner(y + 1, x, amount + 1001, SOUTH, visited);
	}
	//visited.pop_back();
}

int main(void)
{
	try {
		std::pair<int, int>	start;
		parse_data(start);
		std::vector<std::pair<int, int>>	visited;
		maze_runner(start.first, start.second, 0, EAST, visited);

		auto	l_Score = *scores.begin();
		for (auto &a : scores) {
			if (l_Score > a)
				l_Score = a;
		}
		std::cout << "The lowest score is " << l_Score << std::endl;		
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}