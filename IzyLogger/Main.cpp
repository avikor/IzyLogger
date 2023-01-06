#include <iostream>
#include <future>

#if _MSC_VER
#include <format>
#endif

#include "IzyLogger.hpp"


void foo(double d)
{
#if _MSC_VER
	IzyLogger::logFatal(std::format("log fatal from foo with double d: {}", d));
#endif

	IzyLogger::logInfoToLogFile("logging info only to log file from foo");
}

void bar(char c)
{
#if _MSC_VER
	IzyLogger::logError(std::format("log error from bar with char c: {}", c));
#endif

	IzyLogger::logWarnToOutsream(std::cout, "logging warning only to cout from bar");
}


int main(int argc, char* argv[])
{
	std::cout << "hello world\n";

	IzyLogger::logDebug("log debug from main");

	auto fuFoo = std::async(std::launch::async, foo, 3.5);

	auto fuBar = std::async(std::launch::async, bar, 'Q');

	fuFoo.get();

	fuBar.get();

	IzyLogger::logTrace("goodbye world");
}