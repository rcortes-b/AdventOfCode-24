#include "../../utils.hpp"

typedef struct	s_map {
	std::string	map[130];
	int	x = 0;
	int	y = 0;
	int	dir = 0;
}				t_map;

enum	e_direction {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT 
};

#define 	LINE_COUNTER 130
int			steps = 1;
t_map		d_map;

static void	visit_positions(void)
{
	d_map.map[d_map.y][d_map.x] = 'X';
	while (1)
	{
		if (d_map.map[d_map.y][d_map.x] == '.') {
			d_map.map[d_map.y][d_map.x] = 'X';
			steps++;
		}
		if (d_map.dir == UP) {
			if (!d_map.y)
				return ;
			else if (d_map.map[d_map.y - 1][d_map.x] == '#')
				d_map.dir = RIGHT;
			else
				d_map.y--;
		}
		else if (d_map.dir == RIGHT) {
			if (d_map.x == d_map.map[d_map.y].size() - 1)
				return ;
			else if (d_map.map[d_map.y][d_map.x + 1] == '#')
				d_map.dir = DOWN;
			else
				d_map.x++;
		}
		else if (d_map.dir == DOWN) {
			if (d_map.y == LINE_COUNTER - 1)
				return ;
			else if (d_map.map[d_map.y + 1][d_map.x] == '#')
				d_map.dir = LEFT;
			else
				d_map.y++;
		}
		else {
			if (!d_map.x)
				return ;
			else if (d_map.map[d_map.y][d_map.x - 1] == '#')
				d_map.dir = UP;
			else
				d_map.x--;
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
		unsigned int	counter = 0;
		while (std::getline(f, d_map.map[counter]))
		{
			if (d_map.map[counter].find('^') != std::string::npos) {
				d_map.y = counter;
				d_map.x = d_map.map[counter].find('^');
			}
			counter++;
		}
		visit_positions();
		std::cout << "The total amount of visited positions is: " << steps << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}