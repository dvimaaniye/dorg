#include <iostream>
#include <liblogger/logger.hpp>
#include <string>

LogLevel Logger::level = LogLevel::Info;

bool
Logger::should_log(LogLevel l)
{
	return level >= l;
}

std::ostream &
Logger::log(const std::string &tag)
{
	auto &stream = Logger::log();
	stream << tag;
	return stream;
}

std::ostream &
Logger::log()
{
	return std::cout;
}

std::ostream &
Logger::info(const std::string &tag)
{
	return Logger::log(tag);
}

std::ostream &
Logger::debug(const std::string &tag)
{
	return Logger::log(tag);
}

std::ostream &
Logger::error(const std::string &tag)
{
	std::cerr << tag;

	return std::cerr;
}
