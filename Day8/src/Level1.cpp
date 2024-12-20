#include "../../utils.hpp"

#define	LINE_AMOUNT 50
auto	total_locations = 0;

static bool	is_offlimit(int y, int x, int map_size)
{
	if (y < 0 || y >= LINE_AMOUNT || x < 0 || x >= map_size)
		return true;
	return false;
}

static void	same_row(std::string antinode_map[], int y, int x1, int x2)
{
	if (!is_offlimit(y, x2 - x1, antinode_map[y].size()))
		antinode_map[y][x2 - x1] = '#';
	if (!is_offlimit(y, x1 + x2, antinode_map[y].size()))
		antinode_map[y][x2 + x1] = '#';
}

static void	same_column(std::string antinode_map[], int x, int y1, int y2)
{
	if (!is_offlimit(y2 - y1, x, antinode_map[y1].size()))
		antinode_map[y2 - y1][x] = '#';
	if (!is_offlimit(y1 + y2, x, antinode_map[y1].size()))
		antinode_map[y1 + y2][x] = '#';
}

static void	diagonal_right(std::string antinode_map[], int y, int y2, int x, int x2)
{
	if (!is_offlimit(y - (y2 - y), x - (x2 - x), antinode_map[y].size()))
		antinode_map[y - (y2 - y)][x - (x2 - x)] = '#';
	if (!is_offlimit(y2 + (y2 - y), x2 + (x2 - x), antinode_map[y].size()))
		antinode_map[y2 + (y2 - y)][x2 + (x2 - x)] = '#';
}

static void	diagonal_left(std::string antinode_map[], int y, int y2, int x, int x2)
{
	if (!(is_offlimit(y - (y2 - y), x + (x - x2), antinode_map[y].size())))
		antinode_map[y - (y2 - y)][x + (x - x2)] = '#';
	if (!is_offlimit(y2 + (y2 - y), x2 - (x - x2), antinode_map[y].size()))
		antinode_map[y2 + (y2 - y)][x2 - (x - x2)] = '#';
}

static void	create_antinodes(std::string map[], std::string antinode_map[])
{
	for (unsigned int y = 0; y < LINE_AMOUNT; y++) {
		for (unsigned int x = 0; x < map[y].size(); x++) {
			if (map[y][x] != '.') {
				for (unsigned int y2 = y; y2 < LINE_AMOUNT; y2++) {
					for (unsigned int x2 = 0; x2 < map[y2].size(); x2++) {
						if (y == y2 && !x2)
							x2 = x + 1;
						if (map[y2][x2] == map[y][x]) {
							if (y == y2)
								same_row(antinode_map, y, x, x2);
							else if (x == x2)
								same_column(antinode_map, x, y, y2);
							else if(x < x2)
								diagonal_right(antinode_map, y, y2, x, x2);
							else
								diagonal_left(antinode_map, y, y2, x, x2);
						}
					}
				}
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

		std::string			line = "";
		std::string			map[LINE_AMOUNT];
		std::string			antinode_map[LINE_AMOUNT];
		unsigned int	counter = 0;
		while (std::getline(f, line))
		{
			map[counter] = line;
			antinode_map[counter] = std::string(line.size(), '.');
			counter++;
		}
		for (int i = 0; i < LINE_AMOUNT; i++) {
			std::cout << map[i] << std::endl;
		}
		std::cout << "\n\n\n\n\n";
		for (int i = 0; i < LINE_AMOUNT; i++) {
			std::cout << antinode_map[i] << std::endl;
		}
		std::cout << "\n\n\n\n\n";
		create_antinodes(map, antinode_map);
		for (int i = 0; i < LINE_AMOUNT; i++) {
			for (int j = 0; j < antinode_map[i].size(); j++) {
				if (antinode_map[i][j] == '#')
					total_locations++;
				std::cout << antinode_map[i][j];
			}
			std::cout << "\n";
		}
		std::cout << "The total amount of unique locations is: " << total_locations << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}