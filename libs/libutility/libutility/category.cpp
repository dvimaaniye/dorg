#include <boost/algorithm/string/case_conv.hpp>
#include <libutility/category.hpp>
#include <string>
#include <vector>

Category::Category(const std::string &_name, const std::vector<std::string> &_extensions) :
  Category::Category(_name, _name, _extensions)
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
