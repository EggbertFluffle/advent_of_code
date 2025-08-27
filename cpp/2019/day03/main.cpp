#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"
#include "../../utils/EggVector.h"

int main() {
	// std::vector<std::string> input = egg::string_split(egg::readInputFile("./input.txt").at(0), ",");
	std::vector<std::string> input = egg::string_split(egg::readInputFile("./inputTest.txt").at(0), ",");

	std::vector<std::string> firstDirections = egg::string_split(input.at(0), ",");
	std::vector<egg::Vector2i> first;
	first.emplace_back(0, 0);

	for(std::string dir : firstDirections) {
		const egg::Vector2i& back = first.back();
		const int mag = std::stoi(dir.substr(1));

		switch (dir.at(0)) {
			case 'U':
				first.emplace_back(back.x, back.y + mag);
				break;
			case 'D':
				first.emplace_back(back.x, back.y - mag);
				break;
			case 'L':
				first.emplace_back(back.x - mag, back.y);
				break;
			case 'R':
				first.emplace_back(back.x + mag, back.y);
				break;
		}
	}


	std::vector<std::string> secondDirections = egg::string_split(input.at(1), ",");
	std::vector<egg::Vector2i> second;
	second.emplace_back(0, 0);

	for(std::string dir : secondDirections) {
		const egg::Vector2i& back = second.back();
		const int mag = std::stoi(dir.substr(1));

		switch (dir.at(0)) {
			case 'U':
				second.emplace_back(back.x, back.y + mag);
				break;
			case 'D':
				second.emplace_back(back.x, back.y - mag);
				break;
			case 'L':
				second.emplace_back(back.x - mag, back.y);
				break;
			case 'R':
				second.emplace_back(back.x + mag, back.y);
				break;
		}
	}

	egg::print_all(input);

	return 0;
}

std::optional<egg::Vector2i> test_crossed(egg::Vector2i f1, egg::Vector2i f2, egg::Vector2i s1, egg::Vector2i s2) {
	bool firstHorizontal = f1.y == f2.y;

	bool secondHorizontal = s1.y == s2.y;

	if(firstHorizontal ^ secondHorizontal) {
		if(firstHorizontal) {
			if(s1.x >= std::min(f1.x, f2.x) && s1.x <= std::max(f1.x, f2.x) && 
	  			s1.y)
		} else {
		}
	} else {
		// Parallel
		if(firstHorizontal) {
			if(f1.y == s1.y) {
				// Overlapping
			}
		} else {
			if(f1.x == s1.x) {
				// Overlapping
			}
		}
	}
}
