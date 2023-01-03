#ifndef IZY_LOGGING
#define IZY_LOGGING


#include <time.h>
#include <chrono>
#include <iostream>
#include <source_location>
#include <string_view>
#include <fstream>
#include <sstream>
#include <mutex>


class IzyLogger
{
public:
#ifdef NDEBUG
	///////////////////////////// write to both cout and log file /////////////////////////////
	inline static void logFatal(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logError(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logWarn(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logInfo(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logDebug(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logTrace(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	///////////////////////////// write to log file ///////////////////////////////////////////
	inline static void logFatalToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logErrorToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logWarnToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logInfoToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logDebugToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logTraceToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }


	///////////////////////////// write to outstream //////////////////////////////////////////
	inline static void logFatalToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logErrorToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logWarnToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logInfoToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logDebugToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }

	inline static void logTraceToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{ }
#else
	///////////////////////////// write to both cout and log file /////////////////////////////
	inline static void logFatal(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::LogToBoth(Level::fatal, msg, location);
	}

	inline static void logError(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::LogToBoth(Level::error, msg, location);
	}

	inline static void logWarn(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::LogToBoth(Level::warn, msg, location);
	}

	inline static void logInfo(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::LogToBoth(Level::info, msg, location);
	}

	inline static void logDebug(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::LogToBoth(Level::debug, msg, location);
	}

	inline static void logTrace(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::LogToBoth(Level::trace, msg, location);
	}

	///////////////////////////// write to log file ///////////////////////////////////////////
	inline static void logFatalToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::logFile_s);
		IzyLogger::Log(fOut, Level::fatal, msg, location);
	}

	inline static void logErrorToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::logFile_s);
		IzyLogger::Log(fOut, Level::error, msg, location);
	}

	inline static void logWarnToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::logFile_s);
		IzyLogger::Log(fOut, Level::warn, msg, location);
	}

	inline static void logInfoToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::logFile_s);
		IzyLogger::Log(fOut, Level::info, msg, location);
	}

	inline static void logDebugToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::logFile_s);
		IzyLogger::Log(fOut, Level::debug, msg, location);
	}

	inline static void logTraceToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::logFile_s);
		IzyLogger::Log(fOut, Level::trace, msg, location);
	}


	///////////////////////////// write to outstream //////////////////////////////////////////
	inline static void logFatalToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::fatal, msg, location);
	}

	inline static void logErrorToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::error, msg, location);
	}

	inline static void logWarnToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::warn, msg, location);
	}

	inline static void logInfoToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::info, msg, location);
	}

	inline static void logDebugToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::debug, msg, location);
	}

	inline static void logTraceToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::trace, msg, location);
	}
#endif // DEBUG


private:
	static std::ofstream logFile_s;
	static std::mutex mutex_s;

	enum class BackgroundColor : int
	{
		black = 40,
		red = 41,
		green = 42,
		yellow = 43,
		blue = 44,
		magenta = 45,
		cyan = 46,
		white = 47,
		defaultColor = 49
	};

	inline friend std::ostream& operator<<(std::ostream& os, BackgroundColor bgColor)
	{
		os << static_cast<std::underlying_type_t<BackgroundColor>>(bgColor);
		return os;
	}

	enum class Level : int
	{
		fatal,
		error,
		warn,
		info,
		debug,
		trace
	};

	static constexpr std::string_view to_string_view(Level lvl) noexcept;

	inline friend std::ostream& operator<<(std::ostream& os, Level lvl)
	{
		os << "[" << IzyLogger::to_string_view(lvl) << "]\t";
		return os;
	}

	static BackgroundColor levelToColor(Level lvl) noexcept;

	static void colorizeTerminal(std::ostream& os, BackgroundColor bgColor) noexcept;

	static void tagMsgWithLevel(std::ostream& os, Level lvl) noexcept;

	static void unTagMsgWithLevel(std::ostream& os) noexcept;

	static std::ostringstream logTime() noexcept;

	static std::ostringstream getLocationStream(const std::source_location location) noexcept;

	static void Log(std::ostream& os, Level lvl, std::string_view msg, const std::source_location location) noexcept;

	static void LogToBoth(Level lvl, std::string_view msg, const std::source_location location) noexcept;
};

std::ofstream IzyLogger::logFile_s{ "myLog.log" };
std::mutex IzyLogger::mutex_s{};



