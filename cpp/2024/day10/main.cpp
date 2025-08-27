#include <array>
#include <cstddef>
#include <stdexcept>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "../../utils/EggVector.h"
#include "../../utils/EggUtils.h"

void testDir(const std::vector<std::vector<int>>& grid, egg::Vector2i pos, egg::Vector2i dir, std::array<int, 9> trail);
void testTrail(const std::vector<std::vector<int>>& grid, egg::Vector2i pos, std::array<int, 9> trail);

std::set<std::array<int, 9>> uniqueDirections;

int dtoi(egg::Vector2i dir) {
	if(dir.equals(egg::Vector2i(0, -1))) {
		return 0;
	} else if(dir.equals(egg::Vector2i(1, 0))) {
		return 1;
	} else if(dir.equals(egg::Vector2i(0, 1))) {
		return 2;
	} else if(dir.equals(egg::Vector2i(-1, 0))) {
		return 3;
	}
	return -1;
}

void testDir(const std::vector<std::vector<int>>& grid, egg::Vector2i pos, egg::Vector2i dir, std::array<int, 9> trail) {
	egg::Vector2i newVec = pos + dir;
	try {
		if(grid.at(newVec.y).at(newVec.x) == (grid.at(pos.y).at(pos.x) + 1)) {
			std::cout << "before: " << grid.at(pos.y).at(pos.x) << "\n";
			std::cout << "after: " << grid.at(newVec.y).at(newVec.x) << "\n";
			trail.at(grid.at(pos.y).at(pos.x)) = dtoi(dir);
			egg::print_all(trail, ", ");
			testTrail(grid, newVec, trail);
		}
	} catch(std::out_of_range) {}
}

void testTrail(const std::vector<std::vector<int>>& grid, egg::Vector2i pos, std::array<int, 9> trail) {
	if(grid.at(pos.y).at(pos.x) == 9) uniqueDirections.insert(trail);

	testDir(grid, pos, egg::Vector2i(0, -1), trail);
	testDir(grid, pos, egg::Vector2i(1, 0), trail);
	testDir(grid, pos, egg::Vector2i(0, 1), trail);
	testDir(grid, pos, egg::Vector2i(-1, 0), trail);
}


int main() {
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");

	std::vector<std::vector<int>> grid;
	std::vector<egg::Vector2i> trailheads;
	grid.reserve(input.size());
	for(std::size_t i = 0; i < input.size(); i++) {
		std::vector<int> out;
		out.reserve(input.at(i).size());
		for(std::size_t j = 0; j < input.at(i).size(); j++) {
			if(input.at(i).at(j) == '0') trailheads.emplace_back(egg::Vector2i(j, i));
			out.emplace_back(std::stoi(input.at(i).substr(j, 1)));
		}
		grid.emplace_back(out);
	}

	int sum = 0;
	for(egg::Vector2i v : trailheads) {
		testTrail(grid, v, std::array<int, 9>());
		sum += uniqueDirections.size();
		uniqueDirections.clear();
	}
	std::cout << "sum: " << sum << "\n";

	return 0;
}
