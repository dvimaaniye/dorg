#include <app/main.hpp>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <liborganizer/organizer.hpp>
#include <libutility/fs_operations.hpp>
#include <libutility/print_help.hpp>
#include <memory>

namespace fs = std::filesystem;

int
main(int argc, char **argv)
{
	using std::cout, std::cerr, std::endl;

	if (std::string(argv[1]) == "get-config") {
		print_default_config();
		return EXIT_SUCCESS;
	}

	Args args(options);
	args.parse(argc, argv);

	if (args.has("help")) {
		print_help(argv[0]);
		return EXIT_SUCCESS;
	}

	fs::path current_path = fs::current_path();
	fs::path source_path = args.get("source");
	if (source_path.empty()) {
		cerr << "Source path is needed" << endl;
		print_help(argv[0]);
		return EXIT_FAILURE;
	}

	if (!fs::exists(source_path)) {
		return EXIT_FAILURE;
	}

	fs::path destination_path = args.has("dest") ? args.get("dest") : source_path.string();
	if (handle_directory_existence(destination_path) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	const std::string config_home = get_config_home();

	const std::string app_config_dir = config_home + "/dorg";

	const std::string DEFAULT_CONFIG_PATH = app_config_dir + "/default.yml";

	std::string USER_CONFIG_PATH;

	if (args.has("config")) {
		USER_CONFIG_PATH = args.get("config");

		if (!fs::exists(USER_CONFIG_PATH)) {
			cerr << USER_CONFIG_PATH << " does not exist." << endl;

			return EXIT_FAILURE;
		}
	} else {
		USER_CONFIG_PATH = app_config_dir + "/user.yml";
	}

	Config user_config(USER_CONFIG_PATH);
	Config default_config(DEFAULT_CONFIG_PATH);
	default_config.extend_config(user_config);

	bool insensitive_case = args.has("insensitive-case");

	auto extension_to_directory = make_extension_to_directory_map(
	  default_config.rules, insensitive_case
	);
	auto user_extension_to_directory = make_extension_to_directory_map(
	  user_config.rules, insensitive_case
	);

	extend_extension_to_directory_map(extension_to_directory, user_extension_to_directory);

	bool override = args.has("override");
	bool skip = args.has("skip");

	if (override && skip) {
		cerr << "Only one of \"override\" and \"skip\" is allowed at a time." << endl;
		return EXIT_FAILURE;
	}

	OverrideOptions override_option = OverrideOptions::NOT_SET;
	if (override) {
		override_option = OverrideOptions::OVERWRITE;
	} else if (skip) {
		override_option = OverrideOptions::SKIP;
	}

	auto organizer = Organizer(
	  source_path,
	  destination_path,
	  std::make_shared<std::unordered_map<std::string, std::string_view>>(extension_to_directory)
	);

	organizer.organize_in_memory(insensitive_case);
	organizer.info();
	organizer.show_layout();
	organizer.apply(override_option);

	return EXIT_SUCCESS;
}
