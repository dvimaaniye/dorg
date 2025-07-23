#include <app/main.hpp>
#include <cstdlib>
#include <liborganizer/organizer.hpp>
#include <libutility/args.hpp>
#include <libutility/category.hpp>
#include <libutility/config.hpp>
#include <libutility/fs_operations.hpp>
#include <libutility/print_help.hpp>
#include <memory>

int
main(int argc, char **argv)
{
	using std::cout, std::cerr, std::endl;

	Args args(argc, argv);

	if (args.get('h') == "h") {
		print_help(argv[0]);
		return EXIT_SUCCESS;
	}

	fs::path current_path = fs::current_path();
	fs::path source_path = args.get('s');
	if (source_path.empty()) {
		cout << "Source path is needed" << endl;
		print_help(argv[0]);
		return EXIT_FAILURE;
	}
	if (handle_directory_existence(source_path) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	fs::path destination_path = args.get('d', source_path.string());
	if (handle_directory_existence(destination_path) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	print_args(source_path.string(), destination_path.string());

	const std::string config_home = get_config_home();

	const std::string app_config_dir = config_home + "/dorg";

	const std::string DEFAULT_CONFIG_PATH = app_config_dir + "/default.yml";

	const std::string USER_CONFIG_PATH = app_config_dir + "/user.yml";

	Config config(DEFAULT_CONFIG_PATH);
	config.extend_config(Config(USER_CONFIG_PATH));

	auto extension_to_directory = make_extension_to_directory_map(config.rules);
	auto organizer = Organizer(
	  source_path,
	  destination_path,
	  std::make_shared<std::unordered_map<std::string, std::string_view>>(extension_to_directory)
	);
	organizer.organize_in_memory();
	organizer.info();
	organizer.show_layout();
	organizer.apply();

	return EXIT_SUCCESS;
}
