#pragma once

#include <libutility/config.hpp>
#include <pwd.h>
#include <string>
#include <unistd.h>
#include <unordered_map>

inline std::unordered_map<std::string, std::string_view>
make_extension_to_directory_map(const std::unordered_map<std::string, ConfigRule> &rules)
{
	std::unordered_map<std::string, std::string_view> extension_to_directory;
	for (const auto &[_, category] : rules) {
		std::string_view dir = category.dir;
		for (const auto &extension : category.extensions) {
			extension_to_directory[extension] = dir;
		}
	}
	return extension_to_directory;
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
