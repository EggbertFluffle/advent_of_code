#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <array>

#include "../../utils/EggUtils.h"

std::array<std::pair<int, int>, 8> directions = {
	std::make_pair(0, -1),
	std::make_pair(1, -1),
	std::make_pair(1, 0),
	std::make_pair(1, 1),
	std::make_pair(0, 1),
	std::make_pair(-1, 1),
	std::make_pair(-1, 0),
	std::make_pair(-1, -1)
};

char GetNextCellState(std::vector<std::string>& currentGeneration, int i, int j) {
	std::int16_t sum = 0;

	for(std::pair<int, int>& dir : directions) {
		int d = 1;
		while(true) {
			try {
				char looking = currentGeneration.at(i + (d * dir.second)).at(j + (d * dir.first));
				if(looking == '#') {
					sum += 1;
					break;
				} else if(looking == 'L') {
					break;
				}
				d++;
			} catch (std::out_of_range err) {
				break;
			}
		}
	}

	if(currentGeneration.at(i).at(j) == 'L' && sum == 0) {
		return '#';
	} else if(currentGeneration.at(i).at(j) == '#' && sum >= 5) {
		return 'L';
	}

	return currentGeneration.at(i).at(j);
};

std::vector<std::string> ProgressGeneration(std::vector<std::string> currentGeneration) {
	std::vector<std::string> out = currentGeneration;
	
	for(int i = 0; i < currentGeneration.size(); i++) {
		for(int j = 0; j < currentGeneration.at(0).size(); j++) {
			out.at(i).at(j) = GetNextCellState(currentGeneration, i, j);
		}
	}

	return out;
};

	int occupied = 0;

int main() {
	// std::vector<std::string> currentGeneration = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> currentGeneration = egg::readInputFile("./input.txt");

	std::vector<std::string> nextGeneration;
	while(currentGeneration != (nextGeneration = ProgressGeneration(currentGeneration))) {
		currentGeneration = nextGeneration;
	}
	// nextGeneration = ProgressGeneration(currentGeneration);

	std::for_each(currentGeneration.cbegin(), currentGeneration.cend(), [](const std::string str){
		std::for_each(str.cbegin(), str.cend(), [](const char c){
			if(c == '#') occupied++;
		});
	});

	std::printf("answer: %d\n", occupied);

	return 0;
}
