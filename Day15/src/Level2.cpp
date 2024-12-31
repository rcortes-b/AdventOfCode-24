#include "../../utils.hpp"

#define MAP_SIZE 50

enum e_movement
{
	WALL = 0,
	ROCK,
	FREE
};

typedef struct	s_lfish {
	std::string					map[MAP_SIZE];
	std::vector<std::string>	steps;
	int	y;
	int	x;
}				t_lfish;

static void	print_map(t_lfish &lfish)
{
	for (auto y = 0; y < MAP_SIZE; y++) {
		for (auto x = 0; x < lfish.map[y].size(); x++) {
			std::cout << lfish.map[y][x];
		}
		std::cout << std::endl;
	}
	std::cout << "\n\n\n";
}

static void	get_num_boxes(t_lfish &lfish)
{
	auto	box = 0;
	for (auto y = 0; y < MAP_SIZE; y++) {
		for (auto x = 0; x < lfish.map[y].size(); x++) {
			if (lfish.map[y][x] == '[' && lfish.map[y][x + 1] == ']')
				box++;
		}
	}
	std::cout << "Number of boxes is: " << box << std::endl;	
}

static void	parse_data(t_lfish &lfish, char *file)
{
	std::fstream	f;
	f.open(file);
	if (!f)
		throw ThrowError("Failed accessing the input");
	std::string	line = "";
	bool		is_steps = false;
	auto		counter = 0;
	while (std::getline(f, line)) {
		if (line.empty()) {
			is_steps = true;
			continue ;
		}
		if (is_steps)
			lfish.steps.push_back(line);
		else {
			std::string	newline = "";
			auto		ocurr = 0;
			char		c;
			for (auto i = 0; i < line.size(); i++) {
				c = line[i];
				ocurr = 0;
				for (; i < line.size() && line[i] == c && line[i] != '@'; i++)
					ocurr++;
				if (ocurr)
					i--;
				if (c == '@') {
					newline += "@.";
					lfish.y = counter;
					lfish.x = newline.find('@');
				}
				else if (c == '.')
					newline += std::string(ocurr * 2, '.');
				else if (c == '#')
					newline += std::string(ocurr * 2, '#');
				else {
					while (--ocurr >= 0)
						newline += "[]";
				}
			}
			lfish.map[counter++] = newline;
		}
	}
}

static int	is_empty(t_lfish &lfish, std::pair<int, int> &bound_right, std::pair<int, int> &bound_left, bool is_up)
{
	auto	x = bound_left.second;
	auto	y = 0;
	if (is_up)
		y = bound_left.first - 1;
	else
		y = bound_left.first + 1;
	bool	is_rock = false;
	while (x <= bound_right.second)
	{
		if (lfish.map[y][x] == '#' && ((is_up && lfish.map[y + 1][x] != '.') || (!is_up && lfish.map[y - 1][x] != '.')))
			return WALL;
		else if (lfish.map[y][x] != '.')
			is_rock = true;
		x++;
	}
	if (is_rock)
		return ROCK;
	return FREE;
}

static void	update_right_bound(t_lfish &lfish, std::pair<int, int> &bound_right, bool is_up)
{
	int y = bound_right.first, x = bound_right.second;

	if (is_up) {
		if ('[' == lfish.map[y - 1][x]) {
			bound_right.first = y - 1;
			bound_right.second = x + 1;
		}
		else if (']' == lfish.map[y - 1][x]) {
			bound_right.first = y - 1;
			bound_right.second = x;
		}
		else if ('.' == lfish.map[y - 1][x]) {
			bound_right.first = y - 1;
			while (lfish.map[bound_right.first][x] != ']')
				x--;
			bound_right.second = x;
		}
	} else {
		if ('[' == lfish.map[y + 1][x]) {

			bound_right.first = y + 1;
			bound_right.second = x + 1;
		}
		else if (']' == lfish.map[y + 1][x]) {
			bound_right.first = y + 1;
			bound_right.second = x;
		}
		else if ('.' == lfish.map[y + 1][x]) {
			bound_right.first = y + 1;
			while (lfish.map[bound_right.first][x] != ']')
				x--;
			bound_right.second = x;
		}
	}
}

