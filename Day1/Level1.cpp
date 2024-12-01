#include "../utils.hpp"

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

static void	sort_numbers(int_vec &v1, int_vec &v2, int_vec &s_v1, int_vec &s_v2)
{
	it_intvec	it;
	it_intvec	it_lowest;
	while (!v1.empty())
	{
		it_lowest = v1.begin();
		for (it = v1.begin() + 1; it != v1.end(); it++) {
			if (*it < *it_lowest)
				it_lowest = it;
		}
		s_v1.push_back(*it_lowest);
		v1.erase(it_lowest);
	}
	while(!v2.empty())
	{
		it_lowest = v2.begin();
		for (it = v2.begin() + 1; it != v2.end(); it++) {
			if (*it < *it_lowest)
				it_lowest = it;
		}
		s_v2.push_back(*it_lowest);
		v2.erase(it_lowest);
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

		int_vec	s_vec1;
		int_vec	s_vec2;

		sort_numbers(vec1, vec2, s_vec1, s_vec2);

		unsigned int	list_size = s_vec1.size();
		int				total = 0;
		int				tmp = 0;
		it_intvec	it2 = s_vec2.begin();
		for (it_intvec	it1 = s_vec1.begin(); it1 != s_vec1.end(); it1++) {
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
