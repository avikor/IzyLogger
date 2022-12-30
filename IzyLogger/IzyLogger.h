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
		IzyLogger::LogToBoth(Level::Fatal, msg, location);
	}

	inline static void logError(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::LogToBoth(Level::Error, msg, location);
	}

	inline static void logWarn(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::LogToBoth(Level::Warn, msg, location);
	}

	inline static void logInfo(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::LogToBoth(Level::Info, msg, location);
	}

	inline static void logDebug(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::LogToBoth(Level::Debug, msg, location);
	}

	inline static void logTrace(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::LogToBoth(Level::Trace, msg, location);
	}

	///////////////////////////// write to log file ///////////////////////////////////////////
	inline static void logFatalToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::s_logFile);
		IzyLogger::Log(fOut, Level::Fatal, msg, location);
	}

	inline static void logErrorToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::s_logFile);
		IzyLogger::Log(fOut, Level::Error, msg, location);
	}

	inline static void logWarnToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::s_logFile);
		IzyLogger::Log(fOut, Level::Warn, msg, location);
	}

	inline static void logInfoToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::s_logFile);
		IzyLogger::Log(fOut, Level::Info, msg, location);
	}

	inline static void logDebugToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::s_logFile);
		IzyLogger::Log(fOut, Level::Debug, msg, location);
	}

	inline static void logTraceToLogFile(std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::s_logFile);
		IzyLogger::Log(fOut, Level::Trace, msg, location);
	}


	///////////////////////////// write to outstream //////////////////////////////////////////
	inline static void logFatalToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::Fatal, msg, location);
	}

	inline static void logErrorToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::Error, msg, location);
	}

	inline static void logWarnToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::Warn, msg, location);
	}

	inline static void logInfoToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::Info, msg, location);
	}

	inline static void logDebugToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::Debug, msg, location);
	}

	inline static void logTraceToOutsream(std::ostream& os, std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		IzyLogger::Log(os, Level::Trace, msg, location);
	}
#endif // DEBUG


private:
	static std::ofstream s_logFile;
	static std::mutex s_mutex;

	enum class BackgroundColor : int
	{
		Black = 40,
		Red = 41,
		Green = 42,
		Yellow = 43,
		Blue = 44,
		Magenta = 45,
		Cyan = 46,
		White = 47,
		Default = 49
	};

	inline friend std::ostream& operator<<(std::ostream& os, BackgroundColor bgColor)
	{
		os << static_cast<std::underlying_type_t<BackgroundColor>>(bgColor);
		return os;
	}

	enum class Level : int
	{
		Fatal,
		Error,
		Warn,
		Info,
		Debug,
		Trace
	};

	static constexpr std::string_view to_string(Level lvl) noexcept;

	inline friend std::ostream& operator<<(std::ostream& os, Level lvl)
	{
		os << "[" << IzyLogger::to_string(lvl) << "]\t";
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

std::ofstream IzyLogger::s_logFile{ "myLog.log" };
std::mutex IzyLogger::s_mutex{};



constexpr std::string_view IzyLogger::to_string(Level lvl) noexcept
{
	if (lvl == Level::Fatal)
	{
		return "Fatal";
	}
	else if (lvl == Level::Error)
	{
		return "Error";
	}
	else if (lvl == Level::Warn)
	{
		return "Warn";
	}
	else if (lvl == Level::Info)
	{
		return "Info";
	}
	else if (lvl == Level::Debug)
	{
		return "Debug";
	}
	else if (lvl == Level::Trace)
	{
		return "Trace";
	}
	else
	{
		return "to_string(Level)-failure";
	}
}

IzyLogger::BackgroundColor IzyLogger::levelToColor(Level lvl) noexcept
{
	BackgroundColor bgColor{ BackgroundColor::Default };

	if (lvl == Level::Fatal)
	{
		bgColor = BackgroundColor::Magenta;
	}
	else if (lvl == Level::Error)
	{
		bgColor = BackgroundColor::Red;
	}
	else if (lvl == Level::Warn)
	{
		bgColor = BackgroundColor::Yellow;
	}
	else if (lvl == Level::Info)
	{
		bgColor = BackgroundColor::Blue;
	}
	else if (lvl == Level::Debug)
	{
		bgColor = BackgroundColor::Green;
	}
	else if (lvl == Level::Trace)
	{
		bgColor = BackgroundColor::Default;
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
		IzyLogger::colorizeTerminal(os, BackgroundColor::Default);
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
	std::lock_guard lock{ s_mutex };

	IzyLogger::tagMsgWithLevel(os, lvl);

	std::ostringstream timeStream = IzyLogger::logTime();
	os << timeStream.str();

	std::ostringstream locStream{ IzyLogger::getLocationStream(location) };
	os << locStream.str() << msg << '\n';

	IzyLogger::unTagMsgWithLevel(os);
}

void IzyLogger::LogToBoth(IzyLogger::Level lvl, std::string_view msg, const std::source_location location) noexcept
{
	std::lock_guard lock{ s_mutex };

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

	std::ostream& fOut = static_cast<std::ostream&>(IzyLogger::s_logFile);
	IzyLogger::tagMsgWithLevel(fOut, lvl);
	fOut << logLine;
	IzyLogger::unTagMsgWithLevel(fOut);

	IzyLogger::tagMsgWithLevel(std::cout, lvl);
	std::cout << logLine;
	IzyLogger::unTagMsgWithLevel(std::cout);
}

#endif // !IZY_LOGGING
