#pragma once

#include <getopt.h>
#include <string>
#include <vector>

struct Option {
	const char *long_name;
	const char *short_name;
	int has_arg;
};

struct OptionDescription {
	struct Option option;
	std::string argument;
	std::string description;
};

// clang-format off
inline std::vector<OptionDescription> option_descriptions = {
  {"source", "s", required_argument, "DIRECTORY", "Directory to organize the files of (required)"},
  {"dest", "d", required_argument, "DIRECTORY", "Directory to where the organized files are saved (default: source)"},
  {"config", "c", required_argument, "FILE_PATH", "Path to custom config"},
  {"insensitive-case", "i", no_argument, "", "Whether to treat, for ex: jpg and JPG, as same. (default: false, i.e., they are different)"},
  {"override", "o", no_argument, "", "Override existing files without asking"},
  {"skip", "k", no_argument, "", "Skip existing files without asking"},
  {"dry-run", nullptr, no_argument, "", "Does not move any file or create any directory"},
  // Need to have a logger in place to implement the following
  // {"quiet", "q", no_argument, "", "Run without logs (will display errors)"},
  // {"verbose", "v", no_argument, "", "Logs out more details than in default mode"},
  {"help", "h", no_argument, "", "Print the help menu"},
};
// clang-format on

inline std::vector<Option> options = [] {
	std::vector<Option> opts;
	for (const auto &desc : option_descriptions) {
		opts.push_back(desc.option);
	}
	return opts;
}();
