#include <cctype>
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

std::string GetField(std::string& passport, std::string fieldName) {
	int fieldIndex = passport.find(fieldName);
	int fieldEnd = passport.find_first_of("-", fieldIndex);
	std::string fieldValue = passport.substr(fieldIndex + 4, fieldEnd - fieldIndex - 4);

	return fieldValue;
}

bool IsValid(std::string& passport) {
	bool DEBUG = 0;

	for(auto& f : fields) {
		if(passport.find(f) > 100000000) return false;
	}

	// Chceck byr
	std::string byr = GetField(passport, "byr");
	if(byr.size() != 4) return false;
	int byri = std::stoi(byr);
	if(byri < 1920 || byri > 2002) return false;
	if(DEBUG) std::cout << "BYR passed!\n";

	// Chceck iyr
	std::string iyr = GetField(passport, "iyr");
	if(iyr.size() != 4) return false;
	int iyri = std::stoi(iyr);
	if(iyri < 2010 || iyri > 2020) return false;
	if(DEBUG) std::cout << "IYR passed!\n";

	// Check eyr
	std::string eyr = GetField(passport, "eyr");
	if(eyr.size() != 4) return false;
	int eyri = std::stoi(eyr);
	if(eyri < 2010 || eyri > 2030) return false;
	if(DEBUG) std::cout << "EYR passed!\n";

	// Check hgt
	std::string hgt = GetField(passport, "hgt");
	std::string unit = hgt.substr(hgt.size() - 2, 2);
	if(unit.compare("in") == 0) {
		// Handle inches
		hgt.pop_back();
		hgt.pop_back();
		int val = std::stoi(hgt);
		if(val < 59 || val > 76) return false;
	} else if(unit.compare("cm") == 0) {
		// Handle centimeters
		hgt.pop_back();
		hgt.pop_back();
		int val = std::stoi(hgt);
		if(val < 150 || val > 193) return false;
	} else {
		// Invalid
		std::cout << "Improper format for HGT found!\n";
		return false;
	}
	if(DEBUG) std::cout << "HGT passed!\n";

	// Check hcl
	std::string hcl = GetField(passport, "hcl");
	if(hcl.size() != 7) return false;
	if(hcl.at(0) != '#') return false;
	std::string validCharacters = "0123456789abcdef";


	// Woudl have been cool to use std::isdigit and std::isalhpa
	for(int i = 1; i < hcl.size(); i++) {
		std::string search = hcl.substr(i, 1); 
		if(validCharacters.find(search) > 100000000) return false;
	}

	if(DEBUG) std::cout << "HCL passed!\n";

	// Chceck ecl
	std::vector<std::string> validEyeColors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
	std::string ecl = GetField(passport, "ecl");
	if(ecl.size() != 3) return false;
	bool containsValid = false;
	for(auto& c : validEyeColors) {
		if(c.compare(ecl) == 0) {
			containsValid = true;
			break;
		}
	}
	if(!containsValid) return false;
	if(DEBUG) std::cout << "ECL passed!\n";

	// Check pid
	std::string pid = GetField(passport, "pid");
	if(pid.size() != 9) return false;
	std::string validNums = "0123456789";
	for(int i = 0; i < pid.size(); i++) {
		std::string testNum = pid.substr(i, 1);
		if(validNums.find_first_of(testNum) > 100000000) return false;
	}
	if(DEBUG) std::cout << "PID passed!\n";

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

