#include <algorithm>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "../../utils/EggUtils.h"

template <typename T, typename R>
bool has_value(R start, R end, T value) {
	for(R it = start; it != end; it++) {
		if(*it == value) return true;
	}
	return false;
}

int isCorrectUpdate(std::vector<std::pair<int, int>>& rules, std::vector<int>& update) {
	for(auto updateNum = update.begin(); updateNum != update.end(); updateNum++) {
		for(auto rule : rules) {
			if(rule.first == *updateNum && std::find(update.begin(), update.end(), rule.second) != update.end()) {
				// Search after
				if(std::find(updateNum, update.end(), rule.second) == update.end()) return 0;
			} else if(rule.second == *updateNum && std::find(update.begin(), update.end(), rule.first) != update.end()) {
				// Seach before
				if(std::find(update.begin(), updateNum, rule.first) == updateNum) return 0;
			}
		}
	}
	return *(update.begin() + (update.size() / 2));
}

int main() {
	std::vector<std::string> rulesInput = egg::readInputFile("./rules.txt");
	std::vector<std::string> updatesInput = egg::readInputFile("./updates.txt");

	// std::vector<std::string> rulesInput = egg::readInputFile("./rulesTest.txt");
	// std::vector<std::string> updatesInput = egg::readInputFile("./updatesTest.txt");

	std::vector<std::pair<int, int>> rules;
	rules.reserve(rulesInput.size());
	std::transform(rulesInput.begin(), rulesInput.end(), std::back_inserter(rules), [](std::string str){
		return std::make_pair<int, int>(std::stoi(str.substr(0, 2)), std::stoi(str.substr(3)));
	});

	std::vector<std::vector<int>> updates;
	updates.reserve(updatesInput.size());
	for(std::string str : updatesInput) {
		updates.emplace_back(egg::extract_numbers(str));
	}

	int sum = 0;
	for(std::vector<int> u : updates) {
		std::cout << "testing: ";
		egg::print_all(u, ", ");
		std::cout << isCorrectUpdate(rules, u) << "\n";
		sum += isCorrectUpdate(rules, u);
	}
	std::cout << "sum: " << sum << "\n";

	return 0;
}
