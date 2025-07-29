#pragma once

#include <boost/algorithm/string/case_conv.hpp>
#include <cstdlib>
#include <iostream>
#include <libutility/config.hpp>
#include <libutility/default_config.hpp>
#include <pwd.h>
#include <string>

inline void
print_default_config()
{
	std::cout << default_config;
};

inline std::string
get_env_str(std::string const &key)
{
	char *val = std::getenv(key.c_str());
	return val == NULL ? std::string("") : std::string(val);
}

inline std::string
get_config_home()
{
	std::string config_home = get_env_str("XDG_CONFIG_HOME");

	if (config_home.empty()) {
		config_home = get_env_str("HOME");

		if (config_home.empty()) {
			config_home = getpwuid(getuid())->pw_dir;
		}

		config_home += "/.config";
	}

	return config_home;
}

int
main(int argc, char **argv);