constexpr std::string_view IzyLogger::to_string_view(Level lvl) noexcept
{
	if (lvl == Level::fatal)
	{
		return "fatal";
	}
	else if (lvl == Level::error)
	{
		return "error";
	}
	else if (lvl == Level::warn)
	{
		return "warn";
	}
	else if (lvl == Level::info)
	{
		return "info";
	}
	else if (lvl == Level::debug)
	{
		return "debug";
	}
	else if (lvl == Level::trace)
	{
		return "trace";
	}
	else
	{
		return "to_string_view(Level)-failure";
	}
}

IzyLogger::BackgroundColor IzyLogger::levelToColor(Level lvl) noexcept
{
	BackgroundColor bgColor{ BackgroundColor::defaultColor };

	if (lvl == Level::fatal)
	{
		bgColor = BackgroundColor::magenta;
	}
	else if (lvl == Level::error)
	{
		bgColor = BackgroundColor::red;
	}
	else if (lvl == Level::warn)
	{
		bgColor = BackgroundColor::yellow;
	}
	else if (lvl == Level::info)
	{
		bgColor = BackgroundColor::blue;
	}
	else if (lvl == Level::debug)
	{
		bgColor = BackgroundColor::green;
	}
	else if (lvl == Level::trace)
	{
		bgColor = BackgroundColor::defaultColor;
	}

	return bgColor;
}

void IzyLogger::colorizeTerminal(std::ostream& os, BackgroundColor bgColor) noexcept
{
	static constexpr std::string_view escapeSeqIntroducer{ "\033[" };

	if (&os == &std::cout || &os == &std::cerr || &os == &std::clog)
	{
		os << escapeSeqIntroducer << bgColor << 'm';
	}
}

void IzyLogger::tagMsgWithLevel(std::ostream& os, Level lvl) noexcept
{
	if (&os == &std::cout || &os == &std::cerr || &os == &std::clog)
	{
		IzyLogger::colorizeTerminal(os, levelToColor(lvl));
	}

	os << lvl;
}

void IzyLogger::unTagMsgWithLevel(std::ostream& os) noexcept
{
	if (&os == &std::cout || &os == &std::cerr || &os == &std::clog)
	{
		IzyLogger::colorizeTerminal(os, BackgroundColor::defaultColor);
	}
}

std::ostringstream IzyLogger::logTime() noexcept
{
	static constexpr int microSecondsResolution{ 1'000'000 };

	std::ostringstream timeStream{};

	std::chrono::time_point<std::chrono::system_clock> n{ std::chrono::system_clock::now() };
	std::time_t in_time_t{ std::chrono::system_clock::to_time_t(n) };
	std::tm buf{};
	errno_t err = localtime_s(&buf, &in_time_t);
	if (err)
	{
		timeStream << "timestamp-log-failure ";
	}
	else
	{
		auto epoch{ n.time_since_epoch() };
		int microSeconds{ std::chrono::duration_cast<std::chrono::microseconds>(epoch).count() % microSecondsResolution };

		timeStream << std::put_time(&buf, "%F %T.") << microSeconds << ' ';
	}

	return timeStream;
}

std::ostringstream IzyLogger::getLocationStream(const std::source_location location) noexcept
{
	std::ostringstream locStream{};

	locStream << location.file_name()
		<< "(" << location.line()
		<< ":" << location.column()
		<< ") `" << location.function_name()
		<< "`: ";

	return locStream;
}

void IzyLogger::Log(std::ostream& os, IzyLogger::Level lvl, std::string_view msg, const std::source_location location) noexcept
{
	std::lock_guard lock{ mutex_s };

	IzyLogger::tagMsgWithLevel(os, lvl);

	std::ostringstream timeStream = IzyLogger::logTime();
	os << timeStream.str();

	std::ostringstream locStream{ IzyLogger::getLocationStream(location) };
	os << locStream.str() << msg << '\n';

	IzyLogger::unTagMsgWithLevel(os);
}

void IzyLogger::LogToBoth(IzyLogger::Level lvl, std::string_view msg, const std::source_location location) noexcept
{
	std::lock_guard lock{ mutex_s };

	std::ostringstream timeStream{ IzyLogger::logTime() };
	const std::string& timeStr{ timeStream.str() };

	std::ostringstream locStream{ IzyLogger::getLocationStream(location) };
	const std::string& locStr{ locStream.str() };

	std::string logLine
	{
		timeStr +
		locStr +
		msg.data() + '\n'
	};

	std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::logFile_s);
	IzyLogger::tagMsgWithLevel(fOut, lvl);
	fOut << logLine;
	IzyLogger::unTagMsgWithLevel(fOut);

	IzyLogger::tagMsgWithLevel(std::cout, lvl);
	std::cout << logLine;
	IzyLogger::unTagMsgWithLevel(std::cout);
}

#endif // !IZY_LOGGING
