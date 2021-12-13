#include "TestRunner.h"
#include "DllLoader.h"

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

using namespace TestMessenger;

TestRunner::TestRunner(std::string name, bool (*funcPtr)()) : testFunctionName{ name }, testFunction{ funcPtr } { }

void TestRunner::runTest(MessageHandler* messageHandler, Message msg, LOG_LEVEL logLevel) {
	Timer timer{};
	bool result = false;
	timer.startTimer();
	try {
		result = testFunction();///TODO:replace it with DLL load in main2
	}
	catch (std::exception& e) {
		timer.endTimer();
		messageHandler->enqueueTestResult(msg, TEST_RESULT::exception,
			ResultFormatter::testExceptionMessage(testFunctionName, e, logLevel));
		return;
	}

	timer.endTimer();

	if (result) {
		messageHandler->enqueueTestResult(msg, TEST_RESULT::pass,
			ResultFormatter::testPassedMessage(testFunctionName, timer));
		return;
	}

	messageHandler->enqueueTestResult(msg, TEST_RESULT::fail,
		ResultFormatter::testFailedMessage(testFunctionName, timer));
}

/*int main2() {
	TestDLLLoader loader;
	loader.dllLoader("TestBasicCalculatorPass.dll");
	return 0;
}*/
