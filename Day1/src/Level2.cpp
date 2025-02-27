#include "../../utils.hpp"

static void	parse_file(int_vec &v1, int_vec &v2, char *file)
{
	std::fstream	f;
	f.open(file);
	if (!f)
		throw ThrowError("Failed accessing to the file");
	
	std::string	line;
	while (std::getline(f, line))
	{
		bool	trigger = false;
		for (unsigned int i = 0; i < line.size(); i++) {
			if (std::isdigit(line[i])) {
				if (!trigger)
					v1.push_back(std::atoi(&line[i]));
				else
					v2.push_back(std::atoi(&line[i]));
				trigger = true;
				while (i < line.size() && !std::isspace(line[i]))
					i++;
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

		int_vec vec1;
		int_vec vec2;

		parse_file(vec1, vec2, argv[1]);

		int total = 0;
		for (it_intvec it = vec1.begin(); it != vec1.end(); it++) {
			int counter = 0;
			for (it_intvec it2 = vec2.begin(); it2 != vec2.end(); it2++) {
				if (*it == *it2)
					counter++;
			}
			total += (*it * counter);
		}
		std::cout << "The similarity input is " << total << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
