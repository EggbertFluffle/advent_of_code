#include <algorithm>
#include <iterator>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "../../utils/EggUtils.h"

struct FileBlock {
	FileBlock(std::size_t _size, bool _empty, int _id) : 
		size(_size),
		empty(_empty),
		id(_id) {}
	
	std::size_t size;
	bool empty;
	int id;
};

void print_disk(const std::vector<FileBlock>& disk) {
	for(FileBlock fb : disk) {
		for(std::size_t i = 0; i < fb.size; i++) {
			if(fb.empty) {
				std::cout << ".";
			} else {
				std::cout << fb.id;
			}
		}
	}
	std::cout << "\n";
}

bool is_empty(FileBlock p) { return p.empty; }
bool is_nonempty(FileBlock p) { return !p.empty; }

std::size_t find_file(const std::vector<FileBlock>& disk, std::size_t start) {
	for(std::size_t i = start; i >= 0; i--) {
		if(is_nonempty(disk.at(i))) {
			return i;
		}
	}
	return 0;
}

std::size_t compress_empty_blocks(std::vector<FileBlock>& disk) {
	std::size_t compressions = 0;
	for(std::size_t i = 0; i < disk.size() - 1; i++) {
		if(disk.at(i).empty && disk.at(i + 1).empty) {
			compressions++;
			disk.at(i).size += disk.at(i + 1).size;
			disk.erase(disk.begin() + i + 1);
			i--;
		}
	}
	if(disk.back().empty) {
		compressions++;
		disk.erase(disk.end()--);
	}
	return compressions;
}

std::size_t find_large_enough_empty_block(const std::vector<FileBlock>& disk, std::size_t end) {
	for(std::size_t i = 0; i < end; i++) {
		if(disk.at(i).empty && disk.at(i).size >= disk.at(end).size) return i;
	}
	return 0;
}

int main() {
	std::string input = egg::readInputFile("./input.txt").at(0);
	// std::string input = egg::readInputFile("./inputTest.txt").at(0);

	std::vector<FileBlock> disk;
	disk.reserve(input.size());
	for(std::size_t i = 0; i < input.size(); i++) {
		FileBlock p = FileBlock(std::stoi(input.substr(i, 1)), i % 2 == 1, i / 2);
		disk.emplace_back(p);
	}

	try {
		std::set<int> idCounter;
		for(std::size_t i = disk.size() - 1; i >= 0; i--) {
			if(disk.at(i).empty || idCounter.count(disk.at(i).id) != 0) continue;
			// print_disk(disk);
			std::size_t parking = find_large_enough_empty_block(disk, i);
			if(parking == 0) continue;
			idCounter.insert(disk.at(i).id);
			disk.at(parking).size -= disk.at(i).size;
			disk.insert(disk.begin() + parking, disk.at(i));
			parking++;
			i++;
			disk.at(i).empty = true;
			compress_empty_blocks(disk);
			if(i > disk.size()) i = disk.size();
		}
	} catch(std::out_of_range err) {}

	std::vector<int> REALDISK;
	for(FileBlock fb : disk) {
		for(std::size_t i = 0; i < fb.size; i++) {
			if(fb.empty) {
				REALDISK.emplace_back(-1);
			} else {
				REALDISK.emplace_back(fb.id);
			}
		}
	}

	std::uint64_t sum = 0;
	for(std::uint64_t i = 0; i < REALDISK.size(); i++) {
		if(REALDISK.at(i) == -1) continue;
		sum += static_cast<std::uint64_t>(i * REALDISK.at(i));
	}
	std::cout << "sum: " << sum << "\n";

	return 0;
}
