#include <filesystem>
#include <iostream>
#include <libapp/organizer.hpp>
#include <libcategory/category.hpp>

Organizer::Organizer(fs::path source, fs::path destination)
  : Organizer::Organizer(source, destination, Mode::Name::extension)
{
}

Organizer::Organizer(fs::path source, fs::path destination, Mode::Name mode)
{
	this->source = source;
	this->destination = destination;
	this->mode = mode;
}

void
Organizer::organize_in_memory()
{
	this->organize_in_memory(this->mode);
}

void
Organizer::organize_in_memory(Mode::Name mode)
{
	using std::cout, std::endl;
	switch (mode) {
		case Mode::Name::header:
			this->category_wise_files = Category::categorize_by_header(this->source);
			break;
		default:
			this->category_wise_files = Category::categorize_by_extension(this->source);
			break;
	}

	cout << "categories found: " << this->category_wise_files.size() << endl;

	for (const auto &[category, files] : this->category_wise_files) {
		cout << "category: " << category << ", files count: " << files.size() << endl;
	}
}

void
Organizer::apply()
{
	using std::cout, std::cerr, std::endl;

	if (this->category_wise_files.empty()) {
		cerr << "Nothing to apply" << endl;
		return;
	}

	bool global_override = false;

	for (auto &[category, files] : this->category_wise_files) {
		bool category_override = false;
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
			fs::path file_destination_path =
			  destination_directory / file_path.filename();
			bool local_override = false;
			if (fs::exists(file_destination_path) && !global_override &&
			    !category_override) {
				cout << "file " << file_destination_path << "exists" << endl;
				cout << "Override it? [y/N(skip)/c(yes for this category)/a(yes "
					"for all)] ";
				char override_choice;
				std::cin >> override_choice;
				override_choice = std::tolower(override_choice);
				if (override_choice == 'y') {
					local_override = true;
				} else if (override_choice == 'c') {
					category_override = true;
				} else if (override_choice == 'a') {
					global_override = true;
				} else {
					continue;
				}
			}

			auto copy_options =
			  fs::copy_options::skip_symlinks | fs::copy_options::overwrite_existing;

			fs::copy_file(file_path, file_destination_path, copy_options);
		}
	}
}
