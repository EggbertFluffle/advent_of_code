#include <cassert>
#include <cmath>
#include <cstddef>
#include <limits>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"
#include "../../utils/EggVector.h"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

void printGrid(std::vector<std::vector<char>>& grid) {
	for(int y = 0; y < grid.size(); y++) {
		for(int x = 0; x < grid.at(y).size(); x++) {
			std::cout << grid.at(y).at(x);
		}
		std::cout << "\n";
	}
}

struct Node {
	std::uint64_t shortestPath;
	int shortestDir;

	Node() : shortestPath(std::numeric_limits<std::uint64_t>::max()), shortestDir(-1) {}
	Node(std::uint64_t _shortestPath, int _shortestDir) : shortestPath(_shortestPath), shortestDir(_shortestDir) {}
};

int main() {
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");

	const std::size_t WIDTH = input.at(0).size();

	egg::Vector2i start, end;
	std::vector<std::vector<char>> grid;

	std::vector<Node> nodes;
	nodes.resize(input.size() * input.at(0).size());
	std::vector<egg::Vector2i> unvisitedNodes;

	grid.reserve(input.size());
	for(int y = 0; y < input.size(); y++) {
		std::vector<char> row;
		row.reserve(input.at(y).size());
		for(int x = 0; x < input.at(y).size(); x++) {
			char c = input.at(y).at(x);
			egg::Vector2i pos = egg::Vector2i(x, y);
			if(c != '#') {
				unvisitedNodes.emplace_back(pos);
				pos.print();
			}
			if(c == 'S') {
				start = pos;
			} else if(c == 'E') {
				end = pos;
			}
			row.emplace_back(c);
		}
		grid.emplace_back(row);
	}

	nodes.at(start.getIndex(WIDTH)) = Node(0, 1);
	unvisitedNodes.erase(std::find(unvisitedNodes.begin(), unvisitedNodes.end(), start));

	egg::Vector2i currentPos = start;
	while(currentPos != end) {
		Node& currentNode = nodes.at(currentPos.getIndex(WIDTH));
		
		// UP
		if(grid.at(currentPos.y - 1).at(currentPos.x) != '#' && currentNode.shortestDir != 2) {
			egg::Vector2i pos = egg::Vector2i(currentPos.x, currentPos.y - 1);
			std::uint64_t dist = currentNode.shortestPath + 1 + (currentNode.shortestDir != 0 ? 1000 : 0);
			if(dist < nodes.at(pos.getIndex(WIDTH)).shortestPath) {
				nodes.at(pos.getIndex(WIDTH)).shortestPath = dist;
				nodes.at(pos.getIndex(WIDTH)).shortestDir = 0;
				grid.at(pos.y).at(pos.x) = 'o';
			}
		}

		// RIGHT
		if(grid.at(currentPos.y).at(currentPos.x + 1) != '#' && currentNode.shortestDir != 3) {
			egg::Vector2i pos = egg::Vector2i(currentPos.x + 1, currentPos.y);
			std::uint64_t dist = currentNode.shortestPath + 1 + (currentNode.shortestDir != 1 ? 1000 : 0);
			if(dist < nodes.at(pos.getIndex(WIDTH)).shortestPath) {
				nodes.at(pos.getIndex(WIDTH)).shortestPath = dist;
				nodes.at(pos.getIndex(WIDTH)).shortestDir = 1;
				grid.at(pos.y).at(pos.x) = 'o';
			}
		}
		
		// DOWN
		if(grid.at(currentPos.y + 1).at(currentPos.x) != '#' && currentNode.shortestDir != 0) {
			egg::Vector2i pos = egg::Vector2i(currentPos.x, currentPos.y + 1);
			std::uint64_t dist = currentNode.shortestPath + 1 + (currentNode.shortestDir != 2 ? 1000 : 0);
			if(dist < nodes.at(pos.getIndex(WIDTH)).shortestPath) {
				nodes.at(pos.getIndex(WIDTH)).shortestPath = dist;
				nodes.at(pos.getIndex(WIDTH)).shortestDir = 2;
				grid.at(pos.y).at(pos.x) = 'o';
			}
		}

		// LEFT
		if(grid.at(currentPos.y).at(currentPos.x - 1) != '#' && currentNode.shortestDir != 1) {
			egg::Vector2i pos = egg::Vector2i(currentPos.x - 1, currentPos.y);
			std::uint64_t dist = currentNode.shortestPath + 1 + (currentNode.shortestDir != 3 ? 1000 : 0);
			if(dist < nodes.at(pos.getIndex(WIDTH)).shortestPath) {
				nodes.at(pos.getIndex(WIDTH)).shortestPath = dist;
				nodes.at(pos.getIndex(WIDTH)).shortestDir = 3;
				grid.at(pos.y).at(pos.x) = 'o';
			}
		}

		// Choose the next vertex
		grid.at(currentPos.y).at(currentPos.x) = '0';
		auto next = std::find(unvisitedNodes.begin(), unvisitedNodes.end(), currentPos);
		if(next != unvisitedNodes.end() || *next == currentPos) {
			unvisitedNodes.erase(next);
		}

		currentPos = unvisitedNodes.front();
		for(egg::Vector2i p : unvisitedNodes) {
			if(nodes.at(p.getIndex(WIDTH)).shortestPath < nodes.at(currentPos.getIndex(WIDTH)).shortestPath) {
				currentPos = p;
			}
		}
	}

	std::cout << nodes.at(end.getIndex(WIDTH)).shortestPath << "\n";

	return 0;
}
