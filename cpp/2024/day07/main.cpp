#include <cstdlib>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "../../utils/EggUtils.h"

template <typename T>
void incrementByBase(std::vector<T>& vec, char base) {
	std::size_t i = 0;
	vec.at(i) += 1;
	while(vec.at(i) >= base) {
		vec.at(i) = 0;
		i++;
		if(i == vec.size()) vec.emplace_back(0);
		vec.at(i) += 1;
	}
}

std::uint64_t evaluateOperators(const std::vector<std::uint64_t>& operands, const std::vector<int>& operators) {
	std::uint64_t total = operands.at(0);

	for(std::size_t i = 0; i < operators.size() && i < operands.size() - 1; i++) {
		if(operators.at(i) == 0) {
			// std::cout << "add: " << total << "\n";
			total += operands.at(i + 1);
		} else if (operators.at(i) == 1) {
			// std::cout << "mult: " << total << "\n";
			total *= operands.at(i + 1);
		} else if (operators.at(i) == 2){
			// std::cout << "total: " << total << "\n";
			// std::cout << "operand: " << operands.at(i + 1) << "\n";
			total = (total * std::pow(10, int(std::log10(operands.at(i + 1)) + 1))) + operands.at(i + 1);
			// std::cout << "total: " << total << "\n\n";
		}
	}

	return total;
};

std::uint64_t calibrateEquasion(const std::pair<std::uint64_t, std::vector<std::uint64_t>>& equasion) {
	const std::uint64_t& total = equasion.first;
	const std::vector<std::uint64_t>& operands = equasion.second;
	std::vector<int> operators(operands.size() - 1, 0);
	
	while(evaluateOperators(operands, operators) != total && std::count(operators.begin(), operators.end(), 2) != operators.size()) {
		incrementByBase(operators, 3);
	}

	return (total == evaluateOperators(operands, operators)) ? total : 0;
} 

char* p_end{};

int main() {
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::pair<std::uint64_t, std::vector<std::uint64_t>>> equasions;

	equasions.reserve(input.size());

	for(std::string line : input) { 
		std::size_t colonPos = line.find(':');
		std::uint64_t total = std::strtoull(line.substr(0, colonPos).c_str(), &p_end, 10);
		line.erase(0, colonPos);
		std::vector<std::uint64_t> nums = egg::map(egg::string_split(line.substr(2), " "), [](std::string n){
			return static_cast<std::uint64_t>(std::strtoull(n.c_str(), &p_end, 10));
		});
		equasions.emplace_back(std::make_pair(total, nums));
	} 

	std::uint64_t sum = 0;
	for(const std::pair<std::uint64_t, std::vector<std::uint64_t>>& eq : equasions) {
		sum += calibrateEquasion(eq);
	}
	std::cout << "sum: " << sum << '\n';

	return 0;
}
