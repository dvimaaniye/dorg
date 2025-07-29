#include <app/main.hpp>
#include <filesystem>
#include <liblogger/logger.hpp>
#include <liborganizer/organizer.hpp>
#include <libutility/args.hpp>
#include <libutility/category.hpp>
#include <libutility/config.hpp>
#include <libutility/fs_operations.hpp>
#include <libutility/print_help.hpp>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

int
main(int argc, char **argv)
{
	if (argc == 2 && std::string(argv[1]) == "get-config") {
		DEBUG("Printing default config.\n");
		print_default_config();
		return EXIT_SUCCESS;
	}

	Args args(options);
	args.parse(argc, argv);
	DEBUG("Parsed cli arguments.\n")

	// if quiet and verbose are both set OR are both not set, then set log level to Info
	if (!(args.has("quiet") ^ args.has("verbose"))) {
		Logger::level = LogLevel::Info;
		DEBUG("Log level set to Info.\n");
	} else if (args.has("quiet")) {
		Logger::level = LogLevel::Quiet;
		DEBUG("Log level set to Quiet.\n");
	} else if (args.has("verbose")) { // doing the check for clarity, logically not required
		Logger::level = LogLevel::Debug;
		DEBUG("Log level set to Debug.\n");
	}

	if (args.has("help")) {
		DEBUG("Printing help.\n");
		print_help(argv[0]);
		return EXIT_SUCCESS;
	}

	fop::dry_run = args.has("dry-run");

	fs::path source_path = args.get("source");
	if (source_path.empty()) {
		ERROR("Missing source path.\n");
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	if (!fs::exists(source_path)) {
		ERROR(source_path << " does not exist.\n");
		return EXIT_FAILURE;
	}

	fs::path destination_path = args.has("dest") ? args.get("dest") : source_path.string();
	if (fop::handle_directory_existence(destination_path) == EXIT_FAILURE) {
		ERROR("Destination directory " << destination_path << " does not exist.\n");
		return EXIT_FAILURE;
	}

	const std::string config_home = get_config_home();

	const std::string app_config_dir = config_home + "/dorg";

	const std::string DEFAULT_CONFIG_PATH = app_config_dir + "/default.yml";

	std::string USER_CONFIG_PATH;

	if (args.has("config")) {
		USER_CONFIG_PATH = args.get("config");

		if (!fs::exists(USER_CONFIG_PATH)) {
			ERROR(USER_CONFIG_PATH << " does not exist.\n");

			return EXIT_FAILURE;
		}
	} else {
		USER_CONFIG_PATH = app_config_dir + "/user.yml";
	}

	Config user_config(USER_CONFIG_PATH);
	Config master_config(DEFAULT_CONFIG_PATH);
	master_config.extend_config(user_config);

	bool override = args.has("override");
	bool skip = args.has("skip");

	if (override && skip) {
		ERROR("Only one of \"override\" and \"skip\" is allowed at a time.\n");
		return EXIT_FAILURE;
	}

	OverrideOptions override_option = OverrideOptions::NOT_SET;
	if (override) {
		override_option = OverrideOptions::OVERWRITE;
	} else if (skip) {
		override_option = OverrideOptions::SKIP;
	}

	std::vector<Category> categories(master_config.rules.size());

	for (auto &[_, rule] : master_config.rules) {
		categories.push_back(rule);
	}

	bool insensitive_case = args.has("insensitive-case");

	auto organizer = Organizer(categories, insensitive_case);

	organizer.organize_in_memory(source_path);
	organizer.info();
	organizer.show_layout();
	organizer.apply(destination_path, override_option);

	return EXIT_SUCCESS;
}
