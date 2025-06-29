#include <gtest/gtest.h>
#include <libapp/mode.hpp>

TEST(ModeTest, ToStringConversion)
{
	EXPECT_EQ(Mode::to_string(Mode::Name::extension), "extension");
	EXPECT_EQ(Mode::to_string(Mode::Name::header), "header");
}

TEST(ModeTest, FromStringConversionValid)
{
	EXPECT_EQ(Mode::from_string("extension"), Mode::Name::extension);
	EXPECT_EQ(Mode::from_string("HEADER"), Mode::Name::header);
}

TEST(ModeTest, FromStringConversionInvalid)
{
	EXPECT_EQ(Mode::from_string("invalid"), std::nullopt);
	EXPECT_EQ(Mode::from_string("extensions"), std::nullopt);
	EXPECT_EQ(Mode::from_string(""), std::nullopt);
}
