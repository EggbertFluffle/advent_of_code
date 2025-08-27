#include <cmath>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"
#include "../../utils/EggVector.h"

void printGrid(std::vector<std::vector<char>>& grid, egg::Vector2i& pos) {
	for(int y = 0; y < grid.size(); y++) {
		for(int x = 0; x < grid.at(y).size(); x++) {
			if(pos.x == x && pos.y == y) {
				std::cout << '@';
			} else {
				std::cout << grid.at(y).at(x);
			}
		}
		std::cout << "\n";
	}
}

void executeMovement(std::vector<std::vector<char>>& grid, egg::Vector2i& pos, char charDir) {
	egg::Vector2i dir;
	switch(charDir) {
		case '<':
			dir = egg::Vector2i(-1, 0);
			break;
		case '^':
			dir = egg::Vector2i(0, -1);
			break;
		case '>':
			dir = egg::Vector2i(1, 0);
			break;
		case 'v':
			dir = egg::Vector2i(0, 1);
			break;
		default:
			dir = egg::Vector2i(0, 0);
			break;
	}

	if(grid.at(pos.y + dir.y).at(pos.x + dir.x) == '.') {
		pos = pos + dir;
		return;
	}

	if(grid.at(pos.y + dir.y).at(pos.x + dir.x) == '#') {
		return;
	}

	egg::Vector2i probe = pos + dir;
	while(grid.at(probe.y).at(probe.x) != '#') {
		if(grid.at(probe.y).at(probe.x) == '.')	{
			grid.at(probe.y).at(probe.x) = 'O';
			grid.at(pos.y + dir.y).at(pos.x + dir.x) = '.';
			pos = pos + dir;
			return;
		} else {
			probe = probe + dir;
		}
	}
}

int main() {
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");

	egg::Vector2i pos;

	std::string movements = input.at(0);
	input.erase(input.begin());

	std::vector<std::vector<char>> grid;
	grid.reserve(input.size());
	for(int y = 0; y < input.size(); y++) {
		std::vector<char> row;
		row.reserve(input.at(y).size());
		for(int x = 0; x < input.at(y).size(); x++) {
			if(input.at(y).at(x) == '@') {
				pos = egg::Vector2i(x, y);
				row.emplace_back('.');
			} else {
				row.emplace_back(input.at(y).at(x));
			}
		}
		grid.emplace_back(row);
	}
	
	for(char c : movements) {
		executeMovement(grid, pos, c);
	}

	std::uint64_t sum = 0;
	for(std::size_t y = 0; y < grid.size(); y++) {
		for(std::size_t x = 0; x < grid.at(y).size(); x++) {
			if(grid.at(y).at(x) == 'O') sum += 100 * y + x;
		}
	}
	std::cout << "total gps: " << sum << "\n";

	return 0;
}
