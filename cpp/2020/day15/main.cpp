#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

#include "../../utils/EggUtils.h"

std::uint64_t find_recent_last_number(std::unordered_map<std::uint64_t, std::uint64_t>& numbers, std::uint64_t num) {
	try {
		std::uint64_t ret = numbers.at(num); 
		return ret;
	} catch (std::out_of_range err) {
		throw err;
	}
}

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::unordered_map<std::uint64_t, std::uint64_t> numbers;
	for(std::uint64_t i = 0; i < input.size() - 1; i++) {
		numbers[std::stoi(input.at(i))] = i + 1;
	}

	std::uint64_t count = input.size();
	std::uint64_t currentNumber = std::stoi(input.back());
	while(count != 30000000) {
		try {
			std::uint64_t pos = find_recent_last_number(numbers, currentNumber);
			numbers[currentNumber] = count;
			currentNumber = count - pos;
		} catch (std::out_of_range err){
			numbers[currentNumber] = count;
			currentNumber = 0;
		}

		count++;
	}

	std::printf("Last number: %d\n", currentNumber);

	return 0;
}

// 0, 3, 6, 0, 3, 3, 1, 0, 4, 0
