#pragma once

#include <getopt.h>
#include <string>
#include <unordered_map>

class Args
{
      public:
	static void parse(int argc, char **argv);
	static std::string get(char key, const std::string &fallback);

      private:
	static const char *shortopts;
	static const struct option longopts[];
	inline static std::unordered_map<char, std::string> args;
};
