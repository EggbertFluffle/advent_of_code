#include <cstddef>
#include <vector>
#include <string>
#include <iostream>

#include "../../utils/EggUtils.h"

#define HISTORY_LENGTH 5

long FindBrokenNumber(std::vector<long>& input) {
	int brokenNumber;
	for(int i = HISTORY_LENGTH; i < input.size(); i++) {
		std::cout << "Currently checking: " << input.at(i) << "\n";
		bool numberFound = false;
		for(int j = i - HISTORY_LENGTH; j < i; j++) {
			for(int k = j + 1; k < i; k++) {
				if(input.at(j) + input.at(k) == input.at(i)) {
					numberFound = true;
					break;
				}
				if(numberFound) break;
			}
			if(numberFound) break;
		}
		if(!numberFound) return input.at(i);
	}
	return -1;
}

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::vector<long> numbers;
	for(std::size_t i = 0; i < input.size(); i++) {
		numbers.push_back(std::stol(input.at(i)));
	}

	std::cout << FindBrokenNumber(numbers) << "\n";

	return 0;
}
