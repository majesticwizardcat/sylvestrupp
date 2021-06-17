#include "tools.h"


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

std::optional<std::pair<std::string, std::string>> breakNameToParts(std::string name) {
	auto result = std::optional<std::pair<std::string, std::string>>();
	if (name.empty()) {
		return result;
	}
	if (name[0] == '[') {
		name.erase(name.begin());
		std::vector<std::string> tokens = tokeinize(name, ']');
		if (tokens.size() != 2 || tokens[0].empty() || tokens[1].empty()) {
			return result;
		}
		tokens[1].erase(tokens[1].begin());
		result.emplace(tokens[0], tokens[1]);
		return result;
	}
	std::vector<std::string> tokens = tokeinize(name, ':');
	if (tokens.size() != 2 || tokens[0].empty() || tokens[1].empty()) {
		return result;
	}
	result.emplace(tokens[0], tokens[1]);
	return result;
}

}
