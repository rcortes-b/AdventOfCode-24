#include "../../utils.hpp"

unsigned long int	total_calibration = 0;

static void	set_vector(llint_vec &vec, std::string &line, int pos)
{
	for (; pos < line.size(); pos++) {
		if (std::isdigit(line[pos])) {
			vec.push_back(std::atoll(&line[pos]));
			while (pos < line.size() && std::isdigit(line[pos]))
				pos++;
			if (pos == line.size())
				return ;
		}
	}
}

static int long long	get_concatenated_num(int long long num1, int long long num2)
{
	int 			counter = 0;
	int long long	tmp = num2;
	while (tmp > 0) {
		tmp /= 10;
		counter++;
	}
	while(counter-- > 0) {
		num1 *= 10;
	}
	return num1 + num2;
}

static bool	recursive(llint_vec vec, int long long num)
{
	if (vec.size() == 1 && *vec.begin() == num)
		return true;
	else if (vec.size() == 1)
		return false;
	else {
		if (*vec.begin() + *(vec.begin() + 1) <= num) {
			llint_vec vec2 = vec;
			*vec2.begin() = *vec2.begin() + *(vec2.begin() + 1);
			vec2.erase(vec2.begin() + 1);
			if (recursive(vec2, num))
				return true;
		}
		if (*vec.begin() * *(vec.begin() + 1) <= num) {
			llint_vec vec3 = vec;
			*vec3.begin() = *vec3.begin() * *(vec3.begin() + 1);
			vec3.erase(vec3.begin() + 1);
			if (recursive(vec3, num))
				return true;
		}
		int long long concatenated_num = get_concatenated_num(*vec.begin(), *(vec.begin() + 1));
		//std::cout << concatenated_num << " " << num << " " << *vec.begin() << " " << *(vec.begin() + 1) << std::endl;
		if (concatenated_num <= num) {
			vec.erase(vec.begin());
			*vec.begin() = concatenated_num;
			if (recursive(vec, num))
				return true;
		}
	}
	return false;
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
		llint_vec			vec;
		long long	int	num = 0;

		while (std::getline(f, line))
		{
			num = std::atol(line.c_str());
			set_vector(vec, line, line.find(':') + 1);
			if (recursive(vec, num))
				total_calibration += num;
			if (!vec.empty())
				vec.clear();
		}
		std::cout << "The total amount of visited positions is: " << total_calibration << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}