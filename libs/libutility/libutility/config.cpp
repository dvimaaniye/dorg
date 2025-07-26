#include <filesystem>
#include <fstream>
#include <iostream>
#include <liblogger/logger.hpp>
#include <libutility/config.hpp>
#include <ryml.hpp>
#include <ryml_std.hpp>
#include <sstream>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

Config::Config(const std::string &config_path)
{
	this->rules = this->parse_config(config_path);
}

void
Config::extend_config(const Config &other_config)
{
	for (const auto &[category_name, config_rule] : other_config.rules) {
		auto extensions = this->rules[category_name].extensions;
		this->rules[category_name] = config_rule;

		if (!config_rule.override) {
			this->rules[category_name].extensions.insert(
			  this->rules[category_name].extensions.end(), extensions.begin(), extensions.end()
			);
		}
	}
}

std::unordered_map<std::string, CategoryRule>
Config::parse_config(const std::string &config_path)
{
	std::unordered_map<std::string, CategoryRule> rules{};
	if (!fs::exists(config_path)) {
		DEBUG("config: " << config_path << " does not exist.\n");
		return rules;
	}

	std::ifstream file_stream{config_path};
	std::stringstream buffer;
	buffer << file_stream.rdbuf();
	std::string yml_content = buffer.str();

	ryml::Tree tree = ryml::parse_in_place(ryml::to_substr(yml_content));
	ryml::ConstNodeRef root = tree.crootref();
	ryml::ConstNodeRef categories_node = root["categories"];

	for (ryml::ConstNodeRef category_node : categories_node.children()) {
		CategoryRule rule;
		category_node["name"] >> rule.name;

		if (category_node.has_child("dir")) {
			category_node["dir"] >> rule.dir;
		} else {
			category_node["name"] >> rule.dir;
		}

		if (category_node.has_child("override")) {
			category_node["override"] >> rule.override;
		}

		if (category_node.has_child("extensions")) {
			category_node["extensions"] >> rule.extensions;
		}

		rules[rule.name] = rule;
	}

	return rules;
}
