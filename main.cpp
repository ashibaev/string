#include "String.h"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;

bool CharCompare(char lhs, char rhs) {
	lhs = tolower(lhs);
	rhs = tolower(rhs);
	return lhs > rhs;
}

bool StringCompare(const String& lhs, const String& rhs) {
	return std::lexicographical_compare(
		lhs.cbegin(), lhs.cend(),
		rhs.cbegin(), rhs.cend(),
		CharCompare
	);
}


int main() {
	size_t n;
	cin >> n;
	vector<String> strings(n);

	for (auto& string : strings) {
		cin >> string;
	}

	std::sort(
		strings.begin(),
		strings.end(),
		StringCompare
	);

	for (auto& string : strings) {
		cout << string << std::endl;
	}
	return 0;
}