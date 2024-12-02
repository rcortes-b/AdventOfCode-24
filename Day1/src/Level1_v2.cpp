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

		std::sort(vec1.begin(), vec1.end());
		std::sort(vec2.begin(), vec2.end());

		int				total = 0;
		int				tmp = 0;
		it_intvec	it2 = vec2.begin();
		for (it_intvec	it1 = vec1.begin(); it1 != vec1.end(); it1++) {
			tmp = *it1 - *it2;
			if (tmp < 0)
				tmp *= -1;
			total += tmp;
			it2++;
		}
		std::cout << "The total distance is " << total << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
