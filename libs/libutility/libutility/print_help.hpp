#pragma once

#include <boost/algorithm/string/case_conv.hpp>
#include <iostream>

inline void
print_args(std::string_view source, std::string_view destination)
{
	using std::cout, std::endl;
	cout << " ------------- " << endl;
	cout << "      [source] " << source << endl;
	cout << " [destination] " << destination << endl;
	cout << " ------------- " << endl;
}

inline void
print_usage(std::string_view prog_name)
{
	using std::cout, std::endl;
	std::cout << "Usage:\n"
	          << "  " << prog_name << " -s source\n"
	          << "  " << prog_name << " -s source -d destination\n";
}

struct OptionDescription {
	std::string shortopt;
	std::string longopt;
	const char *argument;
	std::string description;
};

template<std::size_t N>
inline void
print_options(const OptionDescription (&options)[N])
{
	using std::cout, std::endl;
	cout << "Options: " << endl;

	for (const auto &opt : options) {
		std::string left_col = opt.argument ? opt.shortopt + " " + opt.argument + ", " + opt.longopt +
		                                        " " + opt.argument
		                                    : opt.shortopt + ", " + opt.longopt;
		std::cout << "  " << left_col << std::left << std::setw(std::max(2, 36 - (int)left_col.size()))
		          << " " << opt.description << "\n";
	}

	std::cout << std::endl;
}

inline void
print_help(std::string_view prog_name)
{
	using std::cout, std::endl;
	const OptionDescription options[] = {
	  {"-s", "--source", "DIRECTORY", "Source directory (required)"},
	  {"-d", "--dest", "DIRECTORY", "Destination directory (default: source)"},
	  {"-h", "--help", nullptr, "Show this help message and exit"}
	};
	print_usage(prog_name);
	print_options(options);
}
