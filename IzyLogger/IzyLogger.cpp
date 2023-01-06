#include "IzyLogger.hpp"



// taken from https://stackoverflow.com/a/63617586 
#ifndef _MSC_VER
#include <locale>   // std::use_facet, std::time_put

template<typename CharT>
struct _put_time
{
	const std::tm* time;
	const char* fmt;
};

template<typename CharT>
inline _put_time<CharT>
put_time(const std::tm* time, const CharT* fmt)
{
	return { time, fmt };
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, _put_time<CharT> f)
{
	typedef typename std::ostreambuf_iterator<CharT, Traits> Iter;
	typedef std::time_put<CharT, Iter> TimePut;

	const CharT* const fmt_end = f.fmt + Traits::length(f.fmt);
	const TimePut& mp = std::use_facet<TimePut>(os.getloc());

	std::ios_base::iostate err = std::ios_base::goodbit;
	try {
		if (mp.put(Iter(os.rdbuf()), os, os.fill(), f.time, f.fmt, fmt_end).failed())
			err |= std::ios_base::badbit;
	}
	catch (...) {
		err |= std::ios_base::badbit;
	}

	if (err)
		os.setstate(err);

	return os;
}
#endif


std::ofstream IzyLogger::logFile_s{ "myLog.log" };
std::mutex IzyLogger::mutex_s{};


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
#if _MSC_VER
	const errno_t err{ localtime_s(&buf, &in_time_t) };
	if (err) [[unlikely]]
	{
		timeStream << "timestamp-log-failure ";
	}
#else
	const std::tm* err{ localtime_r(&in_time_t, &buf) };
	if (!err) [[unlikely]]
	{
		timeStream << "timestamp-log-failure ";
	}
#endif
	else [[likely]]
	{
		const auto epoch{ n.time_since_epoch() };
		const int microSeconds{ static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(epoch).count()) % microSecondsResolution };

#if _MSC_VER
		timeStream << std::put_time(&buf, "%F %T.") << microSeconds << ' ';
#else
		timeStream << put_time(&buf, "%F %T.") << microSeconds << ' ';
#endif
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