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

TestHarness::TestHarness(std::string name, LOG_LEVEL log) : suiteName(name) {
	logger.setLogLevel(log);	//calls the function for setting the log level
}

//Add callable objects to invoke
// TODO: this should be sent through the messenger from the client
void TestHarness::sendTestList(std::list<TestItem> tests) { testList = tests; }

void TestHarness::execute() {

	TestTimer timer{};

	TestMessageHandler h{};

	testHarnessThreadId = std::this_thread::get_id();	// save the parent thread id
	counter.setTotalTests(testList.size());	//counter struct for # of pass, fail, and total tests

	// enqueue test requests
	for (auto const& test : testList) {
		handler.enqueueTestRequest(test);
	}

	timer.startTimer();						// Initiate start time

	// dequeue and run tests
	for (int i = 0; i != testList.size(); ++i) {
		TestItem test = handler.dequeueTestRequest();
		TestRunner runner{ test.getName(), test.getPointer() };
		runner.runTest(&handler, testHarnessThreadId, logger.getLogLevel());
	}

	timer.endTimer();	// Submit end time to determine how much time the test list took to run

	// receive & send out test results
	for (int i = 0; i != testList.size(); ++i) {
		TestMessage message = handler.dequeueTestResult();
		std::string messageStr = message.getMessage();
		if (messageStr.at(2) == 'P') counter.incrementTestPassed();
		else counter.incrementTestFailed();
		logger.writeLogInfoToOutput(messageStr, timer);		// write each result to console
	}

	// write test result summary
	logger.writeTestRunSummary(counter, timer);

}

void TestHarness::executeChild() {

	while (true) {
		//TestItem item = testQueue.deQ();
		//TestRunner runner(item.name, item.ptr);	// run each test on test list
		//bool outcome = runner.runTest(logger.getLogLevel());
	}
}
