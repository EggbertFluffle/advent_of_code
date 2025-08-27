#include <algorithm>
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

bool CheckPassword(std::string record) {
	int hyphenIndex = record.find_first_of('-');
	int colonIndex = record.find_first_of(':');

	int first = std::stoi(record.substr(0, hyphenIndex)) - 1;
	int second = std::stoi(record.substr(hyphenIndex + 1, colonIndex)) - 1;
	char letter = record.at(colonIndex - 1);

	std::string password = record.substr(colonIndex + 2);

	return ((password.at(first) == letter) ^ (password.at(second) == letter)) ? true : false;
}

int main() {
	// std::vector<std::string> output = ReadInputFile("./inputTest.txt");
	std::vector<std::string> output = ReadInputFile("./input.txt");

	int count;
	std::for_each(output.begin(), output.end(), [&count](std::string p){ count += (CheckPassword(p) ? 1 : 0); });
	std::cout << "Valid passwords: " << count << "\n";

	return 0;
}

