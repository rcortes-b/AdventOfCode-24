#include "../../utils.hpp"

static std::vector<int>	split_diskmap(std::string &line)
{
	auto				id_counter = 0;
	std::vector<int>	newvec;

	for (auto i = 0; i < line.size(); i++) {
		if (i % 2 == 0) {
			if (!newvec.empty())
				newvec.insert(newvec.end() , line[i] - '0', id_counter);
			else {
				newvec.push_back(id_counter);
				newvec.insert(newvec.begin(), ((line[i] - '0') - 1), id_counter);
			}
			id_counter++;
		}
		else {
			if (!newvec.empty())
				newvec.insert(newvec.end() , line[i] - '0', -1);
			else {
				newvec.push_back(-1);
				newvec.insert(newvec.begin(), ((line[i] - '0') - 1), -1);
			}
		}	
	}
	return newvec;
}

static void	fill_diskspace(std::vector<int> &newvec)
{
	it_intvec end = newvec.end() - 1;
	for (it_intvec start = newvec.begin(); start != newvec.end() && start <= end; start++) {
		if (*start == -1) {
			//std::cout << newline << std::endl;
			while (*end == -1 && end > start)
				end--;

			*start = *end;
			*end = -1;
			//end = newline.size() - 1;
		}
	}
}

static unsigned long long	get_checksum(std::string &line)
{
	std::vector<int>	newvec = split_diskmap(line);
	fill_diskspace(newvec);
	unsigned long long	checksum = 0;
	auto i = 0;
	for (it_intvec it = newvec.begin(); it != newvec.end(); it++) {
		if (*it != -1)
			checksum += (i * *it);
		i++;
	}

	return checksum;
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

		std::string	line;
		std::getline(f, line);

		std::cout << "The filesystem checksum is " << get_checksum(line) << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}