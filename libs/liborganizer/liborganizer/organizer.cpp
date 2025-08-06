#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <filesystem>
#include <iostream>
#include <liblogger/logger.hpp>
#include <liborganizer/organizer.hpp>
#include <liborganizer/trienode.hpp>
#include <libutility/category.hpp>
#include <libutility/config.hpp>
#include <libutility/fs_operations.hpp>
#include <memory>
#include <unordered_map>

namespace fs = std::filesystem;

Organizer::Organizer(std::vector<Category> categories, bool insensitive_case)
{

	reversed_suffix_trie.set_insensitive_case(insensitive_case);
	this->initialize_trie(categories);
}

void
Organizer::initialize_trie(std::vector<Category> categories)
{
	for (auto category : categories) {
		auto category_name = std::make_shared<std::string>(category.name);
		auto dir_name = std::make_shared<std::string>(category.dir);
		auto data = std::make_shared<TrieData>(category_name, dir_name);

		for (auto &extension : category.extensions) {
			this->reversed_suffix_trie.insert(extension, data);
		}
	}
}

std::unordered_map<std::string, std::vector<fs::path>>
Organizer::dump_structure()
{
	return this->directory_wise_files;
}

void
Organizer::organize_in_memory(const std::vector<fs::path> &files)
{
	for (const auto &file_path : files) {
		std::string file_name = file_path.filename();

		auto match = this->reversed_suffix_trie.find_longest_suffix_match(file_name);
		if (!match || !match->data) {
			continue;
		}

		auto dir_name = match->data->directory;
		if (dir_name != nullptr) {
			this->directory_wise_files[*dir_name].push_back(file_path);
		}
	}
}

void
Organizer::organize_in_memory(fs::path source)
{
	std::vector<fs::path> files{};

	for (const auto &file_iter : fs::directory_iterator{source}) {
		if (file_iter.is_directory() || file_iter.is_symlink()) {
			continue;
		}
		files.push_back(file_iter.path());
	}

	this->organize_in_memory(files);
}

void
Organizer::apply(fs::path destination, OverrideOptions _global_override)
{
	if (this->directory_wise_files.empty()) {
		INFO("Nothing to do\n");
		return;
	}

	OverrideOptions global_override = _global_override;

	for (const auto &[directory_name, files] : this->directory_wise_files) {
		fs::path directory_path = destination / directory_name;
		fop::handle_directory_existence(directory_path, false);

		OverrideOptions directory_override = OverrideOptions::NOT_SET;

		for (const auto &file_path : files) {
			fs::path new_file_path = directory_path / file_path.filename();

			if (fs::exists(new_file_path)) {
				OverrideOptions override_decision = decide_override(
				  new_file_path, directory_override, global_override
				);

				if (override_decision == OverrideOptions::SKIP) {
					continue;
				}
			}

			FS_RENAME(file_path, new_file_path);
		}
		UINFO("\n");
	}
}

OverrideOptions
Organizer::decide_override(fs::path file_path, OverrideOptions &directory, OverrideOptions &global)
{
	if (global != OverrideOptions::NOT_SET) {
		return global;
	}

	if (directory != OverrideOptions::NOT_SET) {
		return directory;
	}

	// clang-format off
	std::cout << "\nfile " << file_path << " exists. Override it? \n"
	        "[ y(yes for this file)/ c(yes for this directory)/ a(yes for all)/ "
	        "n(skip this file)/ k(skip for directory)/ x(skip for all) ] \n"
	        "(default: n) ";
	// clang-format on

	std::string override_choice;
	std::getline(std::cin, override_choice);
	boost::to_lower(override_choice);

	switch (override_choice[0]) {
		case 'y':
			return OverrideOptions::OVERWRITE;
		case 'c':
			directory = OverrideOptions::OVERWRITE;
			return directory;
		case 'a':
			global = OverrideOptions::OVERWRITE;
			return global;
		case 'k':
			directory = OverrideOptions::SKIP;
			return directory;
		case 'x':
			global = OverrideOptions::SKIP;
			return global;
		case 'n':
		default:
			return OverrideOptions::SKIP;
	}
}

void
Organizer::info() const
{
	INFO("files divided into " << this->directory_wise_files.size() << " directories" << "\n");

	for (const auto &[directory_name, files] : this->directory_wise_files) {
		INFO("directory: " << directory_name << ", files count: " << files.size() << "\n");
	}

	UINFO("\n");
}

void
Organizer::show_layout() const
{
	if (this->directory_wise_files.empty()) {
		DEBUG("No layout has been made." << "\n");
		return;
	}

	for (const auto &[directory_name, files] : this->directory_wise_files) {
		DEBUG("  " << directory_name << ": \n");
		for (const auto &file : files) {
			DEBUG("    - " << file << "\n");
		}
	}
	UDEBUG("\n");
}
