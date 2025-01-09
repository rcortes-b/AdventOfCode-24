#include "../../utils.hpp"

static void	parse_line_to_vector(llint_vec &vec, std::string &line)
{
	for (auto i = 0; i < line.size(); i++) {
		if (std::isdigit(line[i])) {
			vec.push_back(std::atoll(&line[i]));
			while (i < line.size() && std::isdigit(line[i]))
				i++;
		}
	}
}

static void	blink_and_split(llint_vec &vec)
{
	llint_vec	v2;
	for (auto i = 0; i < 25; i++) {
		std::cout << i << std::endl;
		if (!v2.empty())
			v2.clear();
		for (it_llintvec it = vec.begin(); it != vec.end(); it++) {
			if (!*it) {
				v2.push_back(1);
			}
			else {
				std::string strnum = std::to_string(*it);
				if (strnum.size() % 2 == 0) {
					v2.push_back(std::atoll(strnum.substr(0, strnum.size() / 2).c_str()));
					v2.push_back(std::atoll(&strnum[strnum.size() / 2]));
				}
				else
					v2.push_back(*it * 2024);
			}
		}
		//if (!vec.empty())
		//	vec.clear();
		vec = v2;
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

		std::string	line = "";
		std::getline(f, line);
		
		llint_vec	vec;
		parse_line_to_vector(vec, line);
		blink_and_split(vec);

		std::cout << "The total amount of stones after blinking 25 times is " << vec.size() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}