#pragma once

#include <boost/algorithm/string/case_conv.hpp>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

inline bool
handle_directory_existence(const std::string &directory_path, const bool ask_before_creating = true)
{
	if (!fs::exists(directory_path)) {

		if (!ask_before_creating) {
			std::cerr << directory_path << " not found";
			std::cout << ", creating...";
			fs::create_directories(directory_path);
			std::cout << "Done!\n";
			return EXIT_SUCCESS;
		}

		std::string user_wants_dir;

		std::cout << "Create it? [y/N] ";
		std::getline(std::cin, user_wants_dir);
		boost::to_lower(user_wants_dir);

		if (user_wants_dir == "y") {
			std::cout << "Creating directory " << directory_path << "\n";
			fs::create_directories(directory_path);
		} else {
			return EXIT_FAILURE;
		}
	} else if (!fs::is_directory(directory_path)) {
		std::cerr << directory_path << " is not a directory" << "\n";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
