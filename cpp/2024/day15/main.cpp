#include <cmath>
#include <string>
#include <utility>
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

void moveStack(std::vector<std::vector<char>>& grid, egg::Vector2i pos, egg::Vector2i& dir) {
	char c = grid.at(pos.y).at(pos.x);
	if(c == '.') return;
	egg::Vector2i otherHalf = egg::Vector2i(pos.x + (c == ']' ? -1 : 1), pos.y);
	moveStack(grid, pos + dir, dir);
	moveStack(grid, otherHalf + dir, dir);
	
	grid.at(pos.y + dir.y).at(pos.x) = grid.at(pos.y).at(pos.x);
	grid.at(otherHalf.y + dir.y).at(otherHalf.x) = grid.at(otherHalf.y).at(otherHalf.x);
	grid.at(pos.y).at(pos.x) = '.';
	grid.at(otherHalf.y).at(otherHalf.x) = '.';
}

bool checkStack(std::vector<std::vector<char>>& grid, egg::Vector2i pos, egg::Vector2i& dir) {
	char c = grid.at(pos.y).at(pos.x);
	if(c == '#') return false;
	if(c == '.') return true;
	egg::Vector2i other = egg::Vector2i(pos.x + (c == ']' ? -1 : 1), pos.y + dir.y);
	return checkStack(grid, other, dir) && checkStack(grid, pos + dir, dir);
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

	if(dir.x != 0) {
		int probe = pos.x + dir.x;
		while(grid.at(pos.y).at(probe) != '#') {
			if(grid.at(pos.y).at(probe) == '.')	{
				for(int i = probe; i != pos.x + dir.x; i -= dir.x) {
					grid.at(pos.y).at(i) = grid.at(pos.y).at(i - dir.x);
				}
				grid.at(pos.y).at(pos.x + dir.x) = '.';
				pos.x += dir.x;
				return;
			} else {
				probe += dir.x;
			}
		}
	} else {
		if(checkStack(grid, pos + dir, dir)) {
			moveStack(grid, pos + dir, dir);
			pos = pos + dir;
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
		row.reserve(input.at(y).size() * 2);
		for(int x = 0; x < input.at(y).size(); x++) {
			switch(input.at(y).at(x)) {
				case '@':
					pos = egg::Vector2i(x * 2, y);
					row.emplace_back('.');
					row.emplace_back('.');
					break;
				case '#':
					row.emplace_back('#');
					row.emplace_back('#');
					break;
				case 'O':
					row.emplace_back('[');
					row.emplace_back(']');
					break;
				case '.':
					row.emplace_back('.');
					row.emplace_back('.');
					break;
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
			if(grid.at(y).at(x) == '[') sum += 100 * y + x;
		}
	}
	std::cout << "total gps: " << sum << "\n";

	return 0;
}
