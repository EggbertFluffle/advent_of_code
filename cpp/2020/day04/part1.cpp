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

std::vector<std::string> fields = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

bool IsValid(std::string passport) {
	for(auto& f : fields) {
		if(passport.find(f) > 100000000) {
			return false;
		}
	}
	return true;
}

int main() {
	// std::vector<std::string> output = ReadInputFile("./inputTest.txt");
	std::vector<std::string> output = ReadInputFile("./input.txt");

	int count = 0;
	for(auto& l : output) {
		count += IsValid(l) ? 1 : 0;
	}

	std::cout << "Valid passports: " << count << "\n";

	return 0;
}

