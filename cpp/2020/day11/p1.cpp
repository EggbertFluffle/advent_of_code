#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

#include "../../utils/EggUtils.h"

char GetNextCellState(std::vector<std::string>& currentGeneration, int i, int j) {
	std::int16_t sum;

	for(int x = -1; x <= 1; x++) {
		for(int y = -1; y <= 1; y++) {
	 		try {
				if(x == 0 && y == 0) continue;
				sum += currentGeneration.at(i + y).at(j + x) == '#' ? 1 : 0;
	 		} catch (std::out_of_range err) { }
		}
	}

	if(currentGeneration.at(i).at(j) == 'L' && sum == 0) {
		return '#';
	} else if(currentGeneration.at(i).at(j) == '#' && sum >= 4) {
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

	std::for_each(currentGeneration.cbegin(), currentGeneration.cend(), [](const std::string str){
		std::for_each(str.cbegin(), str.cend(), [](const char c){
			if(c == '#') occupied++;
		});
	});

	std::printf("answer: %d\n", occupied);

	return 0;
}
