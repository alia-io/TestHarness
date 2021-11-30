#pragma once
#include "TestTimer.h"
#include "TestLogger.h"
#include <string>
#include <iostream>

using namespace TestSuite;

class TestResultFormatter {
public:
	static std::string testPassedMessage(std::string testName, TestTimer timer);
	static std::string testFailedMessage(std::string testName, TestTimer timer);
	static std::string testExceptionMessage(std::string testName, std::exception& e, LOG_LEVEL logLevel);
private:
	static std::string exceptionDetails(std::exception& e);
};