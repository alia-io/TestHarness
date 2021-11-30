#include "TestHarness.h"

//////////////////////////////////////////////////////
// TestHarness.cpp									//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* Implementation of Test Harness Class
*
* Purpose of class is to repeatedly call the testrunner class which inturn invokes the testable function
*
*/

//default constructor
TestHarness::TestHarness() :suiteName("Default") {}

TestHarness::TestHarness(string name, LOGLEVEL log) : suiteName(name) {
	logger.setLogLevel(log);	//calls the function for setting the log level
}

//Add callable objects to invoke
// TODO: this should be sent through the messenger from the client
void TestHarness::sendTestList(list<TestItem> tests) { testList = tests; }

void TestHarness::execute() {

	TestTimer timer{};
	counter.setTotalTests(testList.size());	//counter struct for # of pass, fail, and total tests

	timer.startTimer();						// Initiate start time



	for (auto const& test : testList) {
		TestRunner runner(test.name, test.ptr); // run each test on test list and increase the correct count
		bool outcome = runner.runTest(logger);
		if (outcome) {
			counter.incrementTestPassed();
		}
		else {
			counter.incrementTestFailed();
		}

	}

	timer.endTimer();	// Submit end time to determine how much time the test list took to run
	logger.writeTestRunSummary(counter, timer);

}

void TestHarness::executeChild() {

	while (true) {
		//TestItem item = testQueue.deQ();
		//TestRunner runner(item.name, item.ptr);	// run each test on test list
		//bool outcome = runner.runTest(logger.getLogLevel());
	}
}
