#pragma once

#include <libutility/category.hpp>
#include <string>
#include <unordered_map>

struct Config {
public:
	std::unordered_map<std::string, CategoryRule> rules;
	bool insensitive_case;

	void extend_config(const Config &other_config);
	Config(const std::string &config_path);

private:
	std::unordered_map<std::string, CategoryRule> parse_config(const std::string &config_path);
};
