#include <cctype>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

bool is_alphanum(char ch) {
	return std::isalnum(static_cast<unsigned char>(ch));
}

bool is_space(char ch) {
	return ch == ' ';
}

bool is_prime(int n) {
	if (n <= 1) {
		return false;
	}
	for (int i = 2; i*i <= n; i++) {
		if (n%i == 0) {
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("USAGE: ode <filename>\n");

	}
	std::ifstream input{argv[1]};

	if (!input.is_open()) {
		printf("could not open %s\n", argv[1]);
	}

	std::vector<int> primes;
	// We count for every line of this epic ode,
	// translation: For every line in text
	for (std::string line; std::getline(input, line);) {
		// The number of alphanumeric characters in the line.
		// translation: get number of alphanumeric characters
		// slpl = Significant Letters Per Line
		int slpl = 0;
		int words = 0;
		for (char& c : line) {
			if (is_alphanum(c))
				slpl++;
			else if (is_space(c)) {
			// Per Line by the number of words that comprise it.
			// translation: count number of words
				words++;
			}
		}
		words++; // word at end of line

		// We then multiply the number of Significant Letters
		// Per Line by the number of words that comprise it.
		// translation: multiply slpl by words
		int sn = slpl * words;

		// Once we have for each phrase the Sacred Number,
		// We subtract one from the Sacred Number and keep those that are Prime.
		// translation: subtract one and keep prime numbers
		sn = sn - 1;
		if (is_prime(sn)) {
			primes.push_back(sn);
		}

	}
	input.close();
	// We don't dare disturb you in your beauty slumber,
	// Unless the Sum of those Primes rings a bell and chime.
	// translation: get the sum of all the primes
	// note: what does bell and chime mean?
	auto sum = std::reduce(primes.begin(), primes.end());

	// We then take another pile of coins for each coin that clinks,
	// Or, in plain words, simply multiply the number of coins by itself.
	// translation: multiply sum
	printf("answer: %d\n", sum * sum);
	

	return 0;
}
