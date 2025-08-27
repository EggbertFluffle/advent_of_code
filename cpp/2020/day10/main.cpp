#include <cstdint>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

#include "../../utils/EggUtils.h"

std::map<int, std::int64_t> cache;

std::int64_t FindAdapterSum(std::vector<int>& numbers, int currentJoltage, std::size_t index) {
	std::int64_t sum = 0;

	for(int check = 1; index + check < numbers.size() && check <= 3; check++) {
		if(numbers.at(index + check) - currentJoltage <= 3) {
			sum += cache.at(numbers.at(index + check));
		}
	}

	return sum;
}

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	// Convert input to numbers and sort
	std::vector<int> numbers;
	numbers.reserve(input.size());
	for(std::string& str : input) {
		numbers.emplace_back(std::stol(str));
	}
	numbers.emplace_back(0);
	std::sort(numbers.begin(), numbers.end());
	numbers.emplace_back(numbers.back() + 3);

	cache[numbers.back()] = 1;

	std::for_each(numbers.begin(), numbers.end(), [](int i){ std::printf("%d\n", i); });

	for(std::size_t i = numbers.size() - 2; i > 0; i--) {
		cache[numbers.at(i)] = FindAdapterSum(numbers, numbers.at(i), i);
	}

	std::printf("print map of caches\n");
	for(auto& [key, value] : cache) {
		std::printf("key: %d | val: %d\n", key, value);
	}
	
	std::cout <<  "answer: " << FindAdapterSum(numbers, 0, 0) << "\n";

	return 0;
}
