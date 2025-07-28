#pragma once

#include <filesystem>
#include <memory>
#include <unordered_map>
#include <vector>

namespace sfs = std::filesystem;

enum class OverrideOptions { NOT_SET, SKIP, OVERWRITE };

class Organizer
{
public:
	Organizer(
	  sfs::path source,
	  sfs::path destination,
	  std::shared_ptr<const std::unordered_map<std::string, std::string>> extension_to_directory
	);
	void organize_in_memory(bool insensitive_case = false);
	void apply(OverrideOptions _global_override = OverrideOptions::NOT_SET);
	void info() const;
	void show_layout() const;

private:
	OverrideOptions
	decide_override(sfs::path file_path, OverrideOptions &directory, OverrideOptions &global);
	std::shared_ptr<const std::unordered_map<std::string, std::string>> extension_to_directory;
	std::unordered_map<std::string, std::vector<sfs::path>> directory_wise_files;
	sfs::path source;
	sfs::path destination;
};
