#include <cctype>
#include <cmath>
#include <set>
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
	std::vector<std::string> parents;
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

void AssignParentBags(std::map<std::string, BagRule>& bagRules) {
	for(auto& [bagRuleName, bagRule] : bagRules) {
		for(auto& [bagRuleEntryCount, bagRuleEntryName]: bagRule.children) {
			if(bagRuleEntryCount != 0) {
				bagRules.at(bagRuleEntryName).parents.push_back(bagRuleName);
			}
		}
	}
}

void PrintAllBagRules(std::map<std::string, BagRule>& bagRulesList) {
	for(auto& [bagName, bagRule] : bagRulesList) {
		std::cout << bagName << " contains: \n";

		std::cout << "Parents:\n";
		for(std::string parentName : bagRule.parents) {
			std::cout << "\t" << parentName << "\n";
		}

		std::cout << "Children:\n";
		for(BagRuleEntry& bagRuleEntry : bagRule.children) {
			std::cout << "\t" << bagRuleEntry.count << "x " << bagRuleEntry.bagName << "\n";
		}
		std::cout << "\n";
	}
}

int CountGoldBagContainers(std::map<std::string, BagRule>& bagRules, std::string bagToCheck, std::set<std::string>& checkedBags) {
	int sum = checkedBags.count(bagToCheck) == 0 ? 1 : 0;
	checkedBags.insert(bagToCheck);
	for(std::string& parentName : bagRules.at(bagToCheck).parents) {
		sum += CountGoldBagContainers(bagRules, parentName, checkedBags);
	}
	return sum;
} 

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::map<std::string, BagRule> bagRulesList = ParseBagRuleList(input);

	AssignParentBags(bagRulesList);

	// PrintAllBagRules(bagRulesList);

	std::set<std::string> checkedBags;
	checkedBags.insert("shiny gold");
	int count = CountGoldBagContainers(bagRulesList, "shiny gold", checkedBags);
	std::cout << "Available bags: " << count << "\n";
	// egg::printAll(bagRulesList.at("shiny gold").parents);

	return 0;
}
