#pragma once

#include <boost/algorithm/string/case_conv.hpp>
#include <filesystem>
#include <iostream>
#include <liblogger/logger.hpp>

#define FS_ACTION(fn_call, msg, would_msg) \
	if (fop::dry_run) {                      \
		INFO("Would " << would_msg);           \
	} else {                                 \
		fn_call;                               \
		INFO(msg);                             \
	}

#define FS_CREATE_DIR(path)                  \
	FS_ACTION(                                 \
	  std::filesystem::create_directory(path), \
	  "Created " << path << " directory.\n",   \
	  "create " << path << " directory.\n"     \
	)

#define FS_CREATE_DIRS(path)                   \
	FS_ACTION(                                   \
	  std::filesystem::create_directories(path), \
	  "Created " << path << " directories.\n",   \
	  "create " << path << " directories.\n"     \
	)

#define FS_RENAME(from, to)                     \
	FS_ACTION(                                    \
	  std::filesystem::rename(from, to),          \
	  "Renamed " << from << " to " << to << "\n", \
	  "rename " << from << " to " << to << "\n"   \
	)

namespace fop
{
namespace fs = std::filesystem;

inline bool dry_run = true;

inline bool
handle_directory_existence(const std::string &directory_path, const bool ask_before_creating = true)
{
	if (!fs::exists(directory_path)) {

		if (!ask_before_creating) {
			FS_CREATE_DIRS(directory_path);
			return EXIT_SUCCESS;
		}

		std::string user_wants_dir;

		std::cout << directory_path << " not found.\nCreate it? [y/N] ";
		std::getline(std::cin, user_wants_dir);
		boost::to_lower(user_wants_dir);

		if (user_wants_dir == "y") {
			FS_CREATE_DIRS(directory_path);
		} else {
			return fs::exists(directory_path) ? EXIT_SUCCESS : EXIT_FAILURE;
		}
	} else if (!fs::is_directory(directory_path)) {
		ERROR(directory_path << " is not a directory" << "\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
}
