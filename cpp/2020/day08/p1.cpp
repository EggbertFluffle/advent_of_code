#include <cmath>
#include <vector>
#include <set>
#include <string>

#include "../../utils/EggUtils.h"

#define ACC 1
#define JMP 2
#define NOP 3

struct Instruction {
	int type;
	int argument;
};

std::vector<Instruction> ParseInstructions(std::vector<std::string>& input) {
	std::vector<Instruction> out;
	for(std::string str : input) {
		Instruction instruction;
		std::string t = str.substr(0, 3);
		instruction.type = (t == "acc") ? ACC : (t == "jmp") ? JMP : NOP;

		instruction.argument = std::stoi(str.substr(4));
		out.push_back(instruction);
	}
	return out;
}

int FollowInstructions(std::vector<Instruction>& instructionList) {
	std::set<std::size_t> visitedInstructions;
	int instruction = 0;
	int acc = 0;

	while(visitedInstructions.count(instruction) != 1) {
		visitedInstructions.insert(instruction);
		std::cout << "instruction: " << instruction << "\n";
		switch(instructionList.at(instruction).type) {
			case ACC:
				acc += instructionList.at(instruction).argument;
				instruction++;
				break;
			case JMP:
				instruction += instructionList.at(instruction).argument;
				break;
			default:
				instruction++;
				break;
		}
	}

	return acc;
}

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::vector<Instruction> instructionList = ParseInstructions(input);
	std::cout << "size of instruction list: " << instructionList.size() << "\n";

	int acc = FollowInstructions(instructionList);
	std::cout << "acc: " << acc << "\n";

	return 0;
}

