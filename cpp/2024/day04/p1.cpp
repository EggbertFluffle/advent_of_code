#include <algorithm>
#include <cstdint>
#include <iterator>
#include <pstl/glue_algorithm_defs.h>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"

std::string constructString(std::vector<std::vector<char>>& grid, int x, int y, int dx, int dy) {
	std::string out = "";

	int i = x, j = y;
	while(j < grid.size() && j >= 0 && i < grid.at(0).size() && i >= 0) {
		if(dx < 0) {
			out = grid.at(j).at(i) + out;
		} else {
			out.push_back(grid.at(j).at(i));
		}
		i += dx;
		j += dy;
	}
	
	return out;
};

std::string constructDiagonalString(std::vector<std::vector<char>>& grid, int x, int y, bool back) {
	std::string out = "";

	std::string left;
	std::string right;
	if(back) {
		left = constructString(grid, x, y, -1, -1);
		right = constructString(grid, x, y, 1, 1);
	} else {
		left = constructString(grid, x, y, -1, 1);
		right = constructString(grid, x, y, 1, -1);
	}

	// std::cout << "Right: " << right << "\n";
	// std::cout << "Left: " << left << "\n";
	return left.substr(0, left.size() - 1) + right;
};

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::vector<std::vector<char>> grid;
	grid.reserve(input.size());
	std::transform(input.begin(), input.end(), std::back_inserter(grid), [](std::string str){
		std::vector<char> out;
		out.reserve(str.size());
		for(char c : str) {
			out.emplace_back(c);
		}
		return out;
	});

	int sum = 0;
	// Back slash
	for(int i = grid.size() - 1; i >= 0; i--) {
		std::string str = constructDiagonalString(grid, i, 0, true);
		sum += egg::regex_get(str, "XMAS").size();
		std::reverse(str.begin(), str.end());
		sum += egg::regex_get(str, "XMAS").size();

		if(i != 0) {
			str = constructDiagonalString(grid, 0, i, true);
			sum += egg::regex_get(str, "XMAS").size();
			std::reverse(str.begin(), str.end());
			sum += egg::regex_get(str, "XMAS").size();
		}
	}

	// Front slash
	for(int i = 0; i < grid.size(); i++) {
		std::string str = constructDiagonalString(grid, i, grid.size() - 1, false);
		sum += egg::regex_get(str, "XMAS").size();
		std::reverse(str.begin(), str.end());
		sum += egg::regex_get(str, "XMAS").size();

		if(i != grid.size() - 1) {
			str = constructDiagonalString(grid, 0, i, false);
			sum += egg::regex_get(str, "XMAS").size();
			std::reverse(str.begin(), str.end());
			sum += egg::regex_get(str, "XMAS").size();
		}
	}

	// Rows
	for(std::string str : input) {
		sum += egg::regex_get(str, "XMAS").size();
		std::reverse(str.begin(), str.end());
		sum += egg::regex_get(str, "XMAS").size();
	}

	for(int i = 0; i < grid.size(); i++) {
		std::string str = constructString(grid, i, 0, 0, 1);
		sum += egg::regex_get(str, "XMAS").size();
		std::reverse(str.begin(), str.end());
		sum += egg::regex_get(str, "XMAS").size();
	}

	std::cout << "sum: " << sum << "\n";

	return 0;
}
