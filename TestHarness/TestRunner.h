#pragma once
#include <string>
#include "TestLogger.h"
using namespace TestSuite;

//////////////////////////////////////////////////////
// TestRunner.h										//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* This class is used to run each individual test, obtain the result, and pass logging information
* to the logger.
*
* Public Interface:
* -----------------
* TestRunner	initialize TestRunner object with the name of the test function and a pointer to the test function
* runTest		pass TestLogger object to run the test function
*/

class TestRunner {
private:
	std::string testFunctionName;
	bool (*testFunction)();
public:
	TestRunner(std::string name, bool (*funcPtr)());
	bool runTest(TestLogger logger);
};