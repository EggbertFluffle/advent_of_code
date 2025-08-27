#include <cstdint>
#include <regex>
#include <string>
#include <vector>
#include <array>

#include "../../utils/EggUtils.h"

std::vector<std::string> getMatches(std::string line);
int executeMul(std::string mul);

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::vector<std::string> instructions = egg::regex_get(input.at(0), "(mul\\(\\d+,\\d+\\))|(do\\(\\))|(don't\\(\\))");

	std::int64_t sum = 0;
	bool doing = true;
	for(std::string ins : instructions) {
		if(ins == "do()") {
			doing = true;
		} else if(ins == "don't()") {
			doing = false;
		} else if (doing) {
			sum += executeMul(ins);
		}
	}

	std::cout << "ans: " << sum << "\n";

	return 0;
}

int executeMul(std::string mul) {
	std::vector<int> operands = egg::extract_numbers(mul);

	return operands.at(0) * operands.at(1);
}
