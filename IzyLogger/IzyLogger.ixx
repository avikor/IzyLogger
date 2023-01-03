// currently not enough STL support

//export module IzyLogger;
//
//import <time.h>;
//import <chrono>;
//import <iostream>;
//import <source_location>;
//import <string_view>;
//import <fstream>;
//import <sstream>;
//import <mutex>;
//
//
//namespace IzyLogger
//{
//	static std::ofstream logFile_s{ "technosoftLogger.log" };
//	static std::mutex mutex_s{};
//
//	enum class BackgroundColor : int
//	{
//		black = 40,
//		red = 41,
//		green = 42,
//		yellow = 43,
//		blue = 44,
//		magenta = 45,
//		cyan = 46,
//		white = 47,
//		defaultColor = 49
//	};
//
//	inline std::ostream& operator<<(std::ostream& os, BackgroundColor bgColor)
//	{
//		os << static_cast<std::underlying_type_t<BackgroundColor>>(bgColor);
//		return os;
//	}
//
//	enum class Level : int
//	{
//		fatal,
//		error,
//		warn,
//		info,
//		debug,
//		trace
//	};
//
//	constexpr std::string_view to_string_view(Level lvl) noexcept
//	{
//		if (lvl == Level::fatal)
//		{
//			return "fatal";
//		}
//		else if (lvl == Level::error)
//		{
//			return "error";
//		}
//		else if (lvl == Level::warn)
//		{
//			return "warn";
//		}
//		else if (lvl == Level::info)
//		{
//			return "info";
//		}
//		else if (lvl == Level::debug)
//		{
//			return "debug";
//		}
//		else if (lvl == Level::trace)
//		{
//			return "trace";
//		}
//		else
//		{
//			return "to_string_view(Level)-failure";
//		}
//	}
//
//	inline std::ostream& operator<<(std::ostream& os, Level lvl)
//	{
//		os << "[" << to_string_view(lvl) << "]\t";
//		return os;
//	}
//
//	BackgroundColor levelToColor(Level lvl) noexcept
//	{
//		BackgroundColor bgColor{ BackgroundColor::defaultColor };
//
//		if (lvl == Level::fatal)
//		{
//			bgColor = BackgroundColor::magenta;
//		}
//		else if (lvl == Level::error)
//		{
//			bgColor = BackgroundColor::red;
//		}
//		else if (lvl == Level::warn)
//		{
//			bgColor = BackgroundColor::yellow;
//		}
//		else if (lvl == Level::info)
//		{
//			bgColor = BackgroundColor::blue;
//		}
//		else if (lvl == Level::debug)
//		{
//			bgColor = BackgroundColor::green;
//		}
//		else if (lvl == Level::trace)
//		{
//			bgColor = BackgroundColor::defaultColor;
//		}
//
//		return bgColor;
//	}
//
//	void colorizeTerminal(std::ostream& os, BackgroundColor bgColor) noexcept
//	{
//		static constexpr std::string_view escapeSeqIntroducer{ "\033[" };
//
//		if (&os == &std::cout || &os == &std::cerr || &os == &std::clog)
//		{
//			os << escapeSeqIntroducer << bgColor << 'm';
//		}
//	}
//
//	void tagMsgWithLevel(std::ostream& os, Level lvl) noexcept
//	{
//		if (&os == &std::cout || &os == &std::cerr || &os == &std::clog)
//		{
//			colorizeTerminal(os, levelToColor(lvl));
//		}
//
//		os << lvl;
//	}
//
//	void unTagMsgWithLevel(std::ostream& os) noexcept
//	{
//		if (&os == &std::cout || &os == &std::cerr || &os == &std::clog)
//		{
//			colorizeTerminal(os, BackgroundColor::defaultColor);
//		}
//	}
//
//	std::ostringstream logTime() noexcept
//	{
//		static constexpr int microSecondsResolution{ 1'000'000 };
//
//		std::ostringstream timeStream{};
//
//		std::chrono::time_point<std::chrono::system_clock> n{ std::chrono::system_clock::now() };
//		std::time_t in_time_t{ std::chrono::system_clock::to_time_t(n) };
//		std::tm buf{};
//		errno_t err = localtime_s(&buf, &in_time_t);
//		if (err)
//		{
//			timeStream << "timestamp-log-failure ";
//		}
//		else
//		{
//			auto epoch{ n.time_since_epoch() };
//			int microSeconds{ std::chrono::duration_cast<std::chrono::microseconds>(epoch).count() % microSecondsResolution };
//
//			timeStream << std::put_time(&buf, "%F %T.") << microSeconds << ' ';
//		}
//
//		return timeStream;
//	}
//
//	std::ostringstream getLocationStream(const std::source_location location) noexcept
//	{
//		std::ostringstream locStream{};
//
//		locStream << location.file_name()
//			<< "(" << location.line()
//			<< ":" << location.column()
//			<< ") `" << location.function_name()
//			<< "`: ";
//
//		return locStream;
//	}
//
//	void Log(std::ostream& os, Level lvl, std::string_view msg, const std::source_location location) noexcept
//	{
//		std::lock_guard lock{ mutex_s };
//
//		tagMsgWithLevel(os, lvl);
//
//		std::ostringstream timeStream = logTime();
//		os << timeStream.str();
//
//		std::ostringstream locStream{ getLocationStream(location) };
//		os << locStream.str() << msg << '\n';
//
//		unTagMsgWithLevel(os);
//	}
//
//	void LogToBoth(Level lvl, std::string_view msg, const std::source_location location) noexcept
//	{
//		std::lock_guard lock{ mutex_s };
//
//		std::ostringstream timeStream{ logTime() };
//		const std::string& timeStr{ timeStream.str() };
//
//		std::ostringstream locStream{ getLocationStream(location) };
//		const std::string& locStr{ locStream.str() };
//
//		std::string logLine
//		{
//			timeStr +
//			locStr +
//			msg.data() + '\n'
//		};
//
//		std::ostream& fOut = static_cast<std::ostream&>(logFile_s);
//		tagMsgWithLevel(fOut, lvl);
//		fOut << logLine;
//		unTagMsgWithLevel(fOut);
//
//		tagMsgWithLevel(std::cout, lvl);
//		std::cout << logLine;
//		unTagMsgWithLevel(std::cout);
//	}
//
//	// exports
//#ifdef NDEBUG
/////////////////////////////// write to both cout and log file /////////////////////////////
//	export inline void logFatal(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logError(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logWarn(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logInfo(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logDebug(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logTrace(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	///////////////////////////// write to log file ///////////////////////////////////////////
//	export inline void logFatalToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logErrorToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logWarnToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logInfoToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logDebugToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logTraceToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//
//	///////////////////////////// write to outstream //////////////////////////////////////////
//	export inline void logFatalToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logErrorToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logWarnToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logInfoToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logDebugToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//
//	export inline void logTraceToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{ }
//#else
/////////////////////////////// write to both cout and log file /////////////////////////////
//	export inline void logFatal(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		LogToBoth(Level::fatal, msg, location);
//	}
//
//	export inline void logError(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		LogToBoth(Level::error, msg, location);
//	}
//
//	export inline void logWarn(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		LogToBoth(Level::warn, msg, location);
//	}
//
//	export inline void logInfo(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		LogToBoth(Level::info, msg, location);
//	}
//
//	export inline void logDebug(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		LogToBoth(Level::debug, msg, location);
//	}
//
//	export inline void logTrace(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		LogToBoth(Level::trace, msg, location);
//	}
//
//	///////////////////////////// write to log file ///////////////////////////////////////////
//	export inline void logFatalToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(logFile_s);
//		Log(fOut, Level::fatal, msg, location);
//	}
//
//	export inline void logErrorToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(logFile_s);
//		Log(fOut, Level::error, msg, location);
//	}
//
//	export inline void logWarnToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(logFile_s);
//		Log(fOut, Level::warn, msg, location);
//	}
//
//	export inline void logInfoToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(logFile_s);
//		Log(fOut, Level::info, msg, location);
//	}
//
//	export inline void logDebugToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(logFile_s);
//		Log(fOut, Level::debug, msg, location);
//	}
//
//	export inline void logTraceToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(logFile_s);
//		Log(fOut, Level::trace, msg, location);
//	}
//
//
//	///////////////////////////// write to outstream //////////////////////////////////////////
//	export inline void logFatalToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::fatal, msg, location);
//	}
//
//	export inline void logErrorToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::error, msg, location);
//	}
//
//	export inline void logWarnToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::warn, msg, location);
//	}
//
//	export inline void logInfoToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::info, msg, location);
//	}
//
//	export inline void logDebugToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::debug, msg, location);
//	}
//
//	export inline void logTraceToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::trace, msg, location);
//	}
//}