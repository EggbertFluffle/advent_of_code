#include <cstddef>
#include <ios>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

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
	}

	bool testField(uint num) {
		return (lowRange.first <= num && num <= lowRange.second) || (highRange.first <= num && num <= highRange.second);
	}
};

int main() {
// #define TEST
#ifndef TEST
	std::vector<uint> myTicket{11, 12, 13};
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

	typedef std::vector<uint> Ticket;
	// Create all of the tickets
	std::vector<Ticket> tickets;
	tickets.reserve(nearbyTickets.size());
	for(std::string str : nearbyTickets) {
		std::vector<std::string> splitNumbers = egg::string_split(str, ",");
		Ticket nums;
		for(std::string num : splitNumbers) {
			nums.emplace_back(std::stoi(num));
		}
		tickets.emplace_back(nums);
	}

	std::vector<Ticket> validTickets;
	uint sum = 0;
	for(Ticket& tix : tickets) {
		// Check if a ticket is valid
	 	bool ticketValid = true;
		for(uint num : tix) {
			bool numberValid = false;
			for(Field& f : fields) {
				numberValid = f.testField(num);
				if(numberValid) break;
			}
			ticketValid = numberValid;
			if(!ticketValid) break;
		}
		if(ticketValid) validTickets.emplace_back(tix);
	}

	std::printf("valid ticket count %ld\n", validTickets.size());

	std::printf("------------\n");
	std::for_each(fields.begin(), fields.end(), [](Field& t){
		std::printf("%s\n", t.name.c_str());
	});
	std::printf("------------\n");

	std::vector<Field*> fieldOrder;
	fieldOrder.resize(fields.size());
	for(Field f : fields) {
		std::printf("PLACING FIELD %s\n", f.name.c_str());
		for(int i = 0; i < myTicket.size(); i++) {
			std::printf("\t-Testing ticket value %d\n", i);
			bool fieldValid = true;
			for(Ticket t : validTickets) {
				fieldValid = f.testField(t.at(i));
				if(!fieldValid) break;
			}
			std::printf("\t\tThis is %s %s\n", f.name.c_str(), fieldValid ? "TRUE" : "FALSE");
			if(fieldValid) fieldOrder.at(i) = &f;
		}
	}

	std::for_each(fieldOrder.begin(), fieldOrder.end(), [](Field* f){
		std::printf("%s\n", f->name.c_str());
	});

	std::printf("TOTAL: %d\n", sum);

	return 0;
}
