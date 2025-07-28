#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <filesystem>
#include <iostream>
#include <liblogger/logger.hpp>
#include <liborganizer/organizer.hpp>
#include <libutility/category.hpp>
#include <libutility/config.hpp>
#include <libutility/fs_operations.hpp>
#include <memory>
#include <unordered_map>

namespace fs = std::filesystem;

Organizer::Organizer(
  fs::path source,
  fs::path destination,
  std::shared_ptr<const std::unordered_map<std::string, std::string>> extension_to_directory
) :
  source(source),
  destination(destination),
  extension_to_directory(extension_to_directory)
{
}

void
Organizer::organize_in_memory(bool insensitive_case)
{
	for (const auto &file_path : fs::directory_iterator{this->source}) {
		if (file_path.is_directory() || file_path.is_symlink()) {
			continue;
		}

		std::string extension = file_path.path().extension();
		boost::trim_left_if(extension, boost::is_any_of("."));

		if (insensitive_case) {
			boost::to_lower(extension);
		}

		if (this->extension_to_directory->find(extension) != this->extension_to_directory->end()) {
			this->directory_wise_files[this->extension_to_directory->at(extension)].push_back(
			  file_path.path()
			);
		}
	}
}

void
Organizer::apply(OverrideOptions _global_override)
{
	if (this->directory_wise_files.empty()) {
		INFO("Nothing to do\n");
		return;
	}

	OverrideOptions global_override = _global_override;

	for (const auto &[directory_name, files] : this->directory_wise_files) {
		fs::path directory_path = this->destination / directory_name;
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
	std::cout << "file " << file_path << " exists. Override it? \n"
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

	INFO("\n");
}

void
Organizer::show_layout() const
{
	if (this->directory_wise_files.empty()) {
		DEBUG("No layout has been made for " << this->destination << "\n");
		return;
	}

	DEBUG(this->destination << " organized layout: \n");

	for (const auto &[directory_name, files] : this->directory_wise_files) {
		DEBUG("  " << directory_name << ": \n");
		for (const auto &file : files) {
			DEBUG("    - " << file << "\n");
		}
	}
	DEBUG("\n");
}
