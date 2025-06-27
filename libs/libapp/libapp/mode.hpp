#pragma once

#include <boost/algorithm/string/case_conv.hpp>
#include <optional>
#include <string>
#include <string_view>

namespace Mode
{
enum class Name {
	extension,
	header,
};

inline std::string_view
to_string(Name m)
{
	switch (m) {
		case Name::extension:
			return "extension";
		case Name::header:
			return "header";
	}
	return "";
}

inline std::optional<Name>
from_string(const std::string &str)
{
	std::string s = boost::to_lower_copy(str);
	if (s == "extension") {
		return Name::extension;
	}
	if (s == "header") {
		return Name::header;
	}
	return std::nullopt;
}
} // namespace Mode
