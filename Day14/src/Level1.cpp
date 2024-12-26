#include "../../utils.hpp"

#define ROBOT_AMOUNT 500
#define	WIDE_SIZE 101
#define TALL_SIZE 103
#define TOTAL_SECONDS 100

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

static void	robots_loop(void)
{
	auto	seconds = -1;
	auto	robot_c = 0;
	while (++seconds < TOTAL_SECONDS) {
		robot_c = -1;
		while (++robot_c < ROBOT_AMOUNT) {
			do_movement(robot_c);
		}
	}
}

static int	get_safety_factor(void)
{
	auto	num = 0;
	auto	robot_num = 0;
	auto	y = -1;
	auto	x = -1;

	while (++y < TALL_SIZE / 2) { //UP LEFT
		x = -1;
		while (++x < WIDE_SIZE / 2) {
			if (map[y][x])
				robot_num += map[y][x];
		}
	}
	num = robot_num;
	robot_num = 0;
	y = TALL_SIZE / 2;
	while (++y < TALL_SIZE) { //DOWN LEFT
		x = -1;
		while (++x < WIDE_SIZE / 2) {
			if (map[y][x])
				robot_num += map[y][x];
		}
	}
	num *= robot_num;
	robot_num = 0;
	y = -1;
	while (++y < TALL_SIZE / 2) { //UP RIGHT
		x = WIDE_SIZE / 2;
		while (++x < WIDE_SIZE) {
			if (map[y][x])
				robot_num += map[y][x];
		}
	}
	num *= robot_num;
	robot_num = 0;
	y = TALL_SIZE / 2;
	while (++y < TALL_SIZE) { //DOWN RIGHT
		x = WIDE_SIZE / 2;
		while (++x < WIDE_SIZE)
			if (map[y][x])
				robot_num += map[y][x];
	}
	num *= robot_num;

	return num;
}

int main(int argc, char **argv)
{
	try {
		if (argc == 1)
			throw ThrowError("Not input provided");
		else if (argc > 2)
			throw ThrowError("You can provide only one input");

		parse_robots(argv[1]);
		robots_loop();
		
		std::cout << "The safety factor is " << get_safety_factor() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}