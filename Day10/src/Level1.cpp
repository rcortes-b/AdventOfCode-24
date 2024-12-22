#include "../../utils.hpp"

#define LINE_AMOUNT 45
int_vec	visited_pos;
auto	trailhead_scores = 0;

enum direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	DEFAULT
}	dir;

static bool	is_offlimit(int y, int x, int line_size)
{
	if (y < 0 || y >= LINE_AMOUNT || x < 0 || x >= line_size)
		return true;
	return false;
}

static void	get_trailhead_level(std::string map[], int y, int x, int old_heigth, unsigned int direction)
{
	if (is_offlimit(y, x, map[0].size()))
		return ;
	else if (((map[y][x] - '0') - 1) != old_heigth)
		return ;
	else {
		if (map[y][x] == '9' && old_heigth == 8) {
			if (!visited_pos.empty() && std::find(visited_pos.begin(), visited_pos.end(), (y * 10) + x) != visited_pos.end())
				return ;
			visited_pos.push_back(y * 10 + x);
			trailhead_scores += 1;
			return ;
		}
		//if (direction != UP)
			get_trailhead_level(map, y + 1, x, old_heigth + 1, DOWN);
		//if (direction != DOWN)
			get_trailhead_level(map, y - 1, x, old_heigth + 1, UP);
		//if (direction != LEFT)
			get_trailhead_level(map, y, x + 1, old_heigth + 1, RIGHT);
		//if (direction != RIGHT)
			get_trailhead_level(map, y, x - 1, old_heigth + 1, LEFT);
	}
}

static void	explore_map(std::string map[])
{
	auto	trailheads = 0;
	for (auto y = 0; y < LINE_AMOUNT; y++) {
		for (auto x = 0; x < map[y].size(); x++) {
			if (map[y][x] == '0') {
				get_trailhead_level(map, y, x, -1, DEFAULT);
				if (!visited_pos.empty())
					visited_pos.clear();
			}
		}
	}
}

int main(int argc, char **argv)
{
	try {
		if (argc == 1)
			throw ThrowError("Not input provided");
		else if (argc > 2)
			throw ThrowError("You can provide only one input");
		std::fstream	f;
		f.open(argv[1]);
		if (!f)
			throw ThrowError("Failed accessing the input");

		std::string	map[LINE_AMOUNT];
		auto		counter = 0;
		while (std::getline(f, map[counter]))
			counter++;
		explore_map(map);
		std::cout << "The sum of the scores of all trailheads is " << trailhead_scores << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}