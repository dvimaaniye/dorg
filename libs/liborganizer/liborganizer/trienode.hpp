#pragma once

#include <memory>
#include <string>
#include <unordered_map>

// constexpr const int NUM_VALID_CHARACTERS = 255 - 2; // '/' and '\0' not allowed

struct TrieNode {
	bool end;
	std::shared_ptr<std::string> category;
	std::shared_ptr<std::string> directory;
	std::unordered_map<char, std::unique_ptr<TrieNode>> data;

	TrieNode() : TrieNode::TrieNode(false, nullptr, nullptr)
	{
	}

	TrieNode(std::shared_ptr<std::string> category, std::shared_ptr<std::string> directory) :
	  TrieNode::TrieNode(false, category, directory)
	{
	}

	TrieNode(
	  bool end,
	  std::shared_ptr<std::string> category,
	  std::shared_ptr<std::string> directory
	) :
	  end(end),
	  category(category),
	  directory(directory)
	{
	}

	void set_end(bool e = true)
	{
		this->end = e;
	}

	bool has(char key) const
	{
		return data.find(key) != data.end();
	}

	TrieNode *get(char key)
	{
		return has(key) ? data[key].get() : nullptr;
	}

	void insert(char key, std::unique_ptr<TrieNode> node = nullptr)
	{
		if (key == '/' || key == '\0') {
			return;
		}
		data[key] = std::move(node);
	}
};
