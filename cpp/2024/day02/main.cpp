#include <complex>
#include <iterator>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"

bool isSafe(std::vector<int> report);
std::vector<int> makeReportWithout(std::vector<int> og, std::size_t remove);

int main() {
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	std::vector<std::string> input = egg::readInputFile("./input.txt");

	std::vector<std::vector<std::vector<int>>> realReports;
	realReports.reserve(input.size());

	std::vector<std::vector<int>> reports;
	reports.reserve(input.size());
	std::transform(input.begin(), input.end(), std::back_inserter(reports), [](std::string str) {
		return egg::extract_numbers(str);
	});

	for(std::size_t r = 0; r < reports.size(); r++) {
		realReports.emplace_back(std::vector<std::vector<int>>());
		for(std::size_t j = 0; j < reports.at(r).size(); j++) {
			realReports.back().emplace_back(makeReportWithout(reports.at(r), j));
		}
	}

	int sum = 0;
	for(std::vector<std::vector<int>> reportSet : realReports) {
		bool safe = false;
		for(std::vector<int> r : reportSet) {
			if(isSafe(r)) {
				safe = true;
			}
		}
		sum += safe ? 1 : 0;
	}

	std::cout << "sum: " << sum << "\n";

	return 0;
}

bool isSafe(std::vector<int> report) {
	bool safety = true;
	if(report.at(0) > report.at(1)) {
		// Decending
		for(std::size_t i = 0; i < report.size() - 1; i++) {
			int diff = report.at(i) - report.at(i + 1);
			if(!(diff >= 1 && diff <= 3)) {
				return false;
			}
		}
	} else {
		// Ascending
		for(std::size_t i = 0; i < report.size() - 1; i++) {
			int diff = report.at(i + 1) - report.at(i);
			if(!(diff >= 1 && diff <= 3)) {
				return false;
			}
		}
	}
	return true;
}

std::vector<int> makeReportWithout(std::vector<int> og, std::size_t remove) {
	std::vector<int> out;
	for(std::size_t k = 0; k < og.size(); k++) {
		if(k != remove) {
			out.emplace_back(og.at(k));
		}
	}
	return out;
}

// example
