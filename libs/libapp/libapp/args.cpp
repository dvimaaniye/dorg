#include <libapp/args.hpp>

const char *Args::shortopts = "s:d:m:h";

const struct option Args::longopts[] = { { "source", required_argument, nullptr, 's' },
	                                 { "dest", required_argument, nullptr, 'd' },
	                                 { "mode", required_argument, nullptr, 'm' },
	                                 { "help", no_argument, nullptr, 'h' },
	                                 { nullptr, 0, nullptr, 0 } };

void
Args::parse(int argc, char **argv)
{
	int opt;
	while ((opt = getopt_long(argc, argv, shortopts, longopts, nullptr)) != -1) {
		switch (opt) {
			case 's':
			case 'd':
			case 'm':
				args[opt] = optarg;
				break;
			case 'h':
				args[opt] = opt;
				break;
			default:
				break;
		}
	}
}

std::string
Args::get(char key, const std::string &fallback)
{
	auto it = args.find(key);
	if (it == args.end()) {
		return fallback;
	}
	return it->second;
}
