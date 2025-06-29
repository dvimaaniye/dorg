#include <app/utility.hpp>
#include <cstdlib>
#include <libapp/args.hpp>
#include <libapp/mode.hpp>
#include <libapp/organizer.hpp>

int
main(int argc, char **argv)
{
	using std::cout, std::cerr, std::endl;

	Args args(argc, argv);

	if (args.get('h') == "h") {
		print_help(argv[0]);
		return EXIT_SUCCESS;
	}

	auto maybe_mode = Mode::from_string(args.get('m', "extension"));
	if (!maybe_mode) {
		cerr << "Invalid mode: " << args.get('m') << endl;
		return EXIT_FAILURE;
	}
	Mode::Name mode = *maybe_mode;

	fs::path current_path = fs::current_path();
	fs::path source_path = args.get('s', current_path.string());
	if (handle_directory_existence(source_path) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	fs::path destination_path = args.get('d', source_path.string());
	if (handle_directory_existence(destination_path) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	print_args(source_path.string(), destination_path.string(), Mode::to_string(mode));

	auto organizer = Organizer(source_path, destination_path, mode);
	organizer.organize_in_memory();
	organizer.info();
	organizer.apply();

	return EXIT_SUCCESS;
}
