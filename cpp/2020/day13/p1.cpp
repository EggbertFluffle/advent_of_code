#include <string>
#include <vector>

#include "../../utils/EggUtils.h"

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	int timestart = 1002618;

	std::vector<int> busIDs;

	for(std::string str : input) {
		busIDs.emplace_back(std::stoi(str));
	}

	int minWaitTime = 1000000000;
	int minBusId = 0;
	for(int id : busIDs) {
		if(id - (timestart % id) < minWaitTime) {
			minWaitTime = id - (timestart % id);
			minBusId = id;
		}
	}

	std::printf("busID: %d\n", minBusId);
	std::printf("remainder: %d\n", minWaitTime);
	std::printf("%d\n", minWaitTime * minBusId);

	return 0;
}
