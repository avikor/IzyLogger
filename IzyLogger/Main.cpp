#include <iostream>
#include <format>
#include <future>

#include "IzyLogger.hpp"


void foo(double d)
{
	IzyLogger::logFatal(std::format("log fatal from foo with double d: {}", d));

	IzyLogger::logInfoToLogFile("logging info only to log file from foo");
}

void bar(char c)
{
	IzyLogger::logError(std::format("log error from bar with char c: {}", c));

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