#include <cstddef>
#include <cstdlib>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>
#include <array>

#include "../../utils/EggUtils.h"

#define INITIAL_SIZE 8
#define HALF_INITIAL_SIZE ((INITIAL_SIZE - 1) / 2)
#define FINAL_SIZE (INITIAL_SIZE + 12)
#define HALF_FINAL_SIZE ((FINAL_SIZE - 1) / 2)

class ConwayCubes {
	std::array<std::array<std::array<bool, FINAL_SIZE>, FINAL_SIZE>, FINAL_SIZE> grid;
	
public:
	ConwayCubes(std::vector<std::string> input) {
		for(auto& slice : grid) {
			for(auto& row : slice) {
				for(auto& cell : row) {
					cell = false;
				}
			}
		}

		for(std::size_t y = 0; y < input.size(); y++) { 
			for(std::size_t x = 0; x < input.at(y).size(); x++) {
				setCube(x + HALF_FINAL_SIZE - HALF_INITIAL_SIZE, y + HALF_FINAL_SIZE - HALF_INITIAL_SIZE, HALF_FINAL_SIZE, input.at(y).at(x) == '#');
			}
		}
	}

	ConwayCubes(ConwayCubes* cubes) {
		for(std::size_t x = 0; x < grid.size(); x++) {
			for(std::size_t y = 0; y < grid.size(); y++) {
				for(std::size_t z = 0; z < grid.size(); z++) {
					int neighborCount = cubes->countNeighbors(x, y, z);
					if(cubes->getCube(x, y, z).value() && neighborCount == 2 || neighborCount == 3) {
						setCube(x, y, z, true);
					} else if(cubes->getCube(x, y, z).value() && neighborCount == 3) {
						setCube(x, y, z, true);
					} else {
						setCube(x, y, z, false);
					}
				}
			}
		}
	}

	int countNeighbors(std::size_t x, std::size_t y, std::size_t z) {
		int neighbors = 0;
		for(int dx = -1; dx <= 1; dx++) {
			for(int dy = -1; dy <= 1; dy++) {
				for(int dz = -1; dz <= 1; dz++) {
					std::optional<bool> n = getCube(
						static_cast<int>(x) + dx,
						static_cast<int>(y) + dy,
						static_cast<int>(z) + dz
					);
					if(!(dx == 0 && dy == 0 && dz == 0) && n.has_value() && n.value()) neighbors++;
				}
			}
		}
		return neighbors;
	}

	std::optional<bool> getCube(std::size_t x, std::size_t y, std::size_t z) const {
		try {
			return grid.at(x).at(y).at(z);
		} catch(std::out_of_range err) {
			return {};
		}
	}

	void setCube(std::size_t x, std::size_t y, std::size_t z, bool val) {
		try {
			grid.at(x).at(y).at(z) = val;
		} catch(std::out_of_range err) {}
	}

	void printSlice(int z) {
		std::printf("----------\n");
		for(std::size_t y = 0; y < FINAL_SIZE; y++) { 
			for(std::size_t x = 0; x < FINAL_SIZE; x++) {
				std::printf("%c", getCube(x, y, z).value() ? '#' : '.');
			}
			std::printf("\n");
		}
		std::printf("----------\n");
	}

	int countCubes() {
		int cellCount = 0;
		for(auto& slice : grid) {
			for(auto& row : slice) {
				for(auto& cell : row) {
					if(cell) cellCount++;
				}
			}
		}
		return cellCount;
	}
};

int main() {
	std::vector<std::string> input = egg::read_input_file("input.txt");
	// std::vector<std::string> input = egg::read_input_file("testInput.txt");

	ConwayCubes* cubes = new ConwayCubes(input);
	for(int i = 0; i < 6; i++) {
		ConwayCubes* newCubes = new ConwayCubes(cubes);
		std::free(cubes);
		cubes = newCubes;
	}

	std::printf("CELL COUNT %d\n", cubes->countCubes());
	
	return 0;
}
