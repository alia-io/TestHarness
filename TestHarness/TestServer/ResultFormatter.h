#pragma once
#include "Timer.h"
#include "StaticLogger.h"
#include "ResultCounter.h"
#include <string>
#include <iostream>

class ResultFormatter {
public:
	static std::string testPassedMessage(std::string testName, Timer timer);
	static std::string testFailedMessage(std::string testName, Timer timer);
	static std::string testExceptionMessage(std::string testName, std::exception& e, LOG_LEVEL logLevel);
	static std::string testResultSummary(ResultCounter counter, Timer timer);
private:
	static std::string exceptionDetails(std::exception& e);
};