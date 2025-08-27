#include <algorithm>
#include <cstddef>
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

	std::sort(rightList.begin(), rightList.end());
	std::sort(leftList.begin(), leftList.end());
	
	int sum = 0;
	for(std::size_t i = 0; i < rightList.size(); i++) {
		int dist = std::abs(rightList.at(i) - leftList.at(i));
		sum += dist;
	}

	std::cout << "sum: " << sum << "\n";

	return 0;
}
