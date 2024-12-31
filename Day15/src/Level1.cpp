#include "../../utils.hpp"

#define MAP_SIZE 50

typedef struct	s_lfish {
	std::string					map[MAP_SIZE];
	std::vector<std::string>	steps;
	int	y;
	int	x;
}				t_lfish;

static void	print_map(t_lfish &lfish)
{
	for (auto y = 0; y < MAP_SIZE; y++) {
		for (auto x = 0; x < lfish.map[y].size(); x++) {
			std::cout << lfish.map[y][x] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "\n\n\n";
}

static void	parse_data(t_lfish &lfish, char *file)
{
	std::fstream	f;
	f.open(file);
	if (!f)
		throw ThrowError("Failed accessing the input");
	std::string	line = "";
	bool		is_steps = false;
	auto		counter = 0;
	while (std::getline(f, line)) {
		if (line.empty()) {
			is_steps = true;
			continue ;
		}
		if (is_steps)
			lfish.steps.push_back(line);
		else {
			if (line.find('@', 0) != std::string::npos) {
				lfish.y = counter;
				lfish.x = line.find('@', 0);
			}
			lfish.map[counter++] = line;
		}
	}
}

static void	do_up(t_lfish &lfish)
{
	if (lfish.map[lfish.y - 1][lfish.x] == '#')
		return ;
	else if (lfish.map[lfish.y - 1][lfish.x] == '.') {
		lfish.map[lfish.y][lfish.x] = '.';
		lfish.y--;
		lfish.map[lfish.y][lfish.x] = '@';
	}
	else {
		auto rocks = 0;
		while (lfish.map[lfish.y - rocks - 1][lfish.x] == 'O')
			rocks++;
		if (lfish.map[lfish.y - rocks - 1][lfish.x] == '.') {
			lfish.map[lfish.y - rocks - 1][lfish.x] = 'O';
			lfish.map[lfish.y][lfish.x] = '.';
			lfish.y--;
			lfish.map[lfish.y][lfish.x] = '@';
		}
	}
}

static void	do_down(t_lfish &lfish)
{
	if (lfish.map[lfish.y + 1][lfish.x] == '#')
		return ;
	else if (lfish.map[lfish.y + 1][lfish.x] == '.') {
		lfish.map[lfish.y][lfish.x] = '.';
		lfish.y++;
		lfish.map[lfish.y][lfish.x] = '@';
	}
	else {
		auto rocks = 0;
		while (lfish.map[lfish.y + rocks + 1][lfish.x] == 'O')
			rocks++;
		if (lfish.map[lfish.y + rocks + 1][lfish.x] == '.') {
			lfish.map[lfish.y + rocks + 1][lfish.x] = 'O';
			lfish.map[lfish.y][lfish.x] = '.';
			lfish.y++;
			lfish.map[lfish.y][lfish.x] = '@';
		}
	}
}

static void	do_left(t_lfish &lfish)
{
	if (lfish.map[lfish.y][lfish.x - 1] == '#')
		return ;
	else if (lfish.map[lfish.y][lfish.x - 1] == '.') {
		lfish.map[lfish.y][lfish.x] = '.';
		lfish.x--;
		lfish.map[lfish.y][lfish.x] = '@';
	}
	else {
		auto rocks = 0;
		while (lfish.map[lfish.y][lfish.x - rocks - 1] == 'O')
			rocks++;
		if (lfish.map[lfish.y][lfish.x - rocks - 1] == '.') {
			lfish.map[lfish.y][lfish.x - rocks - 1] = 'O';
			lfish.map[lfish.y][lfish.x] = '.';
			lfish.x--;
			lfish.map[lfish.y][lfish.x] = '@';
		}
	}
}

static void	do_right(t_lfish &lfish)
{
	if (lfish.map[lfish.y][lfish.x + 1] == '#')
		return ;
	else if (lfish.map[lfish.y][lfish.x + 1] == '.') {
		lfish.map[lfish.y][lfish.x] = '.';
		lfish.x++;
		lfish.map[lfish.y][lfish.x] = '@';
	}
	else {
		auto rocks = 0;
		while (lfish.map[lfish.y][lfish.x + rocks + 1] == 'O')
			rocks++;
		if (lfish.map[lfish.y][lfish.x + rocks + 1] == '.') {
			lfish.map[lfish.y][lfish.x + rocks + 1] = 'O';
			lfish.map[lfish.y][lfish.x] = '.';
			lfish.x++;
			lfish.map[lfish.y][lfish.x] = '@';
		}
	}
}

static void	do_movement(t_lfish &lfish, char c)
{
	switch (c)
	{
		case '<' :
					do_left(lfish);
					break ;
		case '^' :
					do_up(lfish);
					break ;
		case '>' :
					do_right(lfish);
					break ;
		case 'v' :
					do_down(lfish);
					break ;
	}
}

static auto	sum_coordinates(t_lfish &lfish)
{
	int	res = 0;

	for (auto y = 0; y < MAP_SIZE; y++) {
		for (auto x = 0; x < lfish.map[y].size(); x++) {
			if (lfish.map[y][x] == 'O')
				res += ((y * 100) + x);
		}
	}
	return res;
}

int main(int argc, char **argv)
{
	try {
		if (argc == 1)
			throw ThrowError("Not input provided");
		else if (argc > 2)
			throw ThrowError("You can provide only one input");
		t_lfish	lfish;
		parse_data(lfish, argv[1]);
		auto	i = 0;
		for (auto &a : lfish.steps) {
			i = -1;
			auto size = a.size();
			while (++i < size) {
				//print_map(lfish);
				do_movement(lfish, a[i]);
			}
			//print_map(lfish);
		}
		std::cout << "The sum of all boxes' GPS coordinates is " << sum_coordinates(lfish) << std::endl;		
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}