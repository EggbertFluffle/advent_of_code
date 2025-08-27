#include <cstddef>
#include <string>
#include <vector>
#include <utility>

#include "../../utils/EggUtils.h"

struct Field {
	std::string name;
	std::pair<uint, uint> lowRange;
	std::pair<uint, uint> highRange;

	Field(std::string line) {
		std::size_t nameDelim = line.find_first_of(":");
		name = line.substr(0, nameDelim);
		line.erase(0, line.substr(0, nameDelim + 1).size());

		std::size_t rangeThrough = line.find_first_of("-");
		std::size_t rangeDelim = line.find_first_of("|");
		lowRange.first = std::stoi(line.substr(0, rangeThrough));
		lowRange.second = std::stoi(line.substr(rangeThrough + 1, rangeDelim - rangeThrough));
		line.erase(0, rangeDelim + 1);

		rangeThrough = line.find_first_of("-");
		rangeDelim = line.find_first_of("|");
		highRange.first = std::stoi(line.substr(0, rangeThrough));
		highRange.second = std::stoi(line.substr(rangeThrough + 1, rangeDelim - rangeThrough));
		line.erase(0, rangeDelim + 1);

		std::printf("\n-----FIELD %s-----\n", name.c_str());
		std::printf("low range %d - %d\n", lowRange.first, lowRange.second);
		std::printf("high range %d - %d\n", highRange.first, highRange.second);
	}

	bool testField(uint num) {
		return (lowRange.first <= num && num <= lowRange.second) || (highRange.first <= num && num <= highRange.second);
	}
};

int main() {
#define TEST
#ifndef TEST
	std::vector<uint> myTicket{7, 1, 14};
	std::vector<std::string> ticketFields = egg::read_input_file("ticketFieldsTest.txt");
	std::vector<std::string> nearbyTickets = egg::read_input_file("nearbyTicketsTest.txt");
#else
	std::vector<uint> myTicket{191,89,73,139,71,103,109,53,97,179,59,67,79,101,113,157,61,107,181,137};
	std::vector<std::string> ticketFields = egg::read_input_file("ticketFields.txt");
	std::vector<std::string> nearbyTickets = egg::read_input_file("nearbyTickets.txt");
#endif

	std::vector<Field> fields;
	fields.reserve(ticketFields.size());
	for(std::string str : ticketFields) {
		fields.emplace_back(Field(str));
	}

	std::vector<std::vector<uint>> tickets;
	tickets.reserve(nearbyTickets.size());
	for(std::string str : nearbyTickets) {
		std::vector<std::string> splitNumbers = egg::string_split(str, ",");
		std::vector<uint> nums;
		for(std::string num : splitNumbers) {
			nums.emplace_back(std::stoi(num));
		}
		tickets.emplace_back(nums);
	}

	uint sum = 0;
	for(std::vector<uint>& tix : tickets) {
		for(uint num : tix) {
			bool invalid = true;
			for(Field f: fields) {
				invalid = invalid && !f.testField(num);
			}
			if(invalid) {
				sum += num;
			} else {
			}
		}
	}

	std::printf("TOTAL: %d\n", sum);

	return 0;
}

// 0, 3, 6, 0, 3, 3, 1, 0, 4, 0
