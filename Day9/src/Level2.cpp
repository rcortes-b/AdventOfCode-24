#include "../../utils.hpp"

static auto	get_amount_of_freespace(it_intvec it, int_vec vec)
{
	auto	counter = 0;
	while (it != vec.end() && *it == -1) {
		it++;
		counter++;
	}
	return counter;
}

static auto	get_amount_of_blocks(it_intvec it, int_vec vec, int value)
{
	auto	counter = 0;
	while (it != vec.begin() && *it == value) {
		it--;
		counter++;
	}
	return counter;
}

static it_intvec	get_freespace_it(int_vec &vec, it_intvec &it, int value, int block_amount)
{
	it_intvec	it2 = vec.begin();

	while (it2 != vec.end()) {
		if (*it2 == -1 && it2 < it) {
			if (block_amount <= get_amount_of_freespace(it2, vec)) {
				//std::cout << value << " " << block_amount << std::endl;
				while (block_amount-- > 0) {
					*it2 = *it;
					*it = -1;
					it2++;
					it--;
				}
				return it2;
			} else {
				while (it2 != vec.end() && *it2 == -1)
					it2++;
			}
		}
		if (it2 != vec.end())
			it2++;
	}
	return it2;
}


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
	it_intvec it = newvec.end() - 1;
	
	while (it != newvec.begin()) {
		if (*it != -1) {
			auto value = *it;
			if (get_freespace_it(newvec, it, value, get_amount_of_blocks(it, newvec, value)) == newvec.end()) {
				while (it != newvec.begin() && *it == value)
					it--;
				//it++;
			}
			/*for (it_intvec it3 = newvec.begin(); it3 != newvec.end(); it3++) {
				if (*it3 == -1)
					std::cout << '.';
				else
					std::cout << *it3;
			}*/
			//std::cout << std::endl;
		}
		else
			it--;
		//if (it != newvec.begin())
	}
}

static unsigned long long	get_checksum(std::string &line)
{
	std::vector<int>	newvec = split_diskmap(line);
	/*for (it_intvec it = newvec.begin(); it != newvec.end(); it++) {
				if (*it == -1)
					std::cout << '.';
				else
					std::cout << *it;
			}
			std::cout << std::endl;*/
	fill_diskspace(newvec);
	unsigned long long	checksum = 0;
	auto i = 0;
	for (it_intvec it = newvec.begin(); it != newvec.end(); it++) {
		if (*it != -1) {
			checksum += (i * *it);
		}
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
