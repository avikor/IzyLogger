#include "IzyLogger.hpp"



std::ofstream IzyLogger::logFile_s{ "myLog.log" };
std::mutex IzyLogger::mutex_s{};


constexpr std::string_view IzyLogger::to_string_view(const Level lvl) noexcept
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

IzyLogger::BackgroundColor IzyLogger::levelToColor(const Level lvl) noexcept
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

void IzyLogger::colorizeTerminal(std::ostream& os, const BackgroundColor bgColor) noexcept
{
	static constexpr std::string_view escapeSeqIntroducer{ "\033[" };

	if (&os == &std::cout || &os == &std::cerr || &os == &std::clog)
	{
		os << escapeSeqIntroducer << bgColor << 'm';
	}
}

void IzyLogger::tagMsgWithLevel(std::ostream& os, const Level lvl) noexcept
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

	const std::chrono::time_point<std::chrono::system_clock> n{ std::chrono::system_clock::now() };
	const std::time_t in_time_t{ std::chrono::system_clock::to_time_t(n) };
	std::tm buf{};
	const errno_t err = localtime_s(&buf, &in_time_t);
	if (err) [[unlikely]]
	{
		timeStream << "timestamp-log-failure ";
	}
	else [[likely]]
	{
		const auto epoch{ n.time_since_epoch() };
		const int microSeconds{ std::chrono::duration_cast<std::chrono::microseconds>(epoch).count() % microSecondsResolution };

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

void IzyLogger::Log(std::ostream& os, const Level lvl, std::string_view msg, const std::source_location location) noexcept
{
	std::lock_guard lock{ mutex_s };

	IzyLogger::tagMsgWithLevel(os, lvl);

	const std::ostringstream timeStream = IzyLogger::logTime();
	os << timeStream.str();

	const std::ostringstream locStream{ IzyLogger::getLocationStream(location) };
	os << locStream.str() << msg << '\n';

	IzyLogger::unTagMsgWithLevel(os);
}

void IzyLogger::LogToBoth(const Level lvl, std::string_view msg, const std::source_location location) noexcept
{
	std::lock_guard lock{ mutex_s };

	const std::ostringstream timeStream{ IzyLogger::logTime() };
	const std::string& timeStr{ timeStream.str() };

	const std::ostringstream locStream{ IzyLogger::getLocationStream(location) };
	const std::string& locStr{ locStream.str() };

	const std::string logLine
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