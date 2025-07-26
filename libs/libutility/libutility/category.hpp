#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#define CATEGORY_LIST \
	X(unknown)          \
	X(audio)            \
	X(document)         \
	X(photo)            \
	X(presentation)     \
	X(video)            \
	X(zip)

struct Category {
	std::string name;
	std::string dir;
	std::unordered_set<std::string> extensions;
	bool has(const std::string &extension);
	Category(const std::string &_name, const std::vector<std::string> &_extensions);
	Category(
	  const std::string &_name,
	  const std::string &_dir,
	  const std::vector<std::string> &_extensions
	);
};

typedef struct Category Category;
