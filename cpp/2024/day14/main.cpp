#include <bitset>
#include <cmath>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"
#include "../../utils/EggVector.h"

struct Robot {
	egg::Vector2i pos;
	egg::Vector2i vel;

	Robot(std::string line) {
		std::vector<int> inputs = egg::map(egg::string_split(line, ","), [](std::string n){ return std::stoi(n); });
		pos = egg::Vector2i(inputs.at(0), inputs.at(1));
		vel = egg::Vector2i(inputs.at(2), inputs.at(3));
	}

	void step(const int& width, const int& height) {
		pos.x += vel.x;
		pos.y += vel.y;

		if(pos.x >= width) pos.x = pos.x - width;
		if(pos.x < 0) pos.x = pos.x + width;

		if(pos.y >= height) pos.y = pos.y - height;
		if(pos.y < 0) pos.y = pos.y + height;
	}
};

void printGrid(std::array<std::bitset<101>, 103>& grid) {
	for(std::bitset<101>& set : grid) {
		for(std::size_t i = 0; i < 101; i++) {
			if(set.test(i)) {
				std::cout << "#";
			} else {
				std::cout << ".";
			}
		}
	 	std::cout << "\n";
	}
}

int main() {
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");

	const int width = 101;
	const int height = 103;

	std::vector<Robot> robots;
	robots.reserve(input.size());
	for(std::string line : input) {
		robots.emplace_back(Robot(line));
	}

	std::array<std::bitset<101>, 103> grid;
	
	for(std::size_t i = 0; true; i++) {
		for(std::bitset<101>& g : grid) {
			g.reset();
		}
		for(std::size_t i = 0; i < robots.size(); i++) {
			robots.at(i).step(width, height);
			grid.at(robots.at(i).pos.y).set(robots.at(i).pos.x);
		}
		bool CHRISTMAS = false;
		for(std::size_t y = 0; y < 103; y++) {
			int row = 0;
			for(std::size_t x = 0; x < 101; x++) {
				if(grid.at(y).test(x)) {
					row++;
				} else {
					row = 0;
				}
				if(row == 8) CHRISTMAS = true;
			}
		}
		if(CHRISTMAS) {
			printGrid(grid);
			char c;
			std::cout << i << " go?";
			std::cin >> c;
			CHRISTMAS = false;
		}
	}

	return 0;
}
