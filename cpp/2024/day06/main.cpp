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

void print_map(const std::vector<std::vector<char>>& map) {
	for(std::vector<char> row : map) {
		egg::print_all(row, "");
		std::cout << "\n";
	}
}

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::pair<int, int> origionalGuardPos;
	std::pair<int, int> originalGuardDir = std::make_pair(0, -1);

	std::vector<std::vector<char>> map;
	std::vector<std::pair<int, int>> possibleObstacles;
	possibleObstacles.reserve(map.size() * map.size());
	// possibleObstacles.emplace_back(std::pair<int, int>(3, 6));
	// possibleObstacles.emplace_back(std::pair<int, int>(6, 7));
	// possibleObstacles.emplace_back(std::pair<int, int>(7, 7));
	// possibleObstacles.emplace_back(std::pair<int, int>(1, 8));
	// possibleObstacles.emplace_back(std::pair<int, int>(3, 8));
	// possibleObstacles.emplace_back(std::pair<int, int>(7, 9));
	
	map.reserve(input.size());
	for(int i = 0; i < input.size(); i++) {
		std::vector<char> out;
		out.reserve(input.at(i).size());
		for(int j = 0; j < input.at(i).size(); j++) {
			if(input.at(i).at(j) == '^') { origionalGuardPos = std::make_pair(j, i); }
			possibleObstacles.emplace_back(std::make_pair(j, i));
			out.emplace_back(input.at(i).at(j));
		}
		map.emplace_back(out);
	}

	std::set<std::pair<int, int>> uniqueObstacles;
	for(std::pair<int, int> obs : possibleObstacles) {
		std::pair<int, int> guardPos = origionalGuardPos;
		std::pair<int, int> guardDir = originalGuardDir;
		std::vector<std::vector<std::bitset<4>>> directions = create_2d_vector(map.size(), map.size());
		std::vector<std::vector<char>> newMap = map;
		newMap.at(obs.second).at(obs.first) = '@';
		// std::cout << "\nNew attempt\n";
		// print_map(newMap);
		try {
			// print_pair(std::make_pair<int, int>(guardPos.second + guardDir.second, guardPos.first + guardDir.first));
			char next;
			while(next = newMap.at(guardPos.second + guardDir.second).at(guardPos.first + guardDir.first)) {
				// print_pair(guardPos);
				switch(next) {
					case '@':
					case '#':
						guardDir = rotate_pair(guardDir);
						break;
					default:
						guardPos = std::make_pair(guardPos.first + guardDir.first, guardPos.second + guardDir.second);
						break;
				}

				if((directions.at(guardPos.second).at(guardPos.first) & pair_to_bitset(guardDir)).any()) {
					uniqueObstacles.insert(obs);
					// std::cout << "sucessful!\n";
					break;
				}
				directions.at(guardPos.second).at(guardPos.first) = directions.at(guardPos.second).at(guardPos.first) | pair_to_bitset(guardDir);
			}
		} catch(std::out_of_range err) {
			// std::cout << "not sucessful!\n";
			continue;
		}
	}
	std::cout << uniqueObstacles.size() << "\n";

	return 0;
}
