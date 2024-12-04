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

static int do_horizontal(std::string &line, int x)
{
	int	occurrences = 0;
	int	save_pos = x;
	if (save_pos >= 3) {
		for (int i = 0; i <= 3; i++) {
			if (word[i] != line[save_pos--])
				break ;
			else if (i == 3)
				occurrences++;
		}
	}
	if (line.size() - 4 < x)
		return occurrences;
	for (int i = 0; i <= 3; i++){
		if (word[i] != line[x++])
				break ;
		else if (i == 3)
			occurrences++;
	}
	return occurrences;
}

static int do_vertical(std::string line[], int y, int x)
{
	int	occurrences = 0;
	int	save_pos = y;
	if (save_pos >= 3) {
		for (int i = 0; i <= 3; i++) {
			if (word[i] != line[save_pos--][x])
				break ;
			else if (i == 3)
				occurrences++;
		}
	}
	if (LINE_AMOUNT - 4 < y)
		return occurrences;
	for (int i = 0; i <= 3; i++){
		if (word[i] != line[y++][x])
				break ;
		else if (i == 3)
			occurrences++;
	}
	return occurrences;
}


static int do_diagonal_left(std::string line[], int y, int x)
{
	int	occurrences = 0;
	if (x < 3)
		return occurrences;

	int	save_y = y;
	int	save_x = x;

	if (y >= 3) {
		for (int i = 0; i <= 3; i++) {
			if (word[i] != line[y--][x--])
				break ;
			else if (i == 3)
				occurrences++;
		}
	}
	if (LINE_AMOUNT - 4 < save_y)
		return occurrences;
	for (int i = 0; i <= 3; i++) {
		if (word[i] != line[save_y++][save_x--])
			break ;
		else if (i == 3)
			occurrences++;
	}
	return occurrences;
}

static int do_diagonal_right(std::string line[], int y, int x)
{
	int	occurrences = 0;
	if (line[y].size() - 4 < x)
		return occurrences;

	int	save_y = y;
	int	save_x = x;

	if (y >= 3) {
		for (int i = 0; i <= 3; i++) {
			if (word[i] != line[y--][x++])
				break ;
			else if (i == 3)
				occurrences++;
		}
	}
	if (LINE_AMOUNT - 4 < save_y)
		return occurrences;
	for (int i = 0; i <= 3; i++) {
		if (word[i] != line[save_y++][save_x++])
			break ;
		else if (i == 3)
			occurrences++;
	}
	return occurrences;
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
				if (lines[y][x] == 'X')
				{
					total += do_horizontal(lines[y], x);
					total += do_vertical(lines, y, x);
					total += do_diagonal_left(lines, y, x);
					total += do_diagonal_right(lines, y, x);
				}
			}
		}
		std::cout << "The total amount of XMAS occurrences is " << total << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}