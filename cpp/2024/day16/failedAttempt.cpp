#include <cmath>
#include <limits>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"
#include "../../utils/EggVector.h"

void dfs(std::vector<std::vector<char>>& grid, egg::Vector2i pos, int dir, std::uint64_t currentDistance, std::uint64_t& minLength) {
	if(grid.at(pos.y).at(pos.x) == 'E') {
		minLength = std::min(minLength, currentDistance);
		return;
	}

	if(currentDistance < 5000) {
		std::cout << "---------------------\n";
		std::cout << "currentPos: ";
		pos.print();
		std::cout << "currentDistance: " << currentDistance << "\n";
		std::cout << "dir: " << dir << "\n";
	}

	if(currentDistance > minLength) return;

	if(grid.at(pos.y - 1).at(pos.x) != '#' && dir != 2) {
		// Up check
		// std::cout << "going Up\n";
		dfs(grid, egg::Vector2i(pos.x, pos.y - 1), 0, currentDistance + 1 + (dir == 0 ? 0 : 1000), minLength);
	}

	if(grid.at(pos.y).at(pos.x + 1) != '#' && dir != 3) {
		// Right check
		// std::cout << "going Right\n";
		dfs(grid, egg::Vector2i(pos.x + 1, pos.y), 1, currentDistance + 1 + (dir == 1 ? 0 : 1000), minLength);
	}

	if(grid.at(pos.y + 1).at(pos.x) != '#' && dir != 0) {
		// Down check
		// std::cout << "going Down\n";
		dfs(grid, egg::Vector2i(pos.x, pos.y + 1), 2, currentDistance + 1 + (dir == 2 ? 0 : 1000), minLength);
	}

	if(grid.at(pos.y).at(pos.x - 1) != '#' && dir != 1) {
		// Left check
		// std::cout << "going Left\n";
		dfs(grid, egg::Vector2i(pos.x - 1, pos.y), 3, currentDistance + 1 + (dir == 3 ? 0 : 1000), minLength);
	}
}

void printGrid(std::vector<std::vector<char>>& grid) {
	for(int y = 0; y < grid.size(); y++) {
		for(int x = 0; x < grid.at(y).size(); x++) {
			std::cout << grid.at(y).at(x);
		}
		std::cout << "\n";
	}
}

int main() {
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");

	egg::Vector2i start, end;
	std::vector<std::vector<char>> grid;

	grid.reserve(input.size());
	for(int y = 0; y < input.size(); y++) {
		std::vector<char> row;
		row.reserve(input.at(y).size());
		for(int x = 0; x < input.at(y).size(); x++) {
			char c = input.at(y).at(x);
			if(c == 'S') {
				start = egg::Vector2i(x, y);
			} else if(c == 'E') {
				end = egg::Vector2i(x, y);
			}
			row.emplace_back(c);
		}
		grid.emplace_back(row);
	}

	std::uint64_t minLength = std::numeric_limits<std::uint64_t>::max();

	printGrid(grid);
	dfs(grid, start, 1, 0, minLength);

	// start.print();
	// end.print();

	std::cout << "minLength: " << minLength << "\n";

	return 0;
}
