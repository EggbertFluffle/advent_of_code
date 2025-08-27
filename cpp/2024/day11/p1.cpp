#include <cmath>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

#include "../../utils/EggUtils.h"

void blink(std::vector<std::uint64_t>& stones) {
	for(std::size_t pos = 0; pos < stones.size(); pos++) {
		std::uint64_t s = stones.at(pos);

		if(s == 0) {
			stones.at(pos) = 1;
			continue;
	 	}

		std::size_t digits = std::floor(std::log10(s) + 1);
		if(digits % 2 == 0) {
			std::uint64_t first = static_cast<std::uint64_t>(std::floor(s / std::pow(10, digits / 2)));

			stones.at(pos) = s - first * std::pow(10, digits / 2);
			stones.insert(stones.begin() + pos, first);
			pos++;
		} else {
			stones.at(pos) *= 2024;
		}
	}
}

int main() {
	std::vector<std::string> input = egg::string_split(egg::readInputFile("./input.txt").at(0), " ");
	// std::vector<std::string> input = egg::string_split(egg::readInputFile("./inputTest.txt").at(0), " ");

	std::vector<std::uint64_t> stones = egg::map(input, [](std::string str){ return static_cast<std::uint64_t>(std::stoi(str)); });

	for(int i = 0; i < 75; i++) {
		std::cout << i << "/" << "75 | " << stones.size() << "\n";
		blink(stones);
	}

	std::cout << "stone length: " << stones.size() << "\n";

	return 0;
}
