#include <app/utility.hpp>
#include <cstdlib>
#include <liborganizer/organizer.hpp>
#include <libutility/args.hpp>

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

	auto organizer = Organizer(source_path, destination_path);
	organizer.organize_in_memory();
	organizer.info();
	organizer.apply();

	return EXIT_SUCCESS;
}
