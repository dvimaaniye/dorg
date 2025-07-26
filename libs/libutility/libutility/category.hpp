#pragma once

#include <string>
#include <vector>

struct CategoryRule {
	std::string name;
	std::string dir;
	bool override = false;
	std::vector<std::string> extensions;
};
