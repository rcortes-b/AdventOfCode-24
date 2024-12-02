#include "../../utils.hpp"

int total = 0;

static void	parse_line(int_vec &vec, std::string &line, bool &is_increasing)
{
	if (!vec.empty())
		vec.clear();
	for (unsigned int i = 0; i < line.size(); i++) {
		if (std::isdigit(line[i])) {
			vec.push_back(std::atoi(&line[i]));
			while (i < line.size() && std::isdigit(line[i]))
				i++;
		}
	}

	int	total_increase = 0;
	int	total_decrease = 0;
	it_intvec	it = vec.begin() + 1;
	for (unsigned int i = 0; i < 3; i++) {	//three samples should be enough
		if (*it > *(it - 1))
			total_increase++;
		else if (*it < *(it - 1))
			total_decrease++;
		it++;
	}
	if (total_increase > total_decrease)
		is_increasing = true;
	
}

static bool	report_is_safe(int_vec &vec, bool is_increasing)
{
	it_intvec	it = vec.begin() + 1;
	bool		remove_level = false;
	if (is_increasing)
	{
		while (it != vec.end())
		{
			if (*it < *(it - 1)) {
				if (remove_level)
					return false;
				if (it == vec.begin() + 1)
					vec.erase(it - 1);
				else
					vec.erase(it - 1);
				remove_level = true;
				continue ;
			}
			int res = *it - *(it - 1);
			if (!res || res > 3) {
				if (remove_level)
					return false;
				if (it == vec.begin() + 1)
					vec.erase(it - 1);
				else {
					it--;
					vec.erase(it + 1);
				}
				remove_level = true;
				continue ;
			}
			it++;
		}
	}
	else {
		while (it != vec.end())
		{
			if (*it > *(it - 1)) {
				if (remove_level)
					return false;
				if (it == vec.begin() + 1)
					vec.erase(it - 1);
				else {
					it--;
					vec.erase(it + 1);
				}
				remove_level = true;
				continue ;
			}
			int res = *(it - 1) - *it;
			if (!res || res > 3) {
				if (remove_level)
					return false;
				if (it == vec.begin() + 1)
					vec.erase(it - 1);
				else
					vec.erase(it - 1);
				remove_level = true;
				continue ;
			}
			it++;
		}
	}
	return true;
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
		int_vec		vec;
		while (std::getline(f, line))
		{
			bool	is_increasing = false;
			parse_line(vec, line, is_increasing);
			if (report_is_safe(vec, is_increasing))
				total++;
		}
		std::cout << "The total amount of safe reports is " << total << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