static void	update_left_bound(t_lfish &lfish, std::pair<int, int> &bound_left, bool is_up)
{
	int y = bound_left.first, x = bound_left.second;

	if (is_up) {
		if ('[' == lfish.map[y - 1][x]) {
			bound_left.first = y - 1;
			bound_left.second = x;
		}
		else if (']' == lfish.map[y - 1][x]) {
			bound_left.first = y - 1;
			bound_left.second = x - 1;
		}
		else if ('.' == lfish.map[y - 1][x]){
			bound_left.first = y - 1;
			while (lfish.map[bound_left.first][x] != '[')
				x++;
			bound_left.second = x;
		}
	} else {
		if ('[' == lfish.map[y + 1][x]) {

			bound_left.first = y + 1;
			bound_left.second = x;
		}
		else if (']' == lfish.map[y + 1][x]) {
			bound_left.first = y + 1;
			bound_left.second = x - 1;
		}
		else if ('.' == lfish.map[y + 1][x]){
			bound_left.first = y + 1;
			while (lfish.map[bound_left.first][x] != '[')
				x++;
			bound_left.second = x;
		}
	}
}

static void	do_up_aux(t_lfish &lfish, std::pair<int, int> &bound_left, std::pair<int, int> &bound_right, bool is_up)
{
	int		status = -1;
	std::vector<std::pair<int, int>>	v_left {bound_left};
	std::vector<std::pair<int, int>>	v_right {bound_right};
	while ((status = is_empty(lfish, bound_right, bound_left, is_up)) >= 0) 
	{
		if (status == WALL)
			return ;
		else if (status == FREE)
			break ;
		update_right_bound(lfish, bound_right, is_up);
		update_left_bound(lfish, bound_left, is_up);
		v_right.insert(v_right.begin(), bound_right);
		v_left.insert(v_left.begin(), bound_left);
	}
	std::vector<std::pair<int, int>>::iterator	it_r = v_right.begin();
	for (auto &a: v_left) {
		while (a.second <= it_r->second) {
			if (lfish.map[a.first][a.second] == '[' || lfish.map[a.first][a.second] == ']') {
				lfish.map[a.first - 1][a.second] =  lfish.map[a.first][a.second];
				lfish.map[a.first][a.second] = '.';
			}
			a.second++;
		}
		it_r++;
	}
	lfish.map[lfish.y][lfish.x] = '.';
	lfish.y--;
	lfish.map[lfish.y][lfish.x] = '@';
}

static void	do_up(t_lfish &lfish)
{
	if (lfish.map[lfish.y - 1][lfish.x] == '#')
		return ;
	else if (lfish.map[lfish.y - 1][lfish.x] == '.') {
		lfish.map[lfish.y][lfish.x] = '.';
		lfish.y--;
		lfish.map[lfish.y][lfish.x] = '@';
	}
	else {
		std::pair<int, int> bound_left;
		std::pair<int, int> bound_right;
		if (lfish.map[lfish.y - 1][lfish.x] == '[') {
			bound_left.first = lfish.y - 1;
			bound_left.second = lfish.x;
			bound_right.first = lfish.y - 1;
			bound_right.second = lfish.x + 1;
		} else {
			bound_left.first = lfish.y - 1;
			bound_left.second = lfish.x - 1;
			bound_right.first = lfish.y - 1;
			bound_right.second = lfish.x;
		}
		do_up_aux(lfish, bound_left, bound_right, true);
	}
}

static void	do_down_aux(t_lfish &lfish, std::pair<int, int> &bound_left, std::pair<int, int> &bound_right, bool is_up)
{
	int		status = -1;
	std::vector<std::pair<int, int>>	v_left {bound_left};
	std::vector<std::pair<int, int>>	v_right {bound_right};
	while ((status = is_empty(lfish, bound_right, bound_left, is_up)) >= 0)
	{
		if (status == WALL)
			return ;
		else if (status == FREE)
			break ;
		update_right_bound(lfish, bound_right, is_up);
		update_left_bound(lfish, bound_left, is_up);
		v_right.insert(v_right.begin(), bound_right);
		v_left.insert(v_left.begin(), bound_left);
	}
	std::vector<std::pair<int, int>>::iterator	it_r = v_right.begin();
	for (auto &a : v_left)
	{
		while (a.second <= it_r->second) {
			if (lfish.map[a.first][a.second] == '[' || lfish.map[a.first][a.second] == ']') {
				lfish.map[a.first + 1][a.second] =  lfish.map[a.first][a.second];
				lfish.map[a.first][a.second] = '.';
			}
			a.second++;
		}
		it_r++;
	}
	lfish.map[lfish.y][lfish.x] = '.';
	lfish.y++;
	lfish.map[lfish.y][lfish.x] = '@';
}

