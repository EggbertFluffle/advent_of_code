#include <cmath>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

#include "../../utils/EggUtils.h"

struct Stone {
	std::uint64_t digit;
	std::size_t quantity;
	std::uint64_t first;
	std::uint64_t second;
	std::size_t digits;
	bool evenDigits;

	Stone(std::uint64_t num, std::size_t _quantity = 1) : digit(num), quantity(_quantity) {
		digits = static_cast<std::uint64_t>(std::floor(std::log10(num)) + 1);
		evenDigits = digits % 2 == 0;

		if(num == 0) {
			first = 1;
		} else if(evenDigits) {
			first = static_cast<std::uint64_t>(std::floor(num / std::pow(10, digits / 2)));
			second = digit - first * std::pow(10, digits / 2);
		} else if(!evenDigits) {
			first = digit * static_cast<std::uint64_t>(2024);
		}
	}

	void blooooooorp(std::map<std::uint64_t, Stone>& stones) {
		if(stones.count(first) == 0) {
			stones.insert(std::make_pair(first, Stone(first, quantity)));
		} else {
			stones.at(first).quantity += quantity;
		}

		if(evenDigits && digit != 0) {
			if(stones.count(second) == 0) {
				stones.insert(std::make_pair(second, Stone(second, quantity)));
			} else {
				stones.at(second).quantity += quantity;
			}
		}
	}
};

std::map<std::uint64_t, Stone> blink(std::map<std::uint64_t, Stone>& stones) {
	std::map<std::uint64_t, Stone> out;
	for(auto& p : stones) {
		p.second.blooooooorp(out);
	}
	return out;
}


int main() {
	std::vector<std::string> input = egg::string_split(egg::readInputFile("./input.txt").at(0), " ");
	// std::vector<std::string> input = egg::string_split(egg::readInputFile("./inputTest.txt").at(0), " ");

	std::map<std::uint64_t, Stone> stones;
	for(std::string str : input) {
		std::uint64_t num = static_cast<std::uint64_t>(std::stoi(str));
		stones.insert(std::make_pair(num, Stone(num)));
	}

	for(int i = 0; i < 100000; i++) {
		stones = blink(stones);
		std::uint64_t sum = 0;
		for(auto& p : stones) {
			sum++;
		}
		std::cout << i << " -> " << sum << "\n";
		if(sum == 3811) break;
	}
	return 0;
}
