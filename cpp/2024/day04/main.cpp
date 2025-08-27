#include <string>
#include <vector>

#include "../../utils/EggUtils.h"

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	int sum = 0;
	for(std::size_t j = 1; j < input.size() - 1; j++) {
		for(std::size_t i = 1; i < input.size() - 1; i++) {
			sum += egg::regex_get(
				input.at(j - 1).substr(i - 1, 3) + input.at(j).substr(i - 1, 3) + input.at(j + 1).substr(i - 1, 3), 
				"((M.S.A.M.S)|(M.M.A.S.S)|(S.M.A.S.M)|(S.S.A.M.M))").size();
		}
	}

	std::cout << "sum: " << sum << "\n";

	return 0;
}
