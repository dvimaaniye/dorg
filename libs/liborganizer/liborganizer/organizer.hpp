#pragma once
#include <filesystem>
#include <libutility/category.hpp>
#include <libutility/config.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

enum class OverrideOptions { NOT_SET, SKIP, OVERWRITE };

class Organizer
{
public:
	Organizer(
	  fs::path source,
	  fs::path destination,
	  std::shared_ptr<const std::unordered_map<std::string, std::string_view>> extension_to_directory
	);
	void organize_in_memory();
	void apply();
	void info() const;
	void show_layout() const;

private:
	OverrideOptions
	decide_override(fs::path file_path, OverrideOptions &directory, OverrideOptions &global);
	std::shared_ptr<const std::unordered_map<std::string, std::string_view>> extension_to_directory;
	std::unordered_map<std::string_view, std::vector<fs::path>> directory_wise_files;
	fs::path source;
	fs::path destination;
};
