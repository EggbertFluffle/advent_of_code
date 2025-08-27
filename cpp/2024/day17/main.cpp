// Wrong answers

#include <cstddef>
#include <thread>
#include <cassert>
#include <cmath>
#include <string>
#include <vector>

#include "../../utils/EggUtils.h"
#include "../../utils/EggVector.h"

#define A registers.at(0)
#define B registers.at(1)
#define C registers.at(2)

std::vector<int> ogProgram;
std::vector<int> ogRegisters;

void run(std::size_t threadCount, std::size_t startOffset) {
	for(int a = startOffset; true; a += threadCount) {
		std::vector<int> registers = ogRegisters;
		std::vector<int> program = ogProgram;
		A = a;

		std::vector<int> out;

		bool quit = false;

		for(std::uint64_t i = 0; i < program.size() && !quit; i += 2) {
			std::uint64_t opcode = program.at(i);
			std::uint64_t literal = program.at(i + 1);
			std::uint64_t combo;

			if(literal > 3 && literal < 7) {
				// Corresponds to a register
				combo = registers.at(literal - 4);
			} else {
				combo = literal;
			}

			switch(opcode) {
				case 0: {
					// adv
					A = static_cast<std::uint64_t>(static_cast<double>(A) / static_cast<double>(std::pow(2, combo)));
					break;
				}
				case 1: {
					// bxl
					B = B ^ literal;
					break;
				}
				case 2: {
					// bst
					B = combo & 7;
					break;
				}
				case 3: {
					// jnz
					if(A == 0) break;
					i = literal;
					i -= 2;
					break;
				}
				case 4: {
					// bxc
					B = B ^ C;
					break;
				}
				case 5: {
					// out
					out.emplace_back(combo % 8);
					if(out.back() != ogProgram.at(out.size() - 1)) quit = true;
					break;
				}
				case 6: {
					// bdv
					B = static_cast<std::uint64_t>(static_cast<double>(A) / static_cast<double>(std::pow(2, combo)));
					break;
				}
				case 7: {
					// cdv
					C = static_cast<std::uint64_t>(static_cast<double>(A) / static_cast<double>(std::pow(2, combo)));
					break;
				}
			}
			if(quit) continue;
		}
		if(out == ogProgram) {
			std::cout << "Answer?: " << a << "\n";
		}
	}
}

int main() {
	std::vector<std::string> input = egg::readInputFile("./input.txt");
	// std::vector<std::string> input = egg::readInputFile("./inputTest.txt");
	
	ogProgram = egg::extract_numbers(input.at(0));
	ogRegisters = egg::extract_numbers(input.at(1));

	const int threadCount = 10;
	std::array<std::thread, threadCount> threads;
	for(std::size_t i = 0; i < threads.size(); i++) {
		threads.at(i) = std::thread(run, threadCount, i);
	}

	for(std::thread& t : threads) {
		t.join();
	}

	return 0;
}
