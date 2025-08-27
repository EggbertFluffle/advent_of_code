#include <algorithm>
#include <cstdint>
#include <iterator>
#include <locale>
#include <numeric>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"

void print_disk(const std::vector<int>& disk) {
	for(int i : disk) {
		if(i == -1) {
			std::cout << ".";
		} else {
			std::cout << i;
		}
	}
	std::cout << '\n';
}

std::size_t find_first_empty(const std::vector<int>& disk) {
	return std::distance(disk.begin(), std::find(disk.begin(), disk.end(), -1));
}

bool is_positive(int i) { return i >= 0; }

std::size_t find_last_nonempty(const std::vector<int>& disk) {
	return disk.size() - std::distance(disk.rbegin(), std::find_if(disk.rbegin(), disk.rend(), is_positive)) - 1;
}

int main() {
	std::string input = egg::readInputFile("./input.txt").at(0);
	// std::string input = egg::readInputFile("./inputTest.txt").at(0);

	std::vector<int> diskInformation;
	diskInformation.reserve(input.size());
	for(std::size_t i = 0; i < input.size(); i++) {
		diskInformation.emplace_back(std::stoi(input.substr(i, 1)));
	}

	std::vector<int> disk;
	disk.reserve(std::reduce(diskInformation.begin(), diskInformation.end()));
	int idNumber = 0;
	for(int infoIndex = 0; infoIndex < diskInformation.size(); infoIndex++) {
		for(int i = 0; i < diskInformation.at(infoIndex); i++) {
			disk.emplace_back(infoIndex % 2 == 0 ? infoIndex / 2 : -1);
		}
	}

	std::size_t emptyPos = find_first_empty(disk);
	std::size_t valuePos = find_last_nonempty(disk);
	while(emptyPos < valuePos) {
		disk.at(emptyPos) = disk.at(valuePos);
		disk.at(valuePos) = -1;

		emptyPos = find_first_empty(disk);
		valuePos = find_last_nonempty(disk);
	}

	std::uint64_t sum = 0;
	for(std::uint64_t i = 0; i < disk.size(); i++) {
		std::cout << disk.at(i);
		if(disk.at(i) == -1) continue;
		sum += static_cast<std::uint64_t>(i * disk.at(i));
	}
	std::cout << "sum: " << sum << "\n";

	return 0;
}
