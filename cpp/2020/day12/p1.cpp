#include <string>
#include <vector>
#include <utility>

#include "../../utils/EggUtils.h"

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::pair<int, int> shipPos;
	int shipDir = 0;
	for(std::string str : input) {
		char dir = str.at(0);
		int mag = std::stoi(str.substr(1));
		switch(dir) {
			case 'N':
				shipPos.second -= mag;
				break;
			case 'S':
				shipPos.second += mag;
				break;
			case 'E':
				shipPos.first += mag;
				break;
			case 'W':
				shipPos.first -= mag;
				break;
			case 'L':
				shipDir -= mag;
				break;
			case 'R':
				shipDir += mag;
				break;
			case 'F':
				switch(shipDir) {
					case 0:
						shipPos.first += mag;
						break;
					case 90:
						shipPos.second += mag;
						break;
					case 180:
						shipPos.first -= mag;
						break;
					case 270:
						shipPos.second -= mag;
						break;
				}
				break;
		}
		shipDir %= 360;
		shipDir = shipDir < 0 ? shipDir + 360 : shipDir;
		std::printf("Ship coords: (%d, %d), Ship Dir: %d\n", shipPos.first, shipPos.second, shipDir);
	}

	//Get Manhattan distance
	std::printf("Answer: %d\n", std::abs(shipPos.first) + std::abs(shipPos.second));

	return 0;
}
