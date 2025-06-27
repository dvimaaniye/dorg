#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <iostream>
#include <libcategory/category.hpp>
#include <libcategory/mappings.hpp>

namespace Category
{
std::unordered_map<Category::Name, std::vector<fs::path>>
categorize_by_extension(const fs::path &source_path)
{
	std::unordered_map<Category::Name, std::vector<fs::path>> categorized;

	for (auto const &entry : fs::directory_iterator{ source_path }) {
		std::string ext = entry.path().extension();
		boost::trim_left_if(ext, boost::is_any_of("."));
		Name category = Category::category_from_extension(ext);
		if (category == Category::Name::unknown) {
			continue;
		}
		categorized[category].push_back(entry.path());
	}
	return categorized;
}

std::unordered_map<Category::Name, std::vector<fs::path>>
categorize_by_header(const fs::path &source_path)
{
	std::cout << "categoring by header" << std::endl;
	return Category::categorize_by_extension(source_path);
}

Category::Name
category_from_extension(std::string ext)
{
	boost::to_lower(ext);
	auto it = extension_to_category.find(ext);
	return it != extension_to_category.end() ? it->second : Category::Name::unknown;
}

std::optional<std::string>
directory_name_from_category(Category::Name cat)
{
	auto it = category_to_directory.find(cat);
	if (it == category_to_directory.end()) {
		return std::nullopt;
	}
	return it->second;
}

std::string
to_string(const Category::Name &cat)
{
	switch (cat) {
#define X(name)                    \
	case Category::Name::name: \
		return #name;
		CATEGORY_LIST
#undef X
	}
	return "unknown";
}

} // namespace Category

std::ostream &
operator<<(std::ostream &os, Category::Name cat)
{
	return os << Category::to_string(cat);
}
