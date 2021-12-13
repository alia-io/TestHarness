#pragma once
#include "StaticLogger.h"
#include "MessageHandler.h"
#include "TestRunner.h"
#include "Timer.h"
#include <functional>
#include <iostream>
#include <string>
#include <list>
#include <thread>

//////////////////////////////////////////////////////
// TestHarness.h									//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* This file contains TestHarness class
* Purpose of class is to repeatedly call the testrunner class which inturn invokes the testable function
*
*/

class TestHarness {
private:
	std::string suiteName;
	ResultCounter counter{};
	MessageHandler handler{};
	void executeChild();
public:
	TestHarness();
	TestHarness(std::string name, LOG_LEVEL log);
	void execute(std::list<std::string> tests);
};