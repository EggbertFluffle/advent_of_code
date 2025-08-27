#include <string>
#include <algorithm>
#include <vector>

#include "../../utils/EggUtils.h"

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::vector<int> numbers;
	numbers.reserve(input.size());
	for(std::string& str : input) {
		numbers.emplace_back(std::stol(str));
	}

	std::sort(numbers.begin(), numbers.end());
	
	int oneJolts = 0;
	int threeJolts = 0;
	int currentJoltage = 0;
	for(std::size_t i = 0; i < numbers.size(); i++) {
		int diff = numbers.at(i) - currentJoltage;
		std::printf("from: %d, to: %d, diff: %d", currentJoltage, numbers.at(i), diff);
		currentJoltage = numbers.at(i);
		if(diff == 3) {
			threeJolts++;
		} else if(diff == 1) {
			oneJolts++;
		}
		std::printf("%d\n", numbers.at(i));
	}
	currentJoltage += 3;
	threeJolts++;

	std::printf("one jolts %d\n", oneJolts);
	std::printf("three jolts %d\n", threeJolts);
	std::printf("ans %d\n", threeJolts * oneJolts);

	return 0;
}
