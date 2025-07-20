#pragma once

#include <getopt.h>
#include <string>
#include <unordered_map>

class Args
{
public:
	Args(int argc, char **argv);
	std::string get(char key) const;
	std::string get(char key, const std::string &fallback) const;
	void clear();

private:
	static std::unordered_map<char, std::string> parse(int argc, char **argv);
	static const char *shortopts;
	static const struct option longopts[];
	std::unordered_map<char, std::string> args;
};
