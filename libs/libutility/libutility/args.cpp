#include <libutility/args.hpp>

const char *Args::shortopts = "s:d:h";

const struct option Args::longopts[] = { { "source", required_argument, nullptr, 's' },
	                                       { "destination", required_argument, nullptr, 'd' },
	                                       { "help", no_argument, nullptr, 'h' },
	                                       { nullptr, 0, nullptr, 0 } };

Args::Args(int argc, char **argv)
{
	this->args = parse(argc, argv);
}

std::unordered_map<char, std::string>
Args::parse(int argc, char **argv)
{
	std::unordered_map<char, std::string> args;
	int opt;
	while ((opt = getopt_long(argc, argv, shortopts, longopts, nullptr)) != -1) {
		switch (opt) {
			case 's':
			case 'd':
				args[opt] = optarg;
				break;
			case 'h':
				args[opt] = opt;
				break;
			default:
				break;
		}
	}
	return args;
}

std::string
Args::get(char key) const
{
	auto it = args.find(key);
	if (it == args.end()) {
		return "";
	}
	return it->second;
}

std::string
Args::get(char key, const std::string &fallback) const
{
	auto it = args.find(key);
	if (it == args.end()) {
		return fallback;
	}
	return it->second;
}

void
Args::clear()
{
	args.clear();
}
