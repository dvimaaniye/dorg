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
	return node->has(std::tolower(key)) ? node->get(std::tolower(key)) : node->get(std::toupper(key));
}

void
ReversedSuffixTrie::insert(std::string suffix, std::shared_ptr<TrieData> data)
{
	if (suffix.empty()) {
		return;
	}

	auto current = root.get();

	for (auto char_it = suffix.rbegin(); char_it != suffix.rend(); ++char_it) {
		if (!current->has(*char_it)) {
			current->insert(*char_it, std::make_unique<TrieNode>());
		}

		current = current->get(*char_it);
	}

	current->make_end(data);
}

TrieNode *
ReversedSuffixTrie::find_longest_suffix_match(std::string word)
{
	if (word.empty()) {
		return nullptr;
	}

	auto current = root.get();
	TrieNode *last_match = nullptr;

	for (auto char_it = word.rbegin(); char_it != word.rend(); ++char_it) {
		current = this->get(current, *char_it);
		if (current == nullptr) {
			break;
		}
		if (current->end) {
			last_match = current;
		}
	}

	return last_match;
}
