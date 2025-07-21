#pragma once
#include <filesystem>
#include <libutility/category.hpp>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

class Organizer
{
public:
	Organizer(fs::path source, fs::path destination);
	void organize_in_memory();
	void apply();
	void info();

private:
	std::unordered_map<Category::Name, std::vector<fs::path>> category_wise_files;
	fs::path source;
	fs::path destination;
};

enum class OverrideOptions { NOT_SET, SKIP, OVERWRITE };
