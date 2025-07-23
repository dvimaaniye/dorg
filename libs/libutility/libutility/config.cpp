#include <filesystem>
#include <fstream>
#include <iostream>
#include <libutility/config.hpp>
#include <ryml.hpp>
#include <ryml_std.hpp>
#include <sstream>

namespace fs = std::filesystem;

Config::Config(const std::string &config_path)
{
	this->rules = this->parse_config(config_path);
}

void
Config::extend_config(const Config &other_config)
{
	for (const auto &[category_name, config_rule] : other_config.rules) {
		if ((this->rules.find(category_name) == this->rules.end()) || (config_rule.override)) {
			this->rules[category_name] = config_rule;
		} else {
			// override is false and rule already exists, extend the extensions
			this->rules[category_name].extensions.insert(
			  this->rules[category_name].extensions.end(),
			  config_rule.extensions.begin(),
			  config_rule.extensions.end()
			);
		}
	}
}

std::unordered_map<std::string, ConfigRule>
Config::parse_config(const std::string &config_path)
{
	std::unordered_map<std::string, ConfigRule> rules{};
	if (!fs::exists(config_path)) {
		std::cout << "config: " << config_path << " does not exist." << std::endl;
		return rules;
	}

	std::ifstream file_stream{config_path};
	std::stringstream buffer;
	buffer << file_stream.rdbuf();
	std::string yml_content = buffer.str();

	ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(yml_content));
	ryml::ConstNodeRef root = tree.crootref();
	ryml::ConstNodeRef categories_node = root["categories"];

	for (ryml::ConstNodeRef category_node : categories_node.children()) {
		ConfigRule rule;
		category_node["name"] >> rule.name;

		if (category_node.has_child("dir")) {
			category_node["dir"] >> rule.dir;
		} else {
			category_node["name"] >> rule.dir;
		}

		if (category_node.has_child("override")) {
			category_node["override"] >> rule.override;
		}

		category_node["extensions"] >> rule.extensions;

		rules[rule.name] = rule;
	}

	return rules;
}
