#include <boost/algorithm/string/case_conv.hpp>
#include <libutility/category.hpp>

Category::Category(const std::string &_name, const std::vector<std::string> &_extensions)
  : Category::Category(_name, _name, _extensions)
{
}

Category::Category(
  const std::string &_name,
  const std::string &_dir,
  const std::vector<std::string> &_extensions
)
{
	name = _name;
	dir = _dir;
	for (const std::string &extension : _extensions) {
		extensions.insert(boost::to_lower_copy(extension));
	}
}

bool
Category::has(const std::string &extension)
{
	return extensions.count(extension) > 0;
}

// namespace Category
// {
// std::unordered_map<Category::Name, std::vector<fs::path>>
// categorize_by_extension(const std::vector<fs::path> &file_paths)
// {
// 	using std::cout, std::endl;
// 	std::unordered_map<Category::Name, std::vector<fs::path>> categorized;
//
// 	for (const auto &path : file_paths) {
// 		std::string ext = path.extension();
// 		boost::trim_left_if(ext, boost::is_any_of("."));
// 		Category::Name category = Category::category_of(ext);
// 		if (category == Category::Name::unknown) {
// 			cout << "Unknown extension: " << ext << endl;
// 			continue;
// 		}
// 		categorized[category].push_back(path);
// 	}
// 	return categorized;
// }
//
// std::unordered_map<Category::Name, std::vector<fs::path>>
// categorize_by_extension(const fs::path &source_path)
// {
// 	std::vector<fs::path> paths;
//
// 	for (const auto &entry : fs::directory_iterator{ source_path }) {
// 		paths.push_back(entry.path());
// 	}
//
// 	return categorize_by_extension(paths);
// }
//
// Category::Name
// category_of(std::string ext)
// {
// 	boost::to_lower(ext);
// 	auto it = extension_to_category.find(ext);
// 	return it != extension_to_category.end() ? it->second : Category::Name::unknown;
// }
//
// std::string
// directory_name_from_category(Category::Name cat)
// {
// 	auto it = category_to_directory.find(cat);
// 	if (it == category_to_directory.end()) {
// 		return "";
// 	}
// 	return it->second;
// }
//
// std::string
// to_string(const Category::Name &cat)
// {
// 	switch (cat) {
// #define X(name)              \
// 	case Category::Name::name: \
// 		return #name;
// 		CATEGORY_LIST
// #undef X
// 	}
// 	return "unknown";
// }
//
// } // namespace Category
//
// std::ostream &
// operator<<(std::ostream &os, Category::Name cat)
// {
// 	return os << Category::to_string(cat);
// }
