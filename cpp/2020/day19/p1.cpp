#include <cmath>
#include <regex>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"

int getMaxNum(std::vector<std::string>& input) {
	int max = 0;
	for(std::string str : input) {
		max = std::max(max, egg::extract_number(str));
	}
	return max;
}

std::string constructRule(std::string r, std::vector<std::string> rules) {
	std::string out = "(";
	if(r.at(1) == 'a') return "a";
	if(r.at(1) == 'b') return "b";
	for(std::size_t i = 0; i < r.size(); i++) {
		if(std::isalnum(r.at(i))) {
			out += constructRule(rules.at(egg::extract_number(r, i)), rules);
		} else if(r.at(i) == '|') {
			out += "|";
		}
	}
	out += ")";

	return out;
}

int main() {
	std::vector<std::string> scrambledRules = egg::read_input_file("testRules.txt");
	std::vector<std::string> messages = egg::read_input_file("testMessages.txt");
	// std::vector<std::string> scrambledRules = egg::read_input_file("rules.txt");
	// std::vector<std::string> messages = egg::read_input_file("messages.txt");
	
	std::vector<std::string> rules;
	rules.resize(getMaxNum(scrambledRules) + 1);

	for(std::string& str : scrambledRules) {
		int index = egg::extract_number(str);
		rules.at(index) = "(" + str.substr(2) + ")";

		if(rules.at(index).at(2) == 'a') {
			rules.at(index) = "(a)";
		} else if(rules.at(index).at(2) == 'b') {
			rules.at(index) = "(b)";
		}
	}

	std::string ruleZero = rules.at(0);
	std::cout << constructRule(ruleZero, rules) << "\n";
	std::regex rx(constructRule(ruleZero, rules));

	int matchCount = 0;
	for(std::string str : messages) {
		if(std::regex_match(str, rx)) matchCount++;
	}

	std::cout << "Match count: " << matchCount << "\n";

	return 0;
}
