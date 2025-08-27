#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::vector<int> rightList;
	std::vector<int> leftList;
	rightList.reserve(input.size());
	leftList.reserve(input.size());

	for(std::string line : input) {
		std::vector<std::string> nums = egg::string_split(line, "   ");
		leftList.emplace_back(std::stoi(nums.at(0)));
		rightList.emplace_back(std::stoi(nums.at(1)));
	}

	std::uint64_t sum = 0;
	for(std::size_t i = 0; i < rightList.size(); i++) {
		auto times = std::count(rightList.begin(), rightList.end(), leftList.at(i));
		sum += leftList.at(i) * times;
	}

	std::cout << "sum: " << sum << "\n";

	return 0;
}
