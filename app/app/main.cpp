#include <app/utility.hpp>
#include <cstdlib>
#include <libapp/args.hpp>
#include <libapp/mode.hpp>
#include <libapp/organizer.hpp>

int
main(int argc, char **argv)
{
	using std::cout, std::cerr, std::endl;

	Args::parse(argc, argv);

	if (Args::get('h', "0") == "h") {
		print_help(argv[0]);
		return EXIT_SUCCESS;
	}

	fs::path current_path = fs::current_path();
	fs::path source_path = Args::get('s', current_path.string());
	fs::path destination_path = Args::get('d', source_path.string());
	if (handle_destination_existence(destination_path) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	auto maybe_mode = Mode::from_string(Args::get('m', "extension"));
	if (!maybe_mode) {
		cerr << "Invalid mode: " << Args::get('m', "extension") << endl;
		return EXIT_FAILURE;
	}
	Mode::Name mode = *maybe_mode;

	print_args(source_path.string(),
	           destination_path.string(),
	           static_cast<std::string>(Mode::to_string(mode)));

	auto organizer = Organizer(source_path, destination_path, mode);
	organizer.organize_in_memory();
	organizer.apply();

	return 0;
}
