#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <liborganizer/organizer.hpp>
#include <libutility/fs_operations.hpp>
#include <string>
#include <unordered_set>
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
		  {"jpeg", "photo/jpeg", {".jpeg"}},
		  {"documents", "docs", {".doc", ".docx", ".odt"}},
		  {"tests", "tests", {".test.cpp", "_test.cpp"}},
		  {"code", "code", {".cpp", ".c", ".py", ".js", ".ts", ".html", ".css", ".go", ".php"}},
		  {"cg", "cg", {"blender", "fbx"}},
		};
	}

	std::vector<fs::path>
	get_test_files(fs::path source_dir, int n = 1, std::vector<Category> categories = {})
	{
		std::vector<fs::path> files;

		for (auto &category : categories) {
			for (auto &extension : category.extensions) {
				for (int i = 1; i <= n; ++i) {
					files.push_back(source_dir / (std::to_string(i) + extension));
				}
			}
		}

		return files;
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
	fs::path source = "/tmp/dorg-testing/";
	fs::path dest = "/tmp/dorg-testing/";
};

TEST_F(OrganizerTest, OrganizesFilesByDirectoryInMemory)
{
	fop::dry_run = false;
	fop::handle_directory_existence(source, false);
	fop::handle_directory_existence(dest, false);

	constexpr const int FILES_PER_EXTENSION = 1;
	auto categories = get_categories();

	int total_files_in_categories = 0;
	for (auto &category : categories) {
		total_files_in_categories += category.extensions.size() * FILES_PER_EXTENSION;
	}

	Organizer organizer = Organizer(categories);

	auto file_paths = get_test_files(source, FILES_PER_EXTENSION, get_categories());
	organizer.organize_in_memory(file_paths);

	auto organized_structure = organizer.dump_structure();

	int total_files_organized = 0;
	for (auto &[_, files] : organized_structure) {
		total_files_organized += files.size();
	}

	ASSERT_EQ(total_files_in_categories, total_files_organized)
	  << "Mismatch in number of organized files.";

	for (const auto &category : categories) {
		const auto &dir_name = category.dir;
		const auto &extensions = category.extensions;

		auto it = organized_structure.find(dir_name);
		ASSERT_NE(it, organized_structure.end()) << "Missing directory in structure: " << dir_name;

		const auto &files_in_dir = it->second;

		std::unordered_set<fs::path> actual_files(files_in_dir.begin(), files_in_dir.end());

		std::unordered_set<fs::path> expected_files;
		for (const auto &ext : extensions) {
			for (int i = 1; i <= FILES_PER_EXTENSION; ++i) {
				expected_files.insert(source / (std::to_string(i) + ext));
			}
		}

		ASSERT_EQ(expected_files, actual_files)
		  << "Mismatch in files organized under directory: " << dir_name;
	}
}
