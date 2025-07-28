#pragma once

#include <boost/algorithm/string/case_conv.hpp>
#include <cstdlib>
#include <iostream>
#include <libutility/config.hpp>
#include <libutility/default_config.hpp>
#include <pwd.h>
#include <string>
#include <unordered_map>

inline void
print_default_config()
{
	std::cout << default_config;
};

inline std::unordered_map<std::string, std::string>
make_extension_to_directory_map(
  const std::unordered_map<std::string, CategoryRule> &rules,
  bool insensitive_case = false
)
{
	std::unordered_map<std::string, std::string> extension_to_directory;
	for (const auto &[_, category] : rules) {
		std::string dir = category.dir;
		for (const auto &extension : category.extensions) {
			extension_to_directory[insensitive_case ? boost::to_lower_copy(extension) : extension] = dir;
		}
	}
	return extension_to_directory;
}

inline void
extend_extension_to_directory_map(
  std::unordered_map<std::string, std::string> &map1,
  const std::unordered_map<std::string, std::string> &map2,
  bool override = true
)
{
	for (const auto &[extension, directory] : map2) {
		if (!override && map1.find(extension) != map1.end()) {
			continue;
		}

		map1[extension] = directory;
	}
}

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
