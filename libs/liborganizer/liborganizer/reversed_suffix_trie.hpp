#pragma once

#include <liborganizer/trienode.hpp>
#include <memory>
#include <string>

class ReversedSuffixTrie
{
public:
	ReversedSuffixTrie();

	void set_insensitive_case(bool c = true);
	void insert(std::string suffix, std::unique_ptr<TrieNode> node);
	TrieNode *find_longest_suffix_match(std::string word);

private:
	std::unique_ptr<TrieNode> root;
	bool insensitive_case;
	TrieNode *get(TrieNode *node, char key);
};
