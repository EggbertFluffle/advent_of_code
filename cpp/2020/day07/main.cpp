#include <cctype>
#include <cmath>
#include <vector>
#include <string>
#include <map>

#include "../../utils/EggUtils.h"

struct BagRuleEntry {
	int count;
	std::string bagName;
};

struct BagRule {
	std::vector<BagRuleEntry> children;
};

std::map<std::string, BagRule> ParseBagRuleList(std::vector<std::string> input) {
	std::map<std::string, BagRule> bagRules;

	for(std::string str : input) {
		std::string bagName = str.substr(0, str.find_first_of(","));
		str.erase(0, bagName.size() + 1);

		std::vector<std::string> bagContentsStr = egg::stringSplit(str, ",");
		BagRule bagRule;

		for(std::string b : bagContentsStr) {
			int i = std::stoi(b.substr(0, 1));
			bagRule.children.push_back({i, i == 0 ? "" : b.substr(2)});
		}
		bagRules.insert({bagName, bagRule});
	}

	return bagRules;
}


int CountTotalInsideBag(std::map<std::string, BagRule>& bagRules, std::string bagToCheck) {
	int sum = 0;
	for(auto& [childBagCount, childBagName] : bagRules.at(bagToCheck).children) {
		if(childBagCount == 0) break;
		sum += childBagCount + (childBagCount * CountTotalInsideBag(bagRules, childBagName));
	}
	return sum;
} 

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::map<std::string, BagRule> bagRulesList = ParseBagRuleList(input);

	std::cout << "Available bags: " << CountTotalInsideBag(bagRulesList, "shiny gold") << "\n";

	return 0;
}

void PrintAllBagRules(std::map<std::string, BagRule>& bagRulesList) {
	for(auto& [bagName, bagRule] : bagRulesList) {
		std::cout << bagName << " contains: \n";

		std::cout << "Children:\n";
		for(BagRuleEntry& bagRuleEntry : bagRule.children) {
			std::cout << "\t" << bagRuleEntry.count << "x " << bagRuleEntry.bagName << "\n";
		}
		std::cout << "\n";
	}
}
