#include <gtest/gtest.h>
#include <initializer_list>
#include <libapp/args.hpp>
#include <vector>

class ArgsTest : public testing::Test
{
protected:
	Args parse_raw_args(std::initializer_list<const char *> raw_args)
	{
		std::vector<char *> argv = { const_cast<char *>("program") };
		for (const char *arg : raw_args) {
			argv.push_back(const_cast<char *>(arg));
		}
		return Args(argv.size(), argv.data());
	}
};

TEST_F(ArgsTest, ParsesShortSourceOption)
{
	Args args = parse_raw_args({ "-s", "source" });
	EXPECT_EQ(args.get('s'), "source");
}

TEST_F(ArgsTest, ParsesLongSourceOption)
{
	Args args = parse_raw_args({ "--source", "source" });
	EXPECT_EQ(args.get('s'), "source");
}

TEST_F(ArgsTest, ParsesShortDestinationOption)
{
	Args args = parse_raw_args({ "-d", "destination" });
	EXPECT_EQ(args.get('d'), "destination");
}

TEST_F(ArgsTest, ParsesLongDestinationOption)
{
	Args args = parse_raw_args({ "--destination", "destination" });
	EXPECT_EQ(args.get('d'), "destination");
}

TEST_F(ArgsTest, ParsesShortModeOption)
{
	Args args = parse_raw_args({ "-m", "mode" });
	EXPECT_EQ(args.get('m'), "mode");
}

TEST_F(ArgsTest, ParsesLongModeOption)
{
	Args args = parse_raw_args({ "--mode", "mode" });
	EXPECT_EQ(args.get('m'), "mode");
}

TEST_F(ArgsTest, ParsesShortHelpOption)
{
	Args args = parse_raw_args({ "-h" });
	EXPECT_EQ(args.get('h'), "h");
}

TEST_F(ArgsTest, ParsesLongHelpOption)
{
	Args args = parse_raw_args({ "--help" });
	EXPECT_EQ(args.get('h'), "h");
}
