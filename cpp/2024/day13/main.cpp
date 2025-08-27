#include <cmath>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"
#include "../../utils/EggVector.h"

std::uint64_t getMinTokenCount(std::string clawInput) {
	std::vector<int> data = egg::map(egg::string_split(clawInput, ","), [](std::string n){ return std::stoi(n); });

	egg::Vector2<std::uint64_t> aButton = egg::Vector2<std::uint64_t>(data.at(0), data.at(1));
	egg::Vector2<std::uint64_t> bButton = egg::Vector2<std::uint64_t>(data.at(2), data.at(3));
	egg::Vector2<std::uint64_t> prize = egg::Vector2<std::uint64_t>(10000000000000 + data.at(4), 10000000000000 + data.at(5));


	std::int64_t determinant = aButton.x * bButton.y - bButton.x * aButton.y;
	if(determinant == 0) std::cout << "THE DETERMINANT IS ZERO\n";

    std::int64_t determinantA = prize.x * bButton.y - bButton.x* prize.y;
    std::int64_t determinantB = aButton.x * prize.y - prize.x* aButton.y;

	std::cout << "-------------------\n";
	std::cout << clawInput << '\n';
	std::cout << "determinant: " << determinant << "\n";
	std::cout << "determinantA: " << determinantA << "\n";
	std::cout << "determinantB: " << determinantB << "\n";

    std::int64_t a = determinantA / determinant;
    std::int64_t b = determinantB / determinant;

	std::cout << "a: " << a << ", " << "b: " << b << "\n";

	if(aButton * a + bButton * b == prize) {
		return a * 3 + b;
	}
	return 0;
}

int main() {
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");

	std::uint64_t totalTokens = 0;
	for(std::string clawInput : input) {
		std::uint64_t tokenCount = getMinTokenCount(clawInput);
		std::cout << "token count: " << tokenCount << "\n";
		totalTokens += tokenCount;
	}
	std::cout << "totalTokens: " << totalTokens << "\n";

	return 0;
}
