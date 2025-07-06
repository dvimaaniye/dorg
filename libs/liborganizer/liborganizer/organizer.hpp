#pragma once
#include <filesystem>
#include <libapp/mode.hpp>
#include <libcategory/category.hpp>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

class Organizer
{
public:
	Organizer(fs::path source, fs::path destination);
	Organizer(fs::path source, fs::path destination, Mode::Name mode);
	void organize_in_memory();
	void organize_in_memory(Mode::Name m);
	void apply();
	void info();

private:
	std::unordered_map<Category::Name, std::vector<fs::path>> category_wise_files;
	fs::path source;
	fs::path destination;
	Mode::Name mode;
};

enum class OverrideOptions { NOT_SET, SKIP, OVERWRITE };
