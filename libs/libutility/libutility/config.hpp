#pragma once
#include <string>
#include <unordered_map>
#include <vector>

struct CategoryRule {
	std::string name;
	std::string dir;
	bool override = false;
	std::vector<std::string> extensions;
};

struct ConfigRule : CategoryRule {
};

struct Config {
	std::unordered_map<std::string, ConfigRule> rules;
	void extend_config(const Config &other_config);
	Config(const std::string &config_path);

private:
	std::unordered_map<std::string, ConfigRule> parse_config(const std::string &config_path);
};
