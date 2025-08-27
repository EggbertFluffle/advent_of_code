#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <array>

std::vector<std::string> ReadInputFile(std::string name) {
	std::fstream stream(name);
	if(!stream.is_open()) std::cout << "File name \"" << name << "\" cannot be found!\n";

	std::vector<std::string> lines;
	while (stream.good()) {
		std::string l;
		std::getline(stream, l);
		lines.push_back(l);
	}
	lines.pop_back();
	return lines;
}

std::bitset<26> GetLetterBitset(std::string str) {
	std::bitset<26> letters;
	for(char c : str) {
		letters.set(c - 97, true);
	}
	return letters;
}

int main() {
	// std::vector<std::string> output = ReadInputFile("./inputTest.txt");
	std::vector<std::string> output = ReadInputFile("./input.txt");

	// Keep track of a map of all the letters
	std::array<std::bitset<26>, 26> LETTERMAP;
	for(std::size_t i = 0; i < LETTERMAP.size(); i++) {
		LETTERMAP.at(i).reset();
		LETTERMAP.at(i).set(i, true);
	}

	int sum = 0;
	std::bitset<26> currentLetters;
	currentLetters.set();
	for(std::string str : output) {
		if(str.empty()) {
			sum += currentLetters.count();
			currentLetters.set();
		} else {
			currentLetters = currentLetters & GetLetterBitset(str);;
		}
	}

	std::cout << "sum: " << sum << "\n";

	return 0;
}
