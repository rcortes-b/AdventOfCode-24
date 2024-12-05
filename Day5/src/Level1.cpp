#include "../../utils.hpp"

unsigned long int	total = 0;

static void	parse_ordering_rules(int_vec &rule1, int_vec &rule2, std::fstream &f)
{
	std::string line;
	while (std::getline(f, line))
	{
		unsigned int i = 0;
		if (!i && line[i] == '\0')
			return ;
		rule1.push_back(std::atoi(&line[i]));
		i = line.find('|') + 1;
		rule2.push_back(std::atoi(&line[i]));		
	}
}

static void	parse_update(int_vec &update, std::string &line)
{
	update.push_back(std::atoi(&line[0]));
	for (unsigned int i = 0; i < line.size(); i++) {
		if (line[i] == ',') {
			i += 1;
			update.push_back(std::atoi(&line[i]));
		}
	}
	
}

static int	check_update_order(int_vec &rule1, int_vec &rule2, int_vec &update, std::string &line)
{

	for (it_intvec it = update.end() - 1; it != update.begin(); it--) {
		for (it_intvec it_r2 = rule2.begin(), it_r1 = rule1.begin(); it_r2 != rule2.end(); it_r1++, it_r2++) {
			if (*it == *it_r1)
			{
				for (it_intvec it2 = update.begin(); it2 != it; it2++) {
					if (*it2 == *it_r2)
						return 0;
				}
			}
		}
	}
	return (*(update.begin() + (update.size() / 2)));
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

		int_vec	rule1;
		int_vec	rule2;
		parse_ordering_rules(rule1, rule2, f);
		std::string line;
		int_vec		update;
		while (std::getline(f, line))
		{
			parse_update(update, line);
			total += check_update_order(rule1, rule2, update, line);
			if (!update.empty())
				update.clear();
		}
		std::cout << "The total total number of the middle ordered pages is " << total << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}