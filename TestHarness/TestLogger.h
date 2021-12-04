#pragma once
#include "TestTimer.h"
#include "TestResultCounter.h"
#include "TestMessageParser.h"
#include <string>
#include <string>
#include <iostream>
#include <Windows.h>
#include <iomanip>

//////////////////////////////////////////////////////
// TestLogger.h										//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is retrieve the logLevel and print the exception messages to a file.
* This class also includes a function for summarizing the test results into a pass/failed section
*
*/

namespace TestSuite {
	enum class LOG_LEVEL {
		info, debug, detail
	};
	class TestLogger
	{
	private:
		LOG_LEVEL logLevel;
	public:
		TestLogger(LOG_LEVEL);
		TestLogger();
		void writeLogInfoToOutput(TEST_RESULT result, std::string message, TestTimer timer);
		LOG_LEVEL getLogLevel();
		void setLogLevel(LOG_LEVEL log);
		void writeTestRunSummary(TestResultCounter counter, TestTimer timer);
	};

};


