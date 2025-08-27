#pragma once

#include <string_view>
#include <cmath>
#include <cstdint>
#include <functional>
#include <future>
#include <iterator>
#include <regex>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace egg {
	std::vector<std::string> read_input_file(const std::string name) {
		std::fstream stream(name);
		if(!stream.is_open()) std::cout << "File name \"" << name << "\" cannot be found!\n";

		std::vector<std::string> lines;
		while (stream.good()) {
			std::string l;
			std::getline(stream, l);
			lines.emplace_back(l);
		}
		lines.pop_back();
		return lines;
	}

	std::vector<std::string> readInputFile(const std::string name) {
		return read_input_file(name);
	}

	template <typename T>
	void print_all(const T& lines, const std::string delimiter) {
		for(auto it = lines.begin(); it != lines.end(); it++) {
			std::cout << *it << delimiter;
		}
	  std::cout << "\n";
	}

	template <typename T>
	void print_all(const std::vector<T>& lines) {
		print_all(lines, "\n");
	}

	std::vector<std::string> string_split(std::string str, const std::string delimeter) {
		std::vector<std::string> out;
		std::size_t pos = 0;
		std::string token;
		while ((pos = str.find(delimeter)) != std::string::npos) {
			token = str.substr(0, pos);
			out.push_back(token);
			str.erase(0, pos + delimeter.length());
		}
		out.push_back(str);
		return out;
	}

	template <typename T>
	bool in_bounds(const T t, const T lower, const T upper) {
		return t > lower && t < upper;
	}

	template <typename T>
	bool in_bounds(const T i, const T j, const T lowerx, const T lowery, const T upperx, const T uppery) {
		return (i > lowerx && i < upperx) && (j > lowery && j < uppery);
	}

	/* 
	 * Takes a string and returns and erases a string between
	 * the wrapperOpen and wrapperClose characters
	 *
	 * @param str: stirng to extract capture from
	 * @param start: where the capture starts, 0 by default
	 * @param wrapperOpen/wrapperClose: delimiters, '(' and ')' by default
	 */
	std::string extract_parenthesis(std::string& str, const std::size_t start = 0, const char wrapperOpen = '(', const char wrapperClose = ')') {
		std::string out;
		if(str.at(start) != wrapperOpen) return "";
		uint open = 0;
		for(std::size_t i = start; i < str.size(); i++) {
			char& current = str.at(i);
			open += current == wrapperOpen ? 1 : current == wrapperClose ? -1 : 0;
			if(open == 0) {
				out = str.substr(start + 1, i - start - 1);
				str.erase(start, i - start + 1);
				break;
			}
		}
		return out;
	}
	
	template <typename T = int>
	int extract_number(std::string& str, std::size_t start = 0) {
		if(str.empty()) throw std::invalid_argument("string is empty");
		if(start >= str.size()) throw std::out_of_range("start is out of bounds");
		std::string out;

		if(str.size() == 1) {
			out = str.substr(0, 1);
			str.erase(0, 1);
			std::cout << out << "\n";
			return std::stoi(out);
		};

		for(std::string::iterator it = str.begin() + start; it != str.end(); it++) {
			if(!std::isalnum(*it)) {
				out = std::string(str.begin() + start, it);
				str.erase(str.begin() + start, it);
				break;
			}
		}
		return static_cast<T>(std::stoi(out.c_str()));
	}

	std::string find_and_replace(std::string base, const std::string find, const std::string replace) {
		std::size_t pos = 0;
		while((pos = base.find(find, pos)) != std::string::npos) {
			base.replace(pos, find.length(), replace);
			pos += replace.length();
		}
		return base;
	}

	std::vector<std::string> regex_get(std::string haystack, const std::string needle) {
		std::vector<std::string> out;

		const std::regex reg(needle);
		std::smatch match;

		while (std::regex_search(haystack, match, reg)) {
			out.emplace_back(match.str());
			haystack = match.suffix().str();
		}

		return out;
	}

	template <typename T = int>
	std::vector<T> extract_numbers(const std::string& haystack) {
		std::vector<std::string> nums = egg::regex_get(haystack, "\\d+");
		std::vector<T> out;
		out.reserve(haystack.size());
		std::transform(nums.begin(), nums.end(), std::back_inserter(out), [](std::string str){ return static_cast<T>(std::stoi(str)); });
		return out;
	}

	template <typename IT, typename E>
	bool has_bounded(const IT start, const IT end, const E value) {
		return std::find(start, end, value) != end;
	}

	template <typename IT, typename E>
	bool has(const IT iterator, const E value) {
		return has_bounded(iterator.begin(), iterator.end(), value);
	}

	template <typename E>
	std::size_t find_index(std::vector<E> iterator, E value) {
		return std::distance(iterator.begin(), std::find(iterator.begin(), iterator.end(), value));
	}

    template <typename I, typename F>
    auto map(const std::vector<I>& input, F lambda) {
        using R = std::invoke_result_t<F, I>;
        std::vector<R> out;
        out.reserve(input.size());
        std::transform(input.begin(), input.end(), std::back_inserter(out), lambda);
        return out;
    }

    template <typename I, typename F>
    auto filter (const std::vector<I>& input, F lambda) {
        std::vector<I> out;
        out.reserve(input.size());
		for(I i : input) {
			if(lambda(i)) out.emplace_back(i);
		}
        return out;
    }

	template <typename I, typename F>
	void for_each(std::vector<I> input, F lambda) {
		for(I i : input) {
			lambda(i);
		}
	}

	template <typename I, typename F>
	bool every(std::vector<I> input, F lambda) {
		for(I i : input) {
			if(!lambda(i)) return false;
		}
		return true;
	}

	template <typename I>
	bool some(const std::vector<I>& input, std::function<bool(I)> lambda) {
		for(I i : input) {
			if(lambda(i)) return true;
		}
		return false;
	}

	template <typename T>
	T parse_large_int(std::string digits) {
		T sum = 0;
		for(std::size_t i = 0; i < digits.size(); i++) {
			sum += std::stoi(digits.substr(i, i + 1)) * std::pow(10, digits.size() - i - 1);
		}
		return sum;
	}

	template <typename T>
	void increment_by_base(std::vector<T>& vec, char base) {
		std::size_t i = 0;
		vec.at(i) += 1;
		while(vec.at(i) >= base) {
			vec.at(i) = 0;
			i++;
			if(i == vec.size()) vec.emplace_back(0);
			vec.at(i) += 1;
		}
	}

	template <typename T>
	std::vector<std::vector<T>> create_2d_vector(std::size_t width, std::size_t height) {
		std::vector<std::vector<T>> out;
		out.reserve(height);
		for(std::size_t i = 0; i < height; i++) {
			std::vector<T> row;
			row.reserve(width);
			for(std::size_t j = 0; j < width; j++) {
				row.emplace_back(T());
			}
			out.emplace_back(row);
		}
		return out;
	}

	template <typename T>
	T lcm(T a, T b) {
		for(T i = 2; i <= std::min(a, b); i++) {
			if((a % i == 0) && (b % i == 0)) return i;
		}
		return 1;
	}


	std::vector<std::vector<char>> to_char_grid(std::vector<std::string> input) {
		std::vector<std::vector<char>> out;
		out.reserve(input.size());
		for(std::string str : input) {
			std::vector<char> row;
			row.reserve(str.size());
			for(char c : str) {
				row.emplace_back(c);
			}
			out.emplace_back(row);
		}
		return out;
	}
};
