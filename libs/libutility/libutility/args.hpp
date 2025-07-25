#pragma once

#include <getopt.h>
#include <libutility/options.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class Args
{
public:
	Args(std::vector<Option> options);
	bool has(const std::string &key) const;
	std::string get(const std::string &key, const std::string &fallback = "") const;
	void clear();
	void parse(int argc, char **argv);
	std::unordered_map<std::string, std::string> dump() const;

private:
	std::unordered_map<std::string, std::string> args;
	const std::vector<Option> options;
	std::unordered_map<char, int> short_to_longindex;
	std::string shortopts;
	std::vector<struct option> longopts;
};
