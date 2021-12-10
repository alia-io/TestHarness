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

TestHarness::TestHarness(std::string name, LOG_LEVEL log) : suiteName(name) { logger.setLogLevel(log); }

void TestHarness::execute(std::list<TestItem> tests) {

	TestTimer timer{};
	TestMessageHandler h{};
	const int NUM_TESTS = tests.size();
	const int NUM_THREADS = 3;

	testHarnessThreadId = std::this_thread::get_id();	// save the parent thread id
	counter.setTotalTests(NUM_TESTS);	//counter struct for # of pass, fail, and total tests

	timer.startTimer();						// Initiate start time

	std::vector<std::thread> threads{};
	for (int i = 0; i < NUM_THREADS; ++i) {
		threads.push_back(std::thread([=] { executeChild(); }));
	}

	// enqueue test requests
	for (auto const& test : tests) {
		handler.enqueueTestRequest(test);
	}

	timer.endTimer();	// Submit end time to determine how much time the test list took to run

	// receive & send out test results
	int numTestsComplete = 0;
	while (true) {
		TestMessage message = handler.dequeueTestResult();
		std::string messageStr = message.getMessageBody();
		TEST_RESULT result = TestMessageParser::testResult(message);
		std::string resultMsg = TestMessageParser::testResultMessage(message);
		if (result == TEST_RESULT::pass) counter.incrementTestPassed();
		else counter.incrementTestFailed();
		logger.writeLogInfoToOutput(result, resultMsg, timer);	// write result to console
		numTestsComplete++;
		if (numTestsComplete == NUM_TESTS) break;
	}

	// write test result summary
	logger.writeTestRunSummary(counter, timer);

	for (auto& thr : threads) {
		if (thr.joinable()) thr.join();
	}
}

void TestHarness::executeChild() {
	while (true) {
		TestItem test = handler.dequeueTestRequest();
		TestRunner runner{ test.getName(), test.getPointer() };
		runner.runTest(&handler, testHarnessThreadId, logger.getLogLevel());
	}
}
