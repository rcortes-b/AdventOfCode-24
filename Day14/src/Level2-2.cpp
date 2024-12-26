#include "../../utils.hpp"

#define ROBOT_AMOUNT 500
#define	WIDE_SIZE 101
#define TALL_SIZE 103
#define TOTAL_SECONDS 10000

/*
Figured out that forming a tree means that there are no clusters in the same position.
It means that if reading all the map and there is no more than 0 to 1 robots in each position there is a tree drawn
*/

typedef struct s_robot
{
	int	y;
	int	x;
	int	v_y;
	int	v_x;
}				t_robot;


int		map[TALL_SIZE][WIDE_SIZE] = {0};
t_robot	robot[ROBOT_AMOUNT];

static void	parse_robots(char *file)
{
	std::fstream	f;
	f.open(file);
	if (!f)
		throw ThrowError("Failed accessing the input");
	std::string	line = "";
	auto		counter = 0;
	auto		i = 0;
	while (std::getline(f, line)) {
		i = 0;
		i = line.find("=", 0, 1) + 1;
		robot[counter].x = std::atoi(&line[i]);
		i = line.find(",", i, 1) + 1;
		robot[counter].y = std::atoi(&line[i]);
		i = line.find("=", i, 1) + 1;
		robot[counter].v_x = std::atoi(&line[i]);
		i = line.find(",", i, 1) + 1;
		robot[counter].v_y = std::atoi(&line[i]);
		map[robot[counter].y][robot[counter].x]++;
		counter++;
	}
}

static void	do_movement(int	robot_index)
{
	map[robot[robot_index].y][robot[robot_index].x]--;
	if (robot[robot_index].y + robot[robot_index].v_y >= TALL_SIZE)
		robot[robot_index].y = robot[robot_index].y + robot[robot_index].v_y - TALL_SIZE;
	else if (robot[robot_index].y + robot[robot_index].v_y < 0)
		robot[robot_index].y = TALL_SIZE - ((robot[robot_index].y + robot[robot_index].v_y) * -1);
	else
		robot[robot_index].y += robot[robot_index].v_y;
	
	if (robot[robot_index].x + robot[robot_index].v_x >= WIDE_SIZE)
		robot[robot_index].x = robot[robot_index].x + robot[robot_index].v_x - WIDE_SIZE;
	else if (robot[robot_index].x + robot[robot_index].v_x < 0)
		robot[robot_index].x = WIDE_SIZE - ((robot[robot_index].x + robot[robot_index].v_x) * -1);
	else
		robot[robot_index].x += robot[robot_index].v_x;
	map[robot[robot_index].y][robot[robot_index].x]++;
}

static auto	robots_loop(void)
{
	auto	seconds = -1;
	auto	robot_c = 0;
	bool	is_unique = true;
	auto	seconds_eg = 0;

	while (++seconds < TOTAL_SECONDS) {
		robot_c = -1;
		while (++robot_c < ROBOT_AMOUNT) {
			do_movement(robot_c);
		}
		is_unique = true;
		for (auto y = 0; y < TALL_SIZE; y++) {
			for (auto x = 0; x < WIDE_SIZE; x++) {
				if (map[y][x] > 1) {
					is_unique = false;
					break ;
				}
			}
			if (!is_unique)
				break ;
		}
		if (is_unique)
			return seconds + 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	try {
		if (argc == 1)
			throw ThrowError("Not input provided");
		else if (argc > 2)
			throw ThrowError("You can provide only one input");

		parse_robots(argv[1]);
		auto second = robots_loop();
		
		std::cout << "The easter egg happens in the second nº " << second << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}