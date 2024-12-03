#include "../../utils.hpp"

unsigned long int	total = 0;

static int	check_sequency(std::string &line, unsigned int &iterator)
{
	int 			num = 0;
	unsigned int	num_pos = 0;
	if (iterator >= line.size())
		return 0;
	if (line[iterator] != '(')
		return 0;
	if (!std::isdigit(line[++iterator]))
		return 0;
	num_pos = iterator;
	while (iterator < line.size() && std::isdigit(line[iterator]))
		iterator++;
	if (iterator < line.size() && line[iterator] != ',')
		return 0;
	num = std::atoi(&line[num_pos]);
	if (!std::isdigit(line[++iterator]))
		return 0;
	num_pos = iterator;
	while (iterator < line.size() && std::isdigit(line[iterator]))
		iterator++;
	if (iterator < line.size() && line[iterator] == ')')
		return num * (std::atoi(&line[num_pos]));
	return 0;
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
		
		std::string line;
		while (std::getline(f, line))
		{
			for (unsigned int i = 0; i < line.size(); i++) {
				if (line.substr(i, 3) == "mul") {
					i += 3;
					total += check_sequency(line, i);
				}
			}
		}
		std::cout << "The total amount of safe reports is " << total << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}