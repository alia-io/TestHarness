#include "TestRunner.h"

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
* 
*/

TestRunner::TestRunner(std::string name, bool (*funcPtr)()) : testFunctionName{ name }, testFunction{ funcPtr } { }

void TestRunner::runTest(TestMessageHandler* messageHandler, std::thread::id parentId, LOG_LEVEL logLevel) {
	TestTimer timer{};
	bool result = false;
	timer.startTimer();
	try {
		result = testFunction();
	}
	catch (std::exception& e) {
		timer.endTimer();
		messageHandler->enqueueTestResult(parentId, TEST_RESULT::exception,
			TestResultFormatter::testExceptionMessage(testFunctionName, e, logLevel));
		return;
	}

	timer.endTimer();

	if (result) {
		messageHandler->enqueueTestResult(parentId, TEST_RESULT::pass,
			TestResultFormatter::testPassedMessage(testFunctionName, timer));
		return;
	}

	messageHandler->enqueueTestResult(parentId, TEST_RESULT::fail,
		TestResultFormatter::testFailedMessage(testFunctionName, timer));
}