#include <iostream>
#include <libutility/args.hpp>

Args::Args(const std::vector<Option> options) : options(options)
{
	for (auto opt : options) {
		if (opt.short_name != nullptr) {
			shortopts += opt.short_name[0];

			// no_argument = 0
			// required_argument = 1, :
			// optional_argument = 2, ::
			for (int i = 0; i < opt.has_arg; ++i) {
				shortopts += ":";
			}
		}

		if (opt.long_name != nullptr) {
			struct option long_opt = {opt.long_name, opt.has_arg, nullptr};

			if (opt.short_name == nullptr) {
				long_opt.val = 0;
			} else {
				long_opt.val = opt.short_name[0];
				short_to_longindex[opt.short_name[0]] = longopts.size();
			}

			longopts.push_back(long_opt);
		}
	}

	longopts.push_back({nullptr, 0, nullptr, 0});
	// for (const auto &long_opt : longopts) {
	// 	std::cout << long_opt.name << ", ";
	// 	std::cout << long_opt.has_arg << ", ";
	// 	std::cout << long_opt.flag << ", ";
	// 	std::cout << (char)long_opt.val << std::endl;
	// }
}

void
Args::parse(int argc, char **argv)
{
	int longindex;

	while (true) {
		longindex = -1;
		int opt = getopt_long(argc, argv, shortopts.c_str(), longopts.data(), &longindex);

		if (opt == -1) {
			break;
		}

		if (opt == '?' || opt == ':') {
			continue; // error cases: unknown option or missing argument
		}

		std::string key;

		// longindex is >= 0, only when a long option is matched in its long form.
		// In this case, opt is 0 because no short form was matched
		if (longindex >= 0) {
			key = longopts[longindex].name;
		} else if (opt > 0) {
			if (short_to_longindex.find(opt) == short_to_longindex.end()) {
				key = static_cast<char>(opt);
			} else {
				longindex = short_to_longindex.at(opt);
				key = longopts[longindex].name;
			}
		}

		args[key] = optarg ? optarg : "";
	}
}

bool
Args::has(const std::string &key) const
{
	auto it = args.find(key);
	if (it == args.end()) {
		return false;
	}
	return true;
}

std::string
Args::get(const std::string &key, const std::string &fallback) const
{
	auto it = args.find(key);
	if (it == args.end()) {
		return fallback;
	}
	return it->second;
}

std::unordered_map<std::string, std::string>
Args::dump() const
{
	return this->args;
}

void
Args::clear()
{
	args.clear();
}
