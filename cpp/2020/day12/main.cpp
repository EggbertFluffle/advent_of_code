#include <string>
#include <vector>
#include <utility>

#include "../../utils/EggUtils.h"

// Wrong answers
// 46603

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::pair<int, int> shipPos;
	std::pair<int, int> waypointPos = std::make_pair(10, 1);

	for(std::string str : input) {
		char dir = str.at(0);
		int mag = std::stoi(str.substr(1));

		std::printf("instruction: %s\n", str.c_str());

		switch(dir) {
			case 'N': {
				waypointPos.second += mag;
				break;
			}
			case 'S': {
				waypointPos.second -= mag;
				break;
			}
			case 'E': {
				waypointPos.first += mag;
				break;
			}
			case 'W': {
				waypointPos.first -= mag;
				break;
			}
			case 'L': {
				for(int i = 0; i < mag / 90; i++) {
					int tmp = waypointPos.first;
					waypointPos.first = -waypointPos.second;
					waypointPos.second = tmp;
				}
				break;
			}
			case 'R': {
				for(int i = 0; i < mag / 90; i++) {
					std::printf("rotation: (%d, %d)", waypointPos.first, waypointPos.second);
					int tmp = waypointPos.first;
					waypointPos.first = waypointPos.second;
					waypointPos.second = -tmp;
					std::printf(" -> (%d, %d)\n", waypointPos.first, waypointPos.second);
				}
				break;
			}
			case 'F': {
				shipPos.first += waypointPos.first * mag;
				shipPos.second += waypointPos.second * mag;
				break;
			}
		}
		std::printf("ship location: (%d, %d)\n", shipPos.first, shipPos.second);
		std::printf("waypoit location: (%d, %d)\n", waypointPos.first, waypointPos.second);
	}

	std::printf("Answer: %d\n", std::abs(shipPos.first) + std::abs(shipPos.second));

	return 0;
}
