#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"

#define HISTORY_LENGTH 25
#define BROKEN_NUMBER 1930745883
// #define BROKEN_NUMBER 127

long SumRange(std::vector<long> &input, std::size_t start, std::size_t end) {
	long sum = 0;
	for (std::size_t i = start; i < end; i++) {
		sum += input.at(i);
	}
	return sum;
}

void PrintRange(std::vector<long> input, std::size_t start, std::size_t end) {
	for (std::size_t i = start; i < end; i++) {
		std::printf("%d: %li\n", i, input.at(i));
	}
}

long FindNumberRange(std::vector<long> &input) {
	for (std::size_t i = 0; i < input.size() - 1; i++) {
		for (std::size_t j = i + 1; j < input.size(); j++) {
			if (SumRange(input, i, j) == BROKEN_NUMBER) {
				std::for_each(input.begin() + i, input.begin() + j, [](long& l){ std::printf("%ld\n", l); });
				
				return *(std::min_element(input.begin() + i, input.begin() + j)) +
					*(std::max_element(input.begin() + i, input.begin() + j));
			}
		}
	}
	return 0;
}

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::vector<long> numbers;
	for (std::size_t i = 0; i < input.size(); i++) {
		long num = std::stol(input.at(i));
		if (num == BROKEN_NUMBER)
			break;
		numbers.emplace_back(num);
	}

	std::printf("Answer: %ld\n", FindNumberRange(numbers));

	return 0;
}
