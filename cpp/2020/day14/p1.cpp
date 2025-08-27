#include <algorithm>
#include <string>
#include <sys/types.h>
#include <bitset>
#include <vector>

#include "../../utils/EggUtils.h"

struct Instruction {
	Instruction(std::string& line) {
		if(line.at(1) == 'a') {
			// Initializing a mask
			isMask = true;
			bitMask = line.substr(7);
		} else {
			// Initializing a memory write
			isMask = false;
			
			std::size_t endOfAddress = line.find_first_of(']');
			address = std::stoi(line.substr(4, endOfAddress));
			number = std::bitset<36>(std::stoi(line.substr(endOfAddress + 4)));
		}
	}

	bool isMask;
	std::string bitMask;
	uint address;
	std::bitset<36> number;
};

std::vector<Instruction> parseInstructions(std::vector<std::string>& input, uint& maxAddress) {
	std::vector<Instruction> out;
	for(std::string& str : input) {
		Instruction newInstruction(str);
		if(!newInstruction.isMask) {
			maxAddress = std::max(maxAddress, newInstruction.address);
		}
		out.emplace_back(newInstruction);
	}
	return out;
}

std::bitset<36> putBitsAt(std::string model, char toConvert) {
	std::bitset<36> out;
	std::size_t pos = 0;
	for(auto c = model.rbegin(); c != model.rend(); c++) {
		out.set(pos, (*c == toConvert) ? 1 : 0);
		pos++;
	}
	return out;
}

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	
	uint maxAddress = 0;
	std::vector<Instruction> instructionList = parseInstructions(input, maxAddress);

	std::vector<std::bitset<36>> memory;
	memory.resize(maxAddress + 1);

	std::string baseBitMask;
	std::bitset<36> zeroMask;
	std::bitset<36> oneMask;
	for(Instruction instruction : instructionList) {
		if(instruction.isMask) {
			baseBitMask = instruction.bitMask;
			zeroMask = putBitsAt(baseBitMask, '0').flip();
			oneMask = putBitsAt(baseBitMask, '1');
		} else { // Instruction mem
			memory[instruction.address] = (oneMask | instruction.number) & zeroMask;
			// std::printf("-------------------------\n");
			// std::cout << "msk: " << baseBitMask << "\n";
			// std::cout << "num: " << instruction.number << "\n";
			// std::cout << "one: " << oneMask << "\n";
			// std::cout << "or : " << (oneMask | instruction.number) << "\n";
			// std::cout << "mem: " << memory[instruction.address] << "\n";
		}
	}
	
	ulong sum = 0;

	// std::cout << "-----------OUTPUT-----------\n";
	// for(std::bitset<36> set : memory) {
	// 	std::cout << set << '\n';
	// }

	std::cout << "-----------OUTPUT-----------\n";
	for(std::bitset<36> val : memory) {
		// std::cout << val.to_ulong() << "\n";
		if(val.any()) {
			sum += val.to_ulong();
		}
	}

	std::cout << "value: " << sum << "\n";

	return 0;
}
