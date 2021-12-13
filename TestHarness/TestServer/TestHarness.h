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
#include <mutex>

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
	Message requestMessage;
	MessageHandler handler{};
	int numberOfTests;
	std::mutex mtx;
	void parentRunner();
	void childRunner();
public:
	TestHarness(std::string name, Message request);
	MessageHandler* getHandler();
	void execute();
};