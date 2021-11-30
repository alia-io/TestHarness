#include "TestRunner.h"
#include <iostream>
#include <Windows.h>
#include <exception>
#include "TestTimer.h"
#include "TestExceptionHandler.h"

//////////////////////////////////////////////////////
// TestRunner.cpp									//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* This file contains the implementation of the TestRunner class.
*
* This class is used to run each individual test, obtain the result, and pass logging information
* to the logger.
*
* Public Interface:
* -----------------
* TestRunner	initialize TestRunner object with the name of the test function and a pointer to the test function
* runTest		pass TestLogger object to run the test function
*/

TestRunner::TestRunner(std::string name, bool (*funcPtr)()) : testFunctionName{ name }, testFunction{ funcPtr } { }

bool TestRunner::runTest(TestLogger logger) {
	TestTimer timer{};
	bool result = false;
	timer.startTimer();
	try {
		result = testFunction();
	}
	catch (std::exception& e) {
		timer.endTimer();
		std::string message = testFunctionName + "\n";
		TestExceptionHandler handler{};
		message += handler.getCustomizedString(e, logger.getLogLevel()) + "\n";
		logger.writeLogInfoToOutput(message, timer);
		return false;
	}

	timer.endTimer();

	if (result) {
		logger.writeLogInfoToOutput(std::string(testFunctionName + "\n"), timer, result);
		return true;
	}

	logger.writeLogInfoToOutput(std::string(testFunctionName + "\n"), timer, result);
	return false;
}