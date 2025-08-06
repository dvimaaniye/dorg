#pragma once

#include <memory>
#include <string>
#include <unordered_map>

// constexpr const int NUM_VALID_CHARACTERS = 255 - 2; // '/' and '\0' not allowed

struct TrieData {
	std::shared_ptr<std::string> category;
	std::shared_ptr<std::string> directory;

	TrieData(std::shared_ptr<std::string> category, std::shared_ptr<std::string> directory) :
	  category(category),
	  directory(directory)
	{
	}

	TrieData() : TrieData(nullptr, nullptr)
	{
	}
};

struct TrieNode {
	bool end;
	std::shared_ptr<TrieData> data;
	std::unordered_map<char, std::unique_ptr<TrieNode>> children;

	TrieNode(
	  bool end,
	  std::shared_ptr<std::string> category,
	  std::shared_ptr<std::string> directory
	) :
	  end(end)
	{
		data = std::make_shared<TrieData>(category, directory);
	}

	TrieNode(std::shared_ptr<std::string> category, std::shared_ptr<std::string> directory) :
	  TrieNode(false, category, directory)
	{
	}

	TrieNode() : TrieNode(false, nullptr, nullptr)
	{
	}

	void set_end(bool e = true)
	{
		this->end = e;
	}

	void make_end(std::shared_ptr<TrieData> data)
	{
		this->set_end();
		this->data = data;
	}

	bool has(char key) const
	{
		return children.find(key) != children.end();
	}

	TrieNode *get(char key)
	{
		return has(key) ? children[key].get() : nullptr;
	}

	void insert(char key, std::unique_ptr<TrieNode> node = nullptr)
	{
		if (key == '/' || key == '\0') {
			return;
		}
		children[key] = std::move(node);
	}
};
