#pragma once

#include <algorithm>
#include <boost/algorithm/string/case_conv.hpp>
#include <iomanip>
#include <iostream>
#include <libutility/args.hpp>
#include <libutility/options.hpp>

inline void
print_args(std::unordered_map<std::string, std::string> args)
{
	int max_width = 10;

	for (const auto &arg : args) {
		max_width = std::max((int)arg.first.size(), max_width);
	}

	std::cout << " " << std::right << std::setw(max_width + 1) << std::setfill('-') << "" << " \n";

	for (const auto &[key, val] : args) {
		std::cout << " " << std::right << std::setw(max_width) << std::setfill(' ') << key << ":";
		std::cout << " " << val << " \n";
	}

	std::cout << " " << std::right << std::setw(max_width + 1) << std::setfill('-') << "" << " \n";
}

inline void
print_usage(std::string_view prog_name)
{
	std::cout << "Usage:\n"
	          << "  " << prog_name << " -s <path>\n"
	          << "  " << std::setw(prog_name.size()) << "" << " [-d | --dest <path>]\n"
	          << "  " << std::setw(prog_name.size()) << "" << " [-i | --insensitive-case]\n"
	          << "  " << std::setw(prog_name.size()) << "" << " [-o | --override]\n"
	          << "  " << std::setw(prog_name.size()) << "" << " [-k | --skip]\n"
	          << "  " << std::setw(prog_name.size()) << "" << " [-h | --help]\n"
	          << "  " << std::setw(prog_name.size()) << "" << " [--dry-run]\n"

	          << "\nTo get default config:\n"
	          << "  " << prog_name << " get-config\n"

	          << "\nNote: Symlinks and directories are never moved\n";
}

inline void
print_options(const std::vector<OptionDescription> &opt_descriptions)
{
	std::cout << "Options: \n";

	for (const auto &opt_description : opt_descriptions) {
		std::string short_name =
		  (opt_description.option.short_name
		     ? "-" + std::string(opt_description.option.short_name) +
		         (opt_description.option.has_arg ? " " + opt_description.argument : "")
		     : "");
		std::string long_name =
		  (opt_description.option.long_name
		     ? "--" + std::string(opt_description.option.long_name) +
		         (opt_description.option.has_arg ? " " + opt_description.argument : "")
		     : "");
		std::string left_col = short_name.empty()  ? long_name
		                       : long_name.empty() ? short_name
		                                           : short_name + ", " + long_name;

		std::cout << "  " << left_col << std::left << std::setw(std::max(2, 36 - (int)left_col.size()))
		          << " " << opt_description.description << "\n";
	}

	std::cout << std::endl;
}

inline void
print_help(std::string_view prog_name)
{
	print_usage(prog_name);
	print_options(option_descriptions);
}
