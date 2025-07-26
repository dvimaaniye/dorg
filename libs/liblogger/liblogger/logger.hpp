#pragma once

#include <iostream>
#include <string>

enum class LogLevel { Quiet = 0, Info = 1, Debug = 2 };

#define ERROR(X) Logger::error() << X;
// U stands for un-tagged where tag is the [ERROR] style string
#define UERROR(X) Logger::error("") << X;

#define INFO(X)                             \
	if (Logger::should_log(LogLevel::Info)) { \
		Logger::info() << X;                    \
	}

#define UINFO(X)                            \
	if (Logger::should_log(LogLevel::Info)) { \
		Logger::info("") << X;                  \
	}

#define DEBUG(X)                             \
	if (Logger::should_log(LogLevel::Debug)) { \
		Logger::debug() << X;                    \
	}

#define UDEBUG(X)                            \
	if (Logger::should_log(LogLevel::Debug)) { \
		Logger::debug("") << X;                  \
	}

class Logger
{
public:
	static LogLevel level;
	static bool should_log(LogLevel l);
	static std::ostream &log(const std::string &tag);
	static std::ostream &log();
	static std::ostream &info(const std::string &tag = "[INFO] ");
	static std::ostream &debug(const std::string &tag = "[DEBUG] ");
	static std::ostream &error(const std::string &tag = "[ERROR] ");
};