static void	do_down(t_lfish &lfish)
{
	if (lfish.map[lfish.y + 1][lfish.x] == '#')
		return ;
	else if (lfish.map[lfish.y + 1][lfish.x] == '.') {
		lfish.map[lfish.y][lfish.x] = '.';
		lfish.y++;
		lfish.map[lfish.y][lfish.x] = '@';
	}
	else {
		std::pair<int, int> bound_left;
		std::pair<int, int> bound_right;
		if (lfish.map[lfish.y + 1][lfish.x] == '[') {
			bound_left.first = lfish.y + 1;
			bound_left.second = lfish.x;
			bound_right.first = lfish.y + 1;
			bound_right.second = lfish.x + 1;
		} else {
			bound_left.first = lfish.y + 1;
			bound_left.second = lfish.x - 1;
			bound_right.first = lfish.y + 1;
			bound_right.second = lfish.x;
		}
		do_down_aux(lfish, bound_left, bound_right, false);
	}
}

static void	do_left(t_lfish &lfish)
{
	if (lfish.map[lfish.y][lfish.x - 1] == '#')
		return ;
	else if (lfish.map[lfish.y][lfish.x - 1] == '.') {
		lfish.map[lfish.y][lfish.x] = '.';
		lfish.x--;
		lfish.map[lfish.y][lfish.x] = '@';
	}
	else {
		auto rocks = 0;
		while (lfish.map[lfish.y][lfish.x - rocks - 2] == '[')
			rocks += 2;
		if (lfish.map[lfish.y][lfish.x - rocks - 1] == '.') {
			auto	i = -1;
			while (++i < rocks) {
				if (i % 2 == 0) {
					lfish.map[lfish.y][lfish.x - rocks - 1 + i] = '[';
				}
				else
					lfish.map[lfish.y][lfish.x - rocks - 1 + i] = ']';
			}
			lfish.map[lfish.y][lfish.x] = '.';
			lfish.x--;
			lfish.map[lfish.y][lfish.x] = '@';
		}
	}
}

static void	do_right(t_lfish &lfish)
{
	if (lfish.map[lfish.y][lfish.x + 1] == '#')
		return ;
	else if (lfish.map[lfish.y][lfish.x + 1] == '.') {
		lfish.map[lfish.y][lfish.x] = '.';
		lfish.x++;
		lfish.map[lfish.y][lfish.x] = '@';
	}
	else {
		auto rocks = 0;
		while (lfish.map[lfish.y][lfish.x + rocks + 2] == ']')
			rocks += 2;
		if (lfish.map[lfish.y][lfish.x + rocks + 1] == '.') {
			auto	i = 0;
			while (i < rocks) {
				if (i % 2 == 0) {
					lfish.map[lfish.y][lfish.x + rocks + 1 - i] = ']';
				}
				else
					lfish.map[lfish.y][lfish.x + rocks + 1 - i] = '[';
				i++;
			}
			lfish.map[lfish.y][lfish.x] = '.';
			lfish.x++;
			lfish.map[lfish.y][lfish.x] = '@';
		}
	}
}

static void	do_movement(t_lfish &lfish, char c)
{
	switch (c)
	{
		case '<' :
					do_left(lfish);
					break ;
		case '^' :
					do_up(lfish);
					break ;
		case '>' :
					do_right(lfish);
					break ;
		case 'v' :
					do_down(lfish);
					break ;
		default:
					return ;
	}
}

static int long long	sum_coordinates(t_lfish &lfish)
{
	int	long long	res = 0;
	auto			size = lfish.map[0].size();

	for (auto y = 0; y < MAP_SIZE; y++) 
		for (auto x = 0; x < size; x++) 
			if (lfish.map[y][x] == '[')
				res += y * 100 + x;
	return res;
}

int main(int argc, char **argv)
{
	try {
		if (argc == 1)
			throw ThrowError("Not input provided");
		else if (argc > 2)
			throw ThrowError("You can provide only one input");
		t_lfish	lfish;
		parse_data(lfish, argv[1]);
		//get_num_boxes(lfish);
		//print_map(lfish);
		auto	i = 0;
		for (auto &a : lfish.steps) {
			i = -1;
			auto size = a.size();
			while (++i < size)
				do_movement(lfish, a[i]);
		}
		//get_num_boxes(lfish);
		//print_map(lfish);
		std::cout << "The sum of all boxes' GPS coordinates is " << sum_coordinates(lfish) << std::endl;		
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}