#include "../../utils.hpp"

#define 	LINE_AMOUNT 140
int			total = 0;
std::string	word = "XMAS";

static void	parse_input(std::string lines[], char *file)
{
	std::fstream	f;
	f.open(file);
	if (!f)
		throw ThrowError("Failed accessing the input");

	unsigned int counter = 0;
	while (std::getline(f, lines[counter]))
		counter++;
}

static bool	is_xmas(std::string lines[], int y, int x)
{
	if (!x || x == lines[y].size() - 1 || !y || y == LINE_AMOUNT - 1)
		return false;

	bool	f_diagonal = false;

	if ((lines[y - 1][x - 1] == 'M' && lines[y + 1][x + 1] == 'S')
		|| (lines[y - 1][x - 1] == 'S' && lines[y + 1][x + 1] == 'M'))
		f_diagonal = true;
	if (f_diagonal && ((lines[y - 1][x + 1] == 'M' && lines[y + 1][x - 1] == 'S')
		|| (lines[y - 1][x + 1] == 'S' && lines[y + 1][x - 1] == 'M')))
		return true;
	return false;
}

int main(int argc, char **argv)
{
	try {

		if (argc == 1)
			throw ThrowError("Not input provided");
		else if (argc > 2)
			throw ThrowError("You can provide only one input");
		
		std::string	lines[LINE_AMOUNT];
		parse_input(lines, argv[1]);
		for (int y = 0; y < LINE_AMOUNT; y++) {
			for (int x = 0; x < lines[y].size(); x++) {
				if (lines[y][x] == 'A')
					if (is_xmas(lines, y, x))
						total++;
			}
		}
		std::cout << "The total amount of XMAS occurrences is " << total << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}