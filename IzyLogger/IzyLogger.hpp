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

	inline friend std::ostream& operator<<(std::ostream& os, const BackgroundColor bgColor)
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

	static constexpr std::string_view to_string_view(const Level lvl) noexcept;

	inline friend std::ostream& operator<<(std::ostream& os, const Level lvl)
	{
		os << "[" << IzyLogger::to_string_view(lvl) << "]\t";
		return os;
	}

	static BackgroundColor levelToColor(const Level lvl) noexcept;

	static void colorizeTerminal(std::ostream& os, const BackgroundColor bgColor) noexcept;

	static void tagMsgWithLevel(std::ostream& os, const Level lvl) noexcept;

	static void unTagMsgWithLevel(std::ostream& os) noexcept;

	static std::ostringstream logTime() noexcept;

	static std::ostringstream getLocationStream(const std::source_location location) noexcept;

	static void Log(std::ostream& os, const Level lvl, std::string_view msg, const std::source_location location) noexcept;

	static void LogToBoth(const Level lvl, std::string_view msg, const std::source_location location) noexcept;
};

#endif // !IZY_LOGGING
