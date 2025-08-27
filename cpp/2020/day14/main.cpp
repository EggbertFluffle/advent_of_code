#include <cstdint>
#include <string>
#include <sys/types.h>
#include <bitset>
#include <unordered_map>
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
			address = std::bitset<36>(std::stoi(line.substr(4, endOfAddress))).to_string();
			number = std::stoi(line.substr(endOfAddress + 4));
		}
	}

	bool isMask;
	std::string bitMask;

	std::string address;
	uint number;
};

std::vector<Instruction> parseInstructions(std::vector<std::string>& input) {
	std::vector<Instruction> out;
	for(std::string& str : input) {
		Instruction newInstruction(str);
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

void sinkBitMask(std::string mask, std::vector<std::bitset<36>>& maskList) {
	if(mask.find_first_of('X') == std::string::npos) {
		maskList.push_back(std::bitset<36>(mask));
		return;
	} else {
		std::size_t floatingBitPos = mask.find_first_of('X');
		sinkBitMask(mask.replace(floatingBitPos, 1, "1"), maskList);
		sinkBitMask(mask.replace(floatingBitPos, 1, "0"), maskList);
	}
}

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	
	std::vector<Instruction> instructionList = parseInstructions(input);

	std::unordered_map<uint64_t, uint64_t> memory;

	std::string baseBitMask;
	for(Instruction instruction : instructionList) {
		if(instruction.isMask) {
			baseBitMask = instruction.bitMask;
		} else {
			std::string floatingAddress;
			floatingAddress.resize(36);
			for(std::size_t i = 0; i < floatingAddress.size(); i++) {
				switch(baseBitMask.at(i)) {
					case '1':
						floatingAddress[i] = '1';
						break;
					case 'X':
						floatingAddress[i] = 'X';
						break;
					default:
						floatingAddress[i] = instruction.address[i];
						break;
				}
			}
			std::vector<std::bitset<36>> bitMaskList;
			sinkBitMask(floatingAddress, bitMaskList);
			for(std::bitset<36> btmsk : bitMaskList) {
				memory[btmsk.to_ulong()] = instruction.number;
			}
		}
	}

	std::uint64_t sum;
	for(auto num : memory) {
		sum += num.second;
	}

	std::cout << "Value: " << sum << "\n";

	return 0;
}
