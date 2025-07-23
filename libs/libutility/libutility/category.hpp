#pragma once

#include <filesystem>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fs = std::filesystem;

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

// class Category
// {
// public:
// 	Category(const std::string &name, const std::vector<std::string> &extensions);
// 	Category(
// 	  const std::string &name,
// 	  const std::string &dir,
// 	  const std::vector<std::string> &extensions
// 	);
//
// 	std::string name();
// 	std::string dir();
// 	std::unordered_set<std::string> extensions();
// 	bool has(const std::string &extension);
//
// private:
// 	std::string _name;
// 	std::string _dir;
// 	std::unordered_set<std::string> _extensions;
// };

// namespace Category
// {
// enum class Name {
// #define X(name) name,
// 	CATEGORY_LIST
// #undef X
// };
//
// std::unordered_map<Category::Name, std::vector<fs::path>>
// categorize_by_extension(const std::vector<fs::path> &file_paths);
//
// std::unordered_map<Category::Name, std::vector<fs::path>>
// categorize_by_extension(const fs::path &source_path);
//
// Category::Name
// category_of(std::string ext);
//
// std::string
// directory_name_from_category(Category::Name cat);
//
// std::string
// to_string(const Category::Name &cat);
//
// } // namespace Category
//
// std::ostream &
// operator<<(std::ostream &os, Category::Name cat);
