#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"
#include "../../utils/EggVector.h"

int main() {
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");

	std::unordered_map<char, std::vector<egg::Vector2i>> antennae;

	for(int i = 0; i < input.size(); i++) {
		for(int j = 0; j < input.at(i).size(); j++) {
			if(input.at(i).at(j) != '.') {
				if(antennae.count(input.at(i).at(j)) == 0) {
					antennae[input.at(i).at(j)] = std::vector<egg::Vector2i>();
					antennae[input.at(i).at(j)].emplace_back(egg::Vector2i(j, i));
				} else {
					antennae[input.at(i).at(j)].emplace_back(egg::Vector2i(j, i));
				}
			}
		}
	}

	std::vector<std::vector<std::string>> map = egg::create_2d_vector<std::string>(input.at(0).size(), input.size());
	for(const std::pair<char, std::vector<egg::Vector2i>> p : antennae) {
		const std::vector<egg::Vector2i>& ants = p.second;
		for(std::size_t i = 0; i < ants.size(); i++) {
			for(std::size_t j = i + 1; j < ants.size(); j++) {
				egg::Vector2i first = (ants.at(i) - ants.at(j)) + ants.at(i);
				egg::Vector2i second = (ants.at(j) - ants.at(i)) + ants.at(j);
				try {
					map.at(first.y).at(first.x).push_back(p.first);
				} catch (std::out_of_range err) {}

				try {
					map.at(second.y).at(second.x).push_back(p.first);
				} catch (std::out_of_range err) {}
			}
		}
	}

	int sum = 0;
	for(std::vector<std::string> row : map) {
		for(std::string cell : row) {
			if(cell.size() != 0) {
				sum++;
			}
		}
	}
	std::cout << "sum: " << sum << "\n";

	return 0;
}
