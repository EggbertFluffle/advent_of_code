#include <cmath>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <set>

#include "../../utils/EggUtils.h"
#include "../../utils/EggVector.h"

void growRegion(std::vector<std::vector<char>>& garden, std::vector<egg::Vector2i>& availablePlants, std::vector<egg::Vector2i>& plants, char& plantType, egg::Vector2i pos);

void growDir(
	std::vector<std::vector<char>>& garden,
	std::vector<egg::Vector2i>& availablePlants,
	std::vector<egg::Vector2i>& plants,
	char& plantType,
	egg::Vector2i pos,
	egg::Vector2i dir
) {
	egg::Vector2i newPos = pos + dir;
	try {
		std::vector<egg::Vector2i>::iterator erase;

		// std::cout << std::count(availablePlants.begin(), availablePlants.end(), egg::Vector2i(newPos)) << "\n";
		if(garden.at(newPos.y).at(newPos.x) == plantType && std::count(availablePlants.begin(), availablePlants.end(), egg::Vector2i(newPos)) != 0)  {
			availablePlants.erase(std::find(availablePlants.begin(), availablePlants.end(), newPos));
			plants.emplace_back(newPos);
			growRegion(garden, availablePlants, plants, plantType, newPos);
		}
	} catch(std::out_of_range err) {}
}

void growRegion(std::vector<std::vector<char>>& garden, std::vector<egg::Vector2i>& availablePlants, std::vector<egg::Vector2i>& plants, char& plantType, egg::Vector2i pos) {
	growDir(garden, availablePlants, plants, plantType, pos, egg::Vector2i(0, -1));
	growDir(garden, availablePlants, plants, plantType, pos, egg::Vector2i(1, 0));
	growDir(garden, availablePlants, plants, plantType, pos, egg::Vector2i(0, 1));
	growDir(garden, availablePlants, plants, plantType, pos, egg::Vector2i(-1, 0));
}

struct Region {
	char plantType;
	std::vector<egg::Vector2i> plants;

	Region(std::vector<std::vector<char>>& garden, std::vector<egg::Vector2i>& availablePlants, egg::Vector2i start) {
		plantType = garden.at(start.y).at(start.x);
		availablePlants.erase(std::find(availablePlants.begin(), availablePlants.end(), start));
		plants.emplace_back(start);
		growRegion(garden, availablePlants, plants, plantType, start);
	}

	int calculateCost() {
		int perimiter = 0;
		for(std::size_t i = 0; i < plants.size(); i++) {
			int validNeighbors = 0;
			for(egg::Vector2i vec : plants.at(i).getNeighbors()) {
				validNeighbors += std::count(plants.begin(), plants.end(), vec);
			}
			perimiter += 4 - validNeighbors;
		}
		return perimiter * plants.size();
	}
};

int main() {
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");

	std::set<char> visitedRegions;
	std::vector<egg::Vector2i> availablePlants;

	std::vector<std::vector<char>> garden;
	garden.reserve(input.size());
	for(std::size_t i = 0; i < input.size(); i++) {
		std::vector<char> out;
		out.reserve(input.at(i).size());
		for(std::size_t j = 0; j < input.at(i).size(); j++) {
			char c = input.at(i).at(j);
			availablePlants.emplace_back(egg::Vector2i(i, j));
			out.emplace_back(input.at(i).at(j));
		}
		garden.emplace_back(out);
	}

	std::vector<Region> regions;
	int totalCost = 0;
	while(availablePlants.size() != 0) {
		regions.emplace_back(Region(garden, availablePlants, availablePlants.front()));
		totalCost += regions.back().calculateCost();
	}

	std::cout << "cost: " << totalCost << "\n";

	return 0;
}
