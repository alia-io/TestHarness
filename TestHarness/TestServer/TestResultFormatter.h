#pragma once
#include "TestTimer.h"
#include "StaticLogger.h"
#include "TestResultCounter.h"
#include <string>
#include <iostream>

class TestResultFormatter {
public:
	static std::string testPassedMessage(std::string testName, TestTimer timer);
	static std::string testFailedMessage(std::string testName, TestTimer timer);
	static std::string testExceptionMessage(std::string testName, std::exception& e, LOG_LEVEL logLevel);
	static std::string testResultSummary(TestResultCounter counter, TestTimer timer);
private:
	static std::string exceptionDetails(std::exception& e);
};