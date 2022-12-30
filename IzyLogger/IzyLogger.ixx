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
//	static std::ofstream s_logFile{ "technosoftLogger.log" };
//	static std::mutex s_mutex{};
//
//	enum class BackgroundColor : int
//	{
//		Black = 40,
//		Red = 41,
//		Green = 42,
//		Yellow = 43,
//		Blue = 44,
//		Magenta = 45,
//		Cyan = 46,
//		White = 47,
//		Default = 49
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
//		Fatal,
//		Error,
//		Warn,
//		Info,
//		Debug,
//		Trace
//	};
//
//	constexpr std::string_view to_string(Level lvl) noexcept
//	{
//		if (lvl == Level::Fatal)
//		{
//			return "Fatal";
//		}
//		else if (lvl == Level::Error)
//		{
//			return "Error";
//		}
//		else if (lvl == Level::Warn)
//		{
//			return "Warn";
//		}
//		else if (lvl == Level::Info)
//		{
//			return "Info";
//		}
//		else if (lvl == Level::Debug)
//		{
//			return "Debug";
//		}
//		else if (lvl == Level::Trace)
//		{
//			return "Trace";
//		}
//		else
//		{
//			return "to_string(Level)-failure";
//		}
//	}
//
//	inline std::ostream& operator<<(std::ostream& os, Level lvl)
//	{
//		os << "[" << to_string(lvl) << "]\t";
//		return os;
//	}
//
//	BackgroundColor levelToColor(Level lvl) noexcept
//	{
//		BackgroundColor bgColor{ BackgroundColor::Default };
//
//		if (lvl == Level::Fatal)
//		{
//			bgColor = BackgroundColor::Magenta;
//		}
//		else if (lvl == Level::Error)
//		{
//			bgColor = BackgroundColor::Red;
//		}
//		else if (lvl == Level::Warn)
//		{
//			bgColor = BackgroundColor::Yellow;
//		}
//		else if (lvl == Level::Info)
//		{
//			bgColor = BackgroundColor::Blue;
//		}
//		else if (lvl == Level::Debug)
//		{
//			bgColor = BackgroundColor::Green;
//		}
//		else if (lvl == Level::Trace)
//		{
//			bgColor = BackgroundColor::Default;
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
//			colorizeTerminal(os, BackgroundColor::Default);
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
//		std::lock_guard lock{ s_mutex };
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
//		std::lock_guard lock{ s_mutex };
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
//		std::ostream& fOut = static_cast<std::ostream&>(s_logFile);
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
//		LogToBoth(Level::Fatal, msg, location);
//	}
//
//	export inline void logError(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		LogToBoth(Level::Error, msg, location);
//	}
//
//	export inline void logWarn(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		LogToBoth(Level::Warn, msg, location);
//	}
//
//	export inline void logInfo(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		LogToBoth(Level::Info, msg, location);
//	}
//
//	export inline void logDebug(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		LogToBoth(Level::Debug, msg, location);
//	}
//
//	export inline void logTrace(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		LogToBoth(Level::Trace, msg, location);
//	}
//
//	///////////////////////////// write to log file ///////////////////////////////////////////
//	export inline void logFatalToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(s_logFile);
//		Log(fOut, Level::Fatal, msg, location);
//	}
//
//	export inline void logErrorToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(s_logFile);
//		Log(fOut, Level::Error, msg, location);
//	}
//
//	export inline void logWarnToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(s_logFile);
//		Log(fOut, Level::Warn, msg, location);
//	}
//
//	export inline void logInfoToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(s_logFile);
//		Log(fOut, Level::Info, msg, location);
//	}
//
//	export inline void logDebugToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(s_logFile);
//		Log(fOut, Level::Debug, msg, location);
//	}
//
//	export inline void logTraceToLogFile(std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		std::ostream& fOut = static_cast<std::ostream&>(s_logFile);
//		Log(fOut, Level::Trace, msg, location);
//	}
//
//
//	///////////////////////////// write to outstream //////////////////////////////////////////
//	export inline void logFatalToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::Fatal, msg, location);
//	}
//
//	export inline void logErrorToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::Error, msg, location);
//	}
//
//	export inline void logWarnToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::Warn, msg, location);
//	}
//
//	export inline void logInfoToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::Info, msg, location);
//	}
//
//	export inline void logDebugToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::Debug, msg, location);
//	}
//
//	export inline void logTraceToOutsream(std::ostream& os, std::string_view msg,
//		const std::source_location location = std::source_location::current()) noexcept
//	{
//		Log(os, Level::Trace, msg, location);
//	}
//}