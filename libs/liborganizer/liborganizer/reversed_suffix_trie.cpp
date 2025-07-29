#include <cctype>
#include <liborganizer/reversed_suffix_trie.hpp>
#include <liborganizer/trienode.hpp>
#include <memory>
#include <string>

ReversedSuffixTrie::ReversedSuffixTrie()
{
	this->root = std::make_unique<TrieNode>();
}

void
ReversedSuffixTrie::set_insensitive_case(bool c)
{
	this->insensitive_case = c;
}

TrieNode *
ReversedSuffixTrie::get(TrieNode *node, char key)
{
	if (!this->insensitive_case) {
		return node->get(key);
	}
	// lowercase is the normalized case
	// in insensitive case, first the key is normalized to lowercase
	// if lowercase key is not found then uppercase key is tried
	// therefore, JPG will be treated as jpg
	return node->has(tolower(key)) ? node->get(tolower(key)) : node->get(toupper(key));
}

void
ReversedSuffixTrie::insert(std::string suffix, std::unique_ptr<TrieNode> node)
{
	if (suffix.empty()) {
		return;
	}

	auto current = root.get();

	for (auto it = suffix.rbegin(); it != suffix.rend() - 1; ++it) {
		if (!current->has(*it)) {
			current->insert(*it, std::make_unique<TrieNode>());
		}

		current = current->get(*it);
	}

	node->set_end();
	current->insert(suffix[0], std::move(node));
}

TrieNode *
ReversedSuffixTrie::find_longest_suffix_match(std::string word)
{
	if (word.empty()) {
		return nullptr;
	}

	auto current = root.get();
	TrieNode *last_match = nullptr;

	for (auto it = word.rbegin(); it != word.rend(); ++it) {
		current = this->get(current, *it);
		if (current == nullptr) {
			break;
		}
		if (current->end) {
			last_match = current;
		}
	}

	return last_match;
}
