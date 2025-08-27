#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>

std::vector<std::string> ReadInputFile(std::string name) {
	std::fstream stream(name);
	if(!stream.is_open()) std::cout << "File name \"" << name << "\" cannot be found!\n";

	std::vector<std::string> lines;
	while (stream.good()) {
		std::string l;
		std::getline(stream, l);
		lines.push_back(l);
	}
	lines.pop_back();
	return lines;
}

template <typename T> struct Vector2 {
	Vector2<T>() : x(0), y(0) {};
	Vector2<T>(T _x, T _y) : x(_x), y(_y) {};

	T x;
	T y;

	void operator+= (Vector2<T>& other) {
		x += other.x;
		y += other.y;
	}

	void operator-= (Vector2<T>& other) {
		x -= other.x;
		y -= other.y;
	}

	std::string toString() {
		std::stringstream str("(");
		str << "(" << x << ", " << y << ")";
		return str.str();
 	}
};

void PrintStage(std::vector<std::string>& output, Vector2<int>& pos) {
	for(int y = 0; y < output.size(); y++) {
		std::string str = output.at(y);
		for(int x = 0; x < str.size(); x++) {
			if(x == pos.x && y == pos.y) {
				std::cout << "\x1B[31m" << str.at(x) << "\033[0m";
			} else {
				std::cout << str.at(x);
			}
		}
		std::cout << "\n";
	}
}

int main() {
	// std::vector<std::string> output = ReadInputFile("./inputTest.txt");
	std::vector<std::string> output = ReadInputFile("./input.txt");

	int count = 1;
	std::array<Vector2<int>, 5> slopes = {
		Vector2<int>({1, 1}),
		Vector2<int>({3, 1}),
		Vector2<int>({5, 1}),
		Vector2<int>({7, 1}),
		Vector2<int>({1, 2})
	};

	int width = output.at(0).size();

	for(int i = 0; i < slopes.size(); i++) {
		Vector2<int> pos = {0, 0};
		int slopeCount = 0;
		while (pos.y < output.size()) {
			pos += slopes[i];
			pos.x = pos.x % width;
			if(pos.y >= output.size()) break;

			std::string line = output.at(pos.y);

			slopeCount += line.at(pos.x) == '#' ? 1 : 0;
		} 
		count *= slopeCount;
	}

	std::cout << "The count is: " << count << "\n";

	return 0;
}

