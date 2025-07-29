#pragma once

#include <filesystem>
#include <liborganizer/reversed_suffix_trie.hpp>
#include <libutility/category.hpp>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

enum class OverrideOptions { NOT_SET, SKIP, OVERWRITE };

class Organizer
{
public:
	Organizer(std::vector<Category> categories, bool insensitive_case = false);

	void organize_in_memory(fs::path source);
	void organize_in_memory(const std::vector<fs::path> &files);
	void apply(fs::path destination, OverrideOptions _global_override = OverrideOptions::NOT_SET);
	void info() const;
	void show_layout() const;
	std::unordered_map<std::string, std::vector<fs::path>> dump_structure();

private:
	std::unordered_map<std::string, std::vector<fs::path>> directory_wise_files;
	ReversedSuffixTrie reversed_suffix_trie;

	void initialize_trie(std::vector<Category> categories);
	OverrideOptions
	decide_override(fs::path file_path, OverrideOptions &directory, OverrideOptions &global);
};
