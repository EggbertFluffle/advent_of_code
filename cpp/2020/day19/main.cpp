#include <algorithm>
#include <cmath>
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
		switch(r.at(i)) {
			case '|':
				out += "|";
				break;
			case '*':
				out += "*";
				break;
			case '}':
				out += "}";
				break;
			case '{':
				out += "{";
				break;
			case 'N':
				out += "N";
				break;
			case '.':
				out += ".";
				break;
			default:
				if(std::isalnum(r.at(i))) {
					out += constructRule(rules.at(egg::extract_number(r, i)), rules);
				}
				break;
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
	std::string rule42 = rules.at(42);
	std::string rule31 = rules.at(31);

	rules.at(8) = "42+";
	// 42 31 | 42 11 31
	std::string ruleEleven = "( . * )";
	rules.at(11) = ruleEleven;

	std::cout << "RULE ELEVEN\n";
	std::string ruleZeroBase = constructRule(ruleZero, rules);
	std::cout << ruleZeroBase << "\n";

	std::cout << "\nRULE FORTY TWO\n";
	std::string rule42Base = constructRule(rule42, rules);
	std::cout << rule42Base  << "\n";

	std::cout << "\nRULE THIRTY ONE\n";
	std::string rule31Base = constructRule(rule31, rules);
	std::cout << rule31Base  << "\n";

	return 0;
}
