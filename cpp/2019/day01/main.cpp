#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

#include "../../utils/EggVector.h"
#include "../../utils/EggUtils.h"

int calculateFuel(int mass) {
	return static_cast<std::uint64_t>(std::floor(mass / 3.0f) - 2);
}

int main() {
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");

	std::vector<int> masses = egg::map(input, [](std::string str){ return std::stoi(str); });

	std::uint64_t sum = 0;
	for(int m : masses) {
		int fuel = calculateFuel(m);
		while(fuel > 0) {
			sum += fuel;
			fuel = calculateFuel(fuel);
		}
	}
	std::cout << "sum: " << sum;

	return 0;
}
