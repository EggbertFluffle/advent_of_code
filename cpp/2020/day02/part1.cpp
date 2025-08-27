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

	int countFloor = std::stoi(record.substr(0, hyphenIndex));
	int countCeil = std::stoi(record.substr(hyphenIndex + 1, colonIndex));
	char letter = record.at(colonIndex - 1);

	std::string password = record.substr(colonIndex + 2);

	std::string::difference_type count = std::count(password.begin(), password.end(), letter);

	return (count <= countCeil) && (count >= countFloor);
}

int main() {
	// std::vector<std::string> output = ReadInputFile("./inputTest.txt");
	std::vector<std::string> output = ReadInputFile("./input.txt");

	int count;
	std::for_each(output.begin(), output.end(), [&count](std::string p){ count += (CheckPassword(p) ? 1 : 0); });
	std::cout << "Valid passwords: " << count << "\n";

	return 0;
}

