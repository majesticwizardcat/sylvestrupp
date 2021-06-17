#pragma once

#include <vector>
#include <string>
#include <optional>

namespace tools {

std::vector<std::string> tokeinize(const std::string& str, char delim);
std::optional<std::pair<std::string, std::string>> breakNameToParts(std::string name);

}