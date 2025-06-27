#pragma once

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

inline int
handle_destination_existence(const fs::path &destination_path)
{
	using std::cin, std::cout, std::cerr, std::endl;
	if (!fs::exists(destination_path)) {
		cerr << "Destination directory " << destination_path << " not found" << endl;

		char user_wants_dir = 'n';

		cout << "Create it? [y/N] ";
		cin >> user_wants_dir;

		if (std::tolower(user_wants_dir) == 'y') {
			cout << "Creating directory " << destination_path << endl;
			fs::create_directory(destination_path);
		} else {
			return EXIT_FAILURE;
		}
	}
	if (!fs::is_directory(destination_path)) {
		cerr << "Destination path " << destination_path << " is not a directory" << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline void
print_args(const std::string &source, const std::string &destination, const std::string &mode)
{
	using std::cout, std::endl;
	cout << " ------------- " << endl;
	cout << "      [source] " << source << endl;
	cout << " [destination] " << destination << endl;
	cout << "        [mode] " << mode << endl;
	cout << " ------------- " << endl;
}

inline void
print_usage(std::string_view bin_name)
{
	using std::cout, std::endl;
	cout << "Usage: " << endl;
#define X(str) cout << "       " << bin_name << " " << #str << endl;
	X(source)
	X(source destination)
	X(-s source)
	X(-s source - d destination)
	X(-s source - d destination - m mode)
#undef X
}

inline void
print_options()
{
	using std::cout, std::endl;

	cout << "Options: " << endl;
#define X(str1, str2) cout << "  " << #str1 << ", " << #str2 << endl;
	X(-s DIRECTORY, --source DIRECTORY Path to the source directory to organize)
	X(-d DIRECTORY,
	  --destination DIRECTORY Path to the destination directory to move the organized files to)
	X(-m MODE, --mode MODE Determines which mode to run the organizer in)
	X(-h, --help Prints this message)
#undef X
}

inline void
print_help(std::string_view bin_name)
{
	using std::cout, std::endl;
	print_usage(bin_name);
	print_options();
}
