#include <algorithm>
#include <set>
#include <bitset>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "../../utils/EggUtils.h"

void print_pair(const std::pair<int, int>& p) {
	std::cout << "<" << p.first << ", " << p.second << ">\n";
}

std::pair<int, int> rotate_pair(const std::pair<int, int>& p) {
	return std::make_pair((p.second != 0 ? -1 : 1) * p.second, p.first);
}

std::pair<int, int> bitset_to_pair(std::bitset<4> dir) {
	if(dir.test(0)) {
		return std::make_pair(0, -1);
	} else if(dir.test(1)) {
		return std::make_pair(1, 0);
	} else if(dir.test(2)) {
		return std::make_pair(0, 1);
	} else {
		return std::make_pair(-1, 0);
	}
}

std::bitset<4> pair_to_bitset(std::pair<int, int> dir) {
	std::bitset<4> out;
	out.reset();
	if(dir.first == 1) {
		out.flip(1);
	} else if(dir.first == -1) {
		out.flip(3);
	} else {
		if(dir.second == -1) {
			out.flip(0);
		} else {
			out.flip(2);
		}
	}
	return out;
}

std::vector<std::vector<std::bitset<4>>> create_2d_vector(std::size_t width, std::size_t height) {
	std::vector<std::vector<std::bitset<4>>> out;
	out.reserve(height);
	for(std::size_t i = 0; i < height; i++) {
		std::vector<std::bitset<4>> row;
		row.reserve(width);
		for(std::size_t j = 0; j < width; j++) {
			std::bitset<4> bitset;
			bitset.reset();
			row.emplace_back(bitset);
		}
		out.emplace_back(row);
	}
	return out;
}

void set_directions(std::vector<std::vector<std::bitset<4>>>& directions, std::vector<std::vector<char>> map, std::pair<int, int> guardPos, std::pair<int, int> guardDir) {
	guardDir = rotate_pair(rotate_pair(guardDir));
	std::pair<int, int> origionalDir = guardDir;
	char c;
	try {
		while(c = map.at(guardPos.second).at(guardPos.first)) {
			switch(c) {
				case '.':
					directions.at(guardPos.second).at(guardPos.first) = directions.at(guardPos.second).at(guardPos.first) | pair_to_bitset(origionalDir);
					guardPos.first += guardDir.first;
					guardPos.second += guardDir.second;
					break;
				case '#':
					return;
					break;
			}
		}
	} catch(std::out_of_range err) {
		return;
	}
}

int main() {
	std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	// std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::pair<int, int> guardPos;
	std::pair<int, int> guardDir = std::make_pair(0, -1);

	std::vector<std::vector<char>> map;
	map.reserve(input.size());
	for(int i = 0; i < input.size(); i++) {
		std::vector<char> out;
		out.reserve(input.at(i).size());
		for(int j = 0; j < input.at(i).size(); j++) {
			if(input.at(i).at(j) == '^') {
				guardPos = std::make_pair(j, i);
				out.emplace_back('.');
			} else {
				out.emplace_back(input.at(i).at(j));
			}
		}
		map.emplace_back(out);
	}

	std::set<std::pair<int, int>> visited;
	std::set<std::pair<int, int>> obstacles;
	std::vector<std::vector<std::bitset<4>>> directions = create_2d_vector(map.size(), map.size());
	visited.insert(guardPos);
	directions.at(guardPos.second).at(guardPos.first) = directions.at(guardPos.second).at(guardPos.first) | pair_to_bitset(guardDir);
	try {
		char next;
		while(next = map.at(guardPos.second + guardDir.second).at(guardPos.first + guardDir.first)) {
			switch(next) {
				case '#':
					guardDir = rotate_pair(guardDir);
					set_directions(directions, map, guardPos, guardDir);
					break;
				default:
					guardPos.first = guardPos.first + guardDir.first;
					guardPos.second = guardPos.second + guardDir.second;

					visited.insert(guardPos);
					break;
			}
			if((directions.at(guardPos.second).at(guardPos.first) & pair_to_bitset(rotate_pair(guardDir))).any()) {
				obstacles.insert(std::make_pair(guardPos.first + guardDir.first, guardPos.second + guardDir.second));
			}
			directions.at(guardPos.second).at(guardPos.first) = directions.at(guardPos.second).at(guardPos.first) | pair_to_bitset(guardDir);
		}
	} catch(std::out_of_range err) {
		for(std::pair<int, int> p : obstacles) {
			print_pair(p);
		}
		std::cout << obstacles.size() << "\n";
	}

	return 0;
}

