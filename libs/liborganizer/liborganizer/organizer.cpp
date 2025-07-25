#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <filesystem>
#include <iostream>
#include <liborganizer/organizer.hpp>
#include <libutility/category.hpp>
#include <libutility/fs_operations.hpp>
#include <memory>

Organizer::Organizer(
  fs::path source,
  fs::path destination,
  std::shared_ptr<const std::unordered_map<std::string, std::string_view>> extension_to_directory
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
	using std::cout, std::cerr, std::endl;

	if (this->directory_wise_files.empty()) {
		cout << "Nothing to do" << endl;
		return;
	}

	OverrideOptions global_override = _global_override;

	for (const auto &[directory_name, files] : this->directory_wise_files) {
		fs::path directory_path = this->destination / directory_name;
		handle_directory_existence(directory_path, false);

		OverrideOptions directory_override = OverrideOptions::NOT_SET;

		for (const auto &file : files) {
			fs::path file_path = directory_path / file.filename();

			if (fs::exists(file_path)) {
				OverrideOptions override_decision = decide_override(
				  file_path, directory_override, global_override
				);

				if (override_decision == OverrideOptions::SKIP) {
					continue;
				}
			}

			fs::rename(file, file_path);
		}
	}
}

OverrideOptions
Organizer::decide_override(fs::path file_path, OverrideOptions &directory, OverrideOptions &global)
{
	using std::cout, std::endl;

	if (global != OverrideOptions::NOT_SET) {
		return global;
	}

	if (directory != OverrideOptions::NOT_SET) {
		return directory;
	}

	// clang-format off
	cout << "file " << file_path << " exists. Override it? \n"
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
	using std::cout, std::endl;
	cout << "files divided into " << this->directory_wise_files.size() << " directories" << "\n";

	for (const auto &[directory_name, files] : this->directory_wise_files) {
		cout << "directory: " << directory_name << ", files count: " << files.size() << "\n";
	}
	cout << endl;
}

void
Organizer::show_layout() const
{
	using std::cout, std::endl;

	if (this->directory_wise_files.empty()) {
		cout << "No layout has been made for " << this->destination << endl;
		return;
	}
	cout << this->destination << " organized layout: \n";

	for (const auto &[directory_name, files] : this->directory_wise_files) {
		cout << "  " << directory_name << ": \n";
		for (const auto &file : files) {
			cout << "    - " << file << "\n";
		}
	}

	cout << endl;
}
