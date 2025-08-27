#include <algorithm>
#include <cstdint>
#include <ctime>
#include <string>
#include <sys/types.h>
#include <vector>
#include <utility>

#include "../../utils/EggUtils.h"

int main() {
	std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	// std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::vector<std::pair<uint64_t, uint64_t>> timeTable;

	int tOffset = 0;
	for(std::string str : input) {
		if(str.at(0) != 'x') {
			timeTable.emplace_back(std::make_pair(std::stoi(str), tOffset));
		}
			tOffset++;
	}

	std::for_each(timeTable.begin(), timeTable.end(), [](auto p){
		std::printf("id %d -> %d\n", p.first, p.second);
	});

	uint64_t currentTime = 0;
	uint64_t timeStep = timeTable.at(0).first;

	for(std::size_t i = 1; i < timeTable.size(); i++) {
		while((currentTime + timeTable.at(i).second) % timeTable.at(i).first != 0) {
			currentTime += timeStep;
		}
		std::printf("-----------------------\n");
		std::printf("train id %lu positioned at time %lu\n", timeTable.at(i).first, currentTime);
		timeStep *= timeTable.at(i).first;
	}

	return 0;
}
