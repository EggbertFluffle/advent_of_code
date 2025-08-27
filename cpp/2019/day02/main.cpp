#include <string>
#include <vector>

#include "../../utils/EggUtils.h"

int main() {
	std::vector<std::string> input = egg::string_split(egg::readInputFile("./input.txt").at(0), ",");
	// std::vector<std::string> input = egg::string_split(egg::readInputFile("./inputTest.txt").at(0), ",");

	std::vector<int> program = egg::map(input, [](std::string str){ return std::stoi(str); });

	program.at(1) = 12;
	program.at(2) = 2;

	bool leaveLoop = false;
	for(std::size_t pos = 0; pos < program.size() && !leaveLoop; pos += 4) {
		// std::cout << "opcode: " << program.at(pos) << "\n";
		// std::cout << "arg1: " << program.at(pos + 1) << "\n";
		// std::cout << "arg2: " << program.at(pos + 2) << "\n";
		// std::cout << "retpos: " << program.at(pos + 3) << "\n";
		switch(program.at(pos)) {
			case 1:
				program.at(program.at(pos + 3)) = program.at(program.at(pos + 1)) + program.at(program.at(pos + 2));
				break;
			case 2:
				program.at(program.at(pos + 3)) = program.at(program.at(pos + 1)) * program.at(program.at(pos + 2));
				break;
			case 99:
				leaveLoop = true;
				break;
		}
	}

	std::cout << "out: " << program.at(0) << "\n";

	return 0;
}
