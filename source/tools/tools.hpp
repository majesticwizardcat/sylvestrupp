#pragma once

#include <vector>
#include <string>

namespace tools {

std::vector<std::string> tokeinize(const std::string& str, char delim) {
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do {
		pos = str.find(delim, prev);
		if (pos == std::string::npos) {
			pos = str.length();
		}
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty()) {
			tokens.push_back(token);
		}
		prev = pos + 1;
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

}