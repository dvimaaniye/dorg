#include <boost/algorithm/string/case_conv.hpp>
#include <filesystem>
#include <iostream>
#include <liborganizer/organizer.hpp>
#include <libutility/category.hpp>

Organizer::Organizer(fs::path source, fs::path destination)
{
	this->source = source;
	this->destination = destination;
}

void
Organizer::organize_in_memory()
{
	this->category_wise_files = Category::categorize_by_extension(this->source);
}

void
Organizer::apply()
{
	using std::cout, std::cerr, std::endl;

	if (this->category_wise_files.empty()) {
		cout << "Nothing to apply" << endl;
		return;
	}

	OverrideOptions global_override = OverrideOptions::NOT_SET;

	for (auto &[category, files] : this->category_wise_files) {
		OverrideOptions category_override = OverrideOptions::NOT_SET;
		auto maybe_directory = Category::directory_name_from_category(category);
		if (!maybe_directory) {
			continue;
		}

		const std::string &directory_name = *maybe_directory;
		fs::path destination_directory = this->destination / directory_name;

		cout << "[" << category << "]: " << destination_directory << endl;
		fs::create_directory(destination_directory);

		cout << "copying files now" << endl;
		for (const auto &file_path : files) {
			fs::path file_destination_path = destination_directory / file_path.filename();
			OverrideOptions local_override = OverrideOptions::NOT_SET;

			if (fs::exists(file_destination_path)) {
				if (global_override == OverrideOptions::SKIP ||
				    category_override == OverrideOptions::SKIP) {
					continue;
				}
				if (global_override == OverrideOptions::NOT_SET &&
				    category_override == OverrideOptions::NOT_SET) {
					cout << "file " << file_destination_path << "exists" << endl;
					cout << "Override it? \n[y/c(yes for this category)/a(yes "
					        "for all), n(skip)/k(skip for category)/x(skip for all)] ";

					std::string override_choice;
					std::getline(std::cin, override_choice);
					boost::to_lower(override_choice);

					if (override_choice == "y") {
						local_override = OverrideOptions::OVERWRITE;
					} else if (override_choice == "c") {
						category_override = OverrideOptions::OVERWRITE;
					} else if (override_choice == "a") {
						global_override = OverrideOptions::OVERWRITE;
					} else if (override_choice == "k") {
						category_override = OverrideOptions::SKIP;
					} else if (override_choice == "x") {
						global_override = OverrideOptions::SKIP;
					} else {
						local_override = OverrideOptions::SKIP;
					}
				}
			}

			auto copy_options = fs::copy_options::skip_symlinks;

			if (local_override == OverrideOptions::OVERWRITE ||
			    category_override == OverrideOptions::OVERWRITE ||
			    global_override == OverrideOptions::OVERWRITE) {
				copy_options |= fs::copy_options::overwrite_existing;
			}

			fs::copy_file(file_path, file_destination_path, copy_options);
		}
	}
}

void
Organizer::info()
{
	using std::cout, std::endl;
	cout << "categories found: " << this->category_wise_files.size() << endl;

	for (const auto &[category, files] : this->category_wise_files) {
		cout << "category: " << category << ", files count: " << files.size() << endl;
	}
}
