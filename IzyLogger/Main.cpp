#include <iostream>
#include <format>
#include <future>

#include "IzyLogger.h"


void foo(double d)
{
	IzyLogger::logFatal(std::format("log fatal from foo with double d: {}", d));
}

void bar(char c)
{
	IzyLogger::logError(std::format("log error from bar with char c: {}", c));
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