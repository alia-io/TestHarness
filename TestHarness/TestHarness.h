#pragma once
#include "TestLogger.h"
#include "TestBlockingQueue.h"
#include "TestRunner.h"
#include "TestLogger.h"
#include "TestTimer.h"
#include <functional>
#include <iostream>
#include <string>
#include <list>
#include <thread>

using namespace TestSuite;
using std::string;
using std::list;

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
struct TestItem {
	string name;
	bool (*ptr)();
};

class TestHarness
{
private:
	string suiteName;
	list<TestItem> testList{};			// TODO: change to be received as a TestMessages
	TestSuite::TestLogger logger{};
	TestResultCounter counter{};
public:
	TestHarness();
	TestHarness(string name, TestSuite::LOGLEVEL log);
	void sendTestList(std::list<TestItem> tests);
	void execute();
	void executeChild();
};

