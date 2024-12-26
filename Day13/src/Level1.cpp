#include "../../utils.hpp"

#define ROBOT_AMOUNT 500
#define	WIDE_SIZE 101
#define TALL_SIZE 103
#define TOTAL_SECONDS 100

typedef struct s_arcade
{
	int	xa;
	int	xb;
	int	ya;
	int	yb;
	int	xp;
	int	yp;
}				t_arcade;

std::vector<t_arcade>	arcade;

static void	get_nums(std::string &line, int &x, int &y)
{
	auto i = 0;

	i = line.find("X", i) + 2;
	x = std::atoi(&line[i]);
	i = line.find("Y", i) + 2;
	y = std::atoi(&line[i]);
}

static void	parse_claw_machines(char *file)
{
	std::fstream	f;
	f.open(file);
	if (!f)
		throw ThrowError("Failed accessing the input");
	std::string	line = "";
	auto		counter = 0;
	t_arcade	clawmachine;
	while (std::getline(f, line)) {
		if (line.empty()) {
			arcade.push_back(clawmachine);
			continue ;
		}
		if (line.substr(0, 8) == "Button A")
			get_nums(line, clawmachine.xa, clawmachine.ya);
		else if (line.substr(0, 8) == "Button B")
			get_nums(line, clawmachine.xb, clawmachine.yb);
		else
			get_nums(line, clawmachine.xp, clawmachine.yp);
	}
	arcade.push_back(clawmachine);
}

static auto	get_single_machine_prize(t_arcade &clawmachine)
{
	auto 	value = clawmachine.ya * clawmachine.xb;
	auto	value2 = clawmachine.xa * clawmachine.yb;
	auto	prize_updated = clawmachine.ya * clawmachine.xp;
	auto	prize_updated2 = clawmachine.xa * clawmachine.yp;
	auto	nb = (prize_updated2 - prize_updated) / (value2 - value);
	auto	na = (clawmachine.xp - (clawmachine.xb * nb)) / clawmachine.xa;
	if (((clawmachine.xb * nb) + (clawmachine.xa * na)) != clawmachine.xp)
		return 0;
	else if (((clawmachine.yb * nb) + (clawmachine.ya * na)) != clawmachine.yp)
		return 0;
	return ((na * 3) + nb);
}

int main(int argc, char **argv)
{
	try {
		if (argc == 1)
			throw ThrowError("Not input provided");
		else if (argc > 2)
			throw ThrowError("You can provide only one input");

		parse_claw_machines(argv[1]);
		auto	tokens = 0;
		for (auto &a : arcade) {
			tokens += get_single_machine_prize(a);
		}
		std::cout << "The fewest amount of tokens to get all the possible prizes is " << tokens << std::endl;		
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}