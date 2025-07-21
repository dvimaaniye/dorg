#include <gtest/gtest.h>
#include <libutility/category.hpp>

// std::unordered_map<Category::Name, std::vector<fs::path>>
// categorize_by_extension(const fs::path &source_path);

TEST(CategoryTest, CategorizeByExtension) {}

TEST(CategoryTest, CategoryFromExtension)
{
	EXPECT_EQ(Category::category_from_extension("ttf"), Category::Name::unknown);

	EXPECT_EQ(Category::category_from_extension("mp3"), Category::Name::audio);
	EXPECT_EQ(Category::category_from_extension("mP3"), Category::Name::audio);
	EXPECT_EQ(Category::category_from_extension("wav"), Category::Name::audio);

	EXPECT_EQ(Category::category_from_extension("doc"), Category::Name::document);
	EXPECT_EQ(Category::category_from_extension("docx"), Category::Name::document);

	EXPECT_EQ(Category::category_from_extension("png"), Category::Name::photo);
	EXPECT_EQ(Category::category_from_extension("jpg"), Category::Name::photo);
	EXPECT_EQ(Category::category_from_extension("JPG"), Category::Name::photo);

	EXPECT_EQ(Category::category_from_extension("ppt"), Category::Name::presentation);
	EXPECT_EQ(Category::category_from_extension("pptx"), Category::Name::presentation);

	EXPECT_EQ(Category::category_from_extension("mp4"), Category::Name::video);
	EXPECT_EQ(Category::category_from_extension("mkv"), Category::Name::video);
}

TEST(CategoryTest, DirectoryNameFromCategory)
{
	EXPECT_FALSE(Category::directory_name_from_category(Category::Name::unknown).has_value());

	EXPECT_EQ("audios", Category::directory_name_from_category(Category::Name::audio).value());
	EXPECT_EQ("documents", Category::directory_name_from_category(Category::Name::document).value());
	EXPECT_EQ("photos", Category::directory_name_from_category(Category::Name::photo).value());
	EXPECT_EQ("presentations",
	          Category::directory_name_from_category(Category::Name::presentation).value());
	EXPECT_EQ("videos", Category::directory_name_from_category(Category::Name::video).value());
	EXPECT_EQ("zips", Category::directory_name_from_category(Category::Name::zip).value());
}

TEST(CategoryTest, ToStringConversion)
{
	EXPECT_EQ("unknown", Category::to_string(Category::Name::unknown));
	EXPECT_EQ("audio", Category::to_string(Category::Name::audio));
	EXPECT_EQ("document", Category::to_string(Category::Name::document));
	EXPECT_EQ("photo", Category::to_string(Category::Name::photo));
	EXPECT_EQ("presentation", Category::to_string(Category::Name::presentation));
	EXPECT_EQ("video", Category::to_string(Category::Name::video));
	EXPECT_EQ("zip", Category::to_string(Category::Name::zip));
}
