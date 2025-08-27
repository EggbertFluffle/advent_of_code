#include <bitset>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

int GetSeatId(std::string boardingpass) {
	int row = std::stoi(boardingpass.substr(0, 7), nullptr, 2);
	int col = std::stoi(boardingpass.substr(8), nullptr, 2);
	return row * 8 + col;
}

int main() {
	// std::vector<std::string> output = ReadInputFile("./inputTest.txt");
	std::vector<std::string> output = ReadInputFile("./input.txt");

	std::bitset<832> seats;
	for(std::size_t i = 0; i < seats.size(); i++) {
		seats.set(i, 0);
	}

	int highest = 0;
	for(std::string str : output) {
		int id = GetSeatId(str);
		seats[id] = true;
		highest = std::max(id, highest);
	}

	for(std::size_t i = 0; i < seats.size(); i++) {
		std::cout << "Seat " << i << ": " << (seats[i] ? "$$" : "[]") << "\n";
	}

	std::cout << "Highest : " << highest << "\n";

	return 0;
}

