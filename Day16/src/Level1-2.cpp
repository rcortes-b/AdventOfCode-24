#include "../../utils.hpp"

enum	e_direction {
	EAST,
	SOUTH,
	WEST,
	NORTH
};

typedef struct s_data
{
	std::vector<std::string>	grid;
	std::pair<int, int>			dirs[4] = {{0, 1}, {1,0}, {0, -1}, {-1, 0}}; //E, S, W, N
	int	y, x;
}				t_data;

static void	parse_data(t_data &data)
{
	std::ifstream	f("../input");
	std::string		line = "";
	auto			counter = 0;
	auto			index = 0;
	while (std::getline(f, line))
	{
		data.grid.push_back(line);
		if ((index = line.find('S')) != std::string::npos) {
			data.y = counter;
			data.x = index;
		}
		counter++;
	}
	f.close();
}

static int	dijsktra(t_data &data)
{
	std::priority_queue<std::tuple<int, int, int, int>, std::vector<std::tuple<int, int, int, int>>, std::greater<std::tuple<int, int, int, int>>>	pq;
	std::map<std::tuple<int, int, int>, int>	visited;
	pq.push({0, data.y, data.x, EAST});
	visited[{data.y, data.x, EAST}] = 0;
	while(!pq.empty())
	{
		auto [dist, y, x, dir] = pq.top();
		pq.pop();
		if (data.grid[y][x] == 'E')
			return dist;
		for (auto i = 0; i < 4; i++) {
			if ((i % 2 == 0 && dir % 2 == 0 && i != dir) || (i % 2 != 0 && dir % 2 != 0 && i != dir))
				continue ;
			auto 	nY = y + data.dirs[i].first;
			auto 	nX = x + data.dirs[i].second;
			auto	nDist = dist + 1;
			if (data.grid[nY][nX] == '#')
				continue ;
			if (i != dir)
				nDist += 1000;
			auto cur = std::make_tuple(nY, nX, dir);
			if (visited.find(cur) == visited.end() || nDist < visited[cur]) {
				visited[cur] = nDist;
				pq.push(std::make_tuple(nDist, nY, nX, i));
			}
		}
	}
	return 0;
}

int main(void)
{
	try {
		t_data	data;
		parse_data(data);
		std::cout << "The lowest score is " << dijsktra(data) << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}