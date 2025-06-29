#pragma once

#include <filesystem>
#include <optional>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

#define CATEGORY_LIST \
	X(unknown)          \
	X(audio)            \
	X(document)         \
	X(photo)            \
	X(presentation)     \
	X(video)            \
	X(zip)

namespace Category
{
enum class Name {
#define X(name) name,
	CATEGORY_LIST
#undef X
};

std::unordered_map<Name, std::vector<fs::path>>
categorize_by_extension(const fs::path &source_path);

std::unordered_map<Name, std::vector<fs::path>>
categorize_by_header(const fs::path &source_path);

Name
category_from_extension(std::string ext);

std::optional<std::string>
directory_name_from_category(Name cat);

std::string
to_string(const Name &cat);

} // namespace Category

std::ostream &
operator<<(std::ostream &os, Category::Name cat);
