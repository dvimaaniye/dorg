#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <liborganizer/organizer.hpp>
#include <libutility/fs_operations.hpp>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class OrganizerTest : public testing::Test
{
public:
	std::vector<Category> get_categories()
	{
		return {
		  {"audio", "audio", {".mp3", ".wav", ".ogg"}},
		  {"video", "video", {".mp4", ".mkv", ".mov"}},
		  {"photo", "photo", {".jpg", ".png", ".webp"}},
		  {"documents", "docs", {".doc", ".docx", ".odt"}},
		  {"tests", "tests", {".test.cpp", "_test.cpp"}},
		};
	}

	void make_test_files(fs::path source_dir, int n = 1, std::vector<Category> categories = {})
	{
		for (auto &category : categories) {
			for (auto &extension : category.extensions) {
				for (int i = 1; i <= n; ++i) {
					std::ofstream file(source_dir / (std::to_string(i) + extension));
					file.close();
				}
			}
		}
	}

	void destroy_test_files(fs::path source_dir, int n = 1, std::vector<Category> categories = {})
	{
		for (auto &category : categories) {
			for (auto &extension : category.extensions) {
				for (int i = 1; i <= n; ++i) {
					fs::remove(source_dir / (std::to_string(i) + extension));
				}
			}
		}
	}

protected:
	std::string source = "/tmp/dorg-testing/";
	std::string dest = "/tmp/dorg-testing/";
};

TEST_F(OrganizerTest, OrganizesFilesByDirectoryInMemory)
{
	fop::dry_run = false;
	fop::handle_directory_existence(source, false);
	fop::handle_directory_existence(dest, false);

	constexpr const int FILES_PER_EXTENSION = 100;
	auto categories = get_categories();
	make_test_files(source, FILES_PER_EXTENSION, categories);

	int total_files_in_categories = 0;
	for (auto &category : categories) {
		total_files_in_categories += category.extensions.size() * FILES_PER_EXTENSION;
	}

	Organizer organizer = Organizer(categories);

	organizer.organize_in_memory(source);
	auto organized_structure = organizer.dump_structure();

	int total_files_organized = 0;
	for (auto &[_, files] : organized_structure) {
		total_files_organized += files.size();
	}

	EXPECT_EQ(total_files_in_categories, total_files_organized);

	destroy_test_files(source, FILES_PER_EXTENSION, categories);
}
