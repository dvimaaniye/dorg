#pragma once

#include <string>
#include <vector>

struct Category {
	std::string name;
	std::string dir;
	std::vector<std::string> extensions;
};

struct CategoryRule : Category {
	bool override = false;
};
