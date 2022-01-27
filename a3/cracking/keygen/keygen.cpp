#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <unordered_map>

const std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool check_fifth(const char a, const char b, const char c, const char d, const char e) {
	return (b - 1 == a) && (d + 1 == c) && (e == 'X');
}

bool check_fourth(const char a, const char b, const char c, const char d, const char e) {
	return ((a | c | e) & 0xf) == (b ^ d);
}

bool check_third(const char a, const char b, const char c, const char d, const char e) {
	return (a & b & c & d) == e;
}

bool check_second(const char a, const char b, const char c, const char d, const char e) {
	return (a ^ b ^ c) == e;
}

bool check_first(const char a, const char b, const char c, const char d, const char e) {
	return (a ^ b ^ c ^ d ^ e) == 'A';
}

std::unordered_map<int, std::string> generate(
            std::function<bool(const char, const char, const char,
                               const char, const char)> callback) {
	std::unordered_map<int, std::string> result;

	int count = 0;
	for (auto a : std::as_const(alphabet)) {
		for (auto b : std::as_const(alphabet)) {
			for (auto c : std::as_const(alphabet)) {
				for (auto d : std::as_const(alphabet)) {
					for (auto e : std::as_const(alphabet)) {
						if (std::invoke(callback, a, b, c, d, e)) {
							std::string s;
							s += a;   s += b;   s += c;
							s += d;   s += e;
							result.emplace(count++, s);
						}
					}
				}
			}
		}
	}

	return result;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Provide a number as an argument" << std::endl;
		return -1;
	}

	std::function<bool(const char, const char, const char, const char, const char)> first_f = check_first;
	std::function<bool(const char, const char, const char, const char, const char)> second_f = check_second;
	std::function<bool(const char, const char, const char, const char, const char)> third_f = check_third;
	std::function<bool(const char, const char, const char, const char, const char)> fourth_f = check_fourth;
	std::function<bool(const char, const char, const char, const char, const char)> fifth_f = check_fifth;

	std::unordered_map<int, std::string> first = generate(first_f);
	std::unordered_map<int, std::string> second = generate(second_f);
	std::unordered_map<int, std::string> third = generate(third_f);
	std::unordered_map<int, std::string> fourth = generate(fourth_f);
	std::unordered_map<int, std::string> fifth = generate(fifth_f);
	
	std::string arg = argv[1];
	if (arg.compare("--all") == 0) {
		for (auto& first_it : first) {
			for (auto& second_it : second) {
				for (auto& third_it : third) {
					for (auto& fourth_it : fourth) {
						for (auto& fifth_it : fifth) {
							std::cout << first_it.second << "-" << second_it.second << "-" <<
							             third_it.second << "-" << fourth_it.second << "-" <<
							             fifth_it.second << std::endl;
						}
					}
				}
			}
		}
	} else {
		int i = 0;
		int nKeys = std::stoi(arg);
		for (auto& first_it : first) {
			for (auto& second_it : second) {
				for (auto& third_it : third) {
					for (auto& fourth_it : fourth) {
						for (auto& fifth_it : fifth) {
							std::cout << first_it.second << "-" << second_it.second << "-" <<
										 third_it.second << "-" << fourth_it.second << "-" <<
										 fifth_it.second << std::endl;

							if (i++ >= nKeys)
								return 0;
						}
					}
				}
			}
		}
	}

	return 0;
}
