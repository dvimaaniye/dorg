#pragma once

#include <boost/algorithm/string/case_conv.hpp>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

inline bool
handle_directory_existence(const std::string &directory_path, const bool ask_before_creating = true)
{
	using std::cin, std::cout, std::cerr, std::endl;
	if (!fs::exists(directory_path)) {
		cerr << "Directory " << directory_path << " not found" << endl;

		if (!ask_before_creating) {
			cout << "Creating directory " << directory_path << endl;
			fs::create_directories(directory_path);
			return EXIT_SUCCESS;
		}

		std::string user_wants_dir;

		cout << "Create it? [y/N] ";
		std::getline(cin, user_wants_dir);
		boost::to_lower(user_wants_dir);

		if (user_wants_dir == "y") {
			cout << "Creating directory " << directory_path << endl;
			fs::create_directory(directory_path);
		} else {
			return EXIT_FAILURE;
		}
	} else if (!fs::is_directory(directory_path)) {
		cerr << directory_path << " is not a directory" << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
