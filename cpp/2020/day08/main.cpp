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
		if(instruction == instructionList.size()) {
			return acc;
		}
	}

	return -1;
}

int FollowPermutatedInstructions(std::vector<std::vector<Instruction>>& instructionListPermutations) {
	for(std::vector<Instruction>& permutatedList : instructionListPermutations) {
		int permutatedListAcc = FollowInstructions(permutatedList);
		if(permutatedListAcc != -1) {
			return permutatedListAcc;
		}
	}

	return  -1;
}

std::vector<std::vector<Instruction>> PermutateInstructionList(std::vector<Instruction>& input) {
	std::vector<std::vector<Instruction>> out;
	for(int i = 0; i < input.size(); i++) {
		if(input.at(i).type != ACC) {
			std::vector<Instruction> newInstructionList = input;
			newInstructionList.at(i).type = newInstructionList.at(i).type == JMP ? NOP : JMP;
			out.push_back(newInstructionList);
		}
	}
	return out;
}

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::vector<Instruction> instructionList = ParseInstructions(input);
	std::vector<std::vector<Instruction>> instructionListPermutations = PermutateInstructionList(instructionList);

	int acc = FollowPermutatedInstructions(instructionListPermutations);
	std::cout << "acc: " << acc << "\n";

	return 0;
}

