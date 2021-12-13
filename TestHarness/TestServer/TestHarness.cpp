#include "TestHarness.h"
#include "Executive.h"

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

TestHarness::TestHarness(std::string name, Message request) : suiteName{ name }, requestMessage{ request } {
	StaticLogger<1>::setLogLevel(request.getRequestMessageBody().logLevel);
}

MessageHandler* TestHarness::getHandler() { return &handler; }

void TestHarness::execute() {
	//std::thread parent([=] { parentRunner(); });
	//if (parent.joinable()) parent.join();
	parentRunner();
}

void TestHarness::parentRunner() {
	
	//Timer timer{};
	const int NUM_THREADS = 3;
	numberOfTests = requestMessage.getRequestMessageBody().testCount;

	//timer.startTimer();		// Initiate start time

	std::vector<std::thread> threads{};		// child threads
	for (int i = 0; i < NUM_THREADS; ++i) {
		threads.push_back(std::thread([=] { childRunner(); }));
	}

	handler.enqueueTestRequests(requestMessage);	// enqueue test requests

	// receive & send out test results
	/*int numTestsComplete = 0;
	while (true) {

		Message message = handler.dequeueTestResult();
		TestItem result = message.getResultMessageBody();

		// increment totals & write result to console
		if (result.testResult == TEST_RESULT::pass) {
			//counter.incrementTestPassed();
			StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::positive, result.testMessage });
		}
		else if (result.testResult == TEST_RESULT::fail) {
			//counter.incrementTestFailed();
			StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::negative, result.testMessage });
		}
		else {
			//counter.incrementTestFailed();
			StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::error, result.testMessage });
		}

		numTestsComplete++;
		//if (numTestsComplete == NUM_TESTS) break;
	}*/

	//timer.endTimer();	// Submit end time to determine how much time the test list took to run

	// write test result summary
	//StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::summary, ResultFormatter::testResultSummary(counter, timer) });

	for (auto& thr : threads) {
		if (thr.joinable()) thr.join();
	}
}

void TestHarness::childRunner() {
	while (true) {
		if (numberOfTests <= 0) break;
		Message message = handler.dequeueTestRequest();
		bool (*ptr)() = TestGetter::getTest(message.getResultMessageBody().testName).pointer;
		TestRunner runner{ message.getResultMessageBody().testName, ptr };
		runner.runTest(&handler, message, StaticLogger<1>::getLogLevel());
		mtx.lock();
		numberOfTests--;
		mtx.unlock();
	}
}

/*int main() {

	StaticLogger<1>::attach(&std::cout);
	StaticLogger<1>::start();

	std::list<std::string> tests{
		"TestBasicCalculatorPass", "TestBasicCalculatorFail", "TestBasicCalculatorException", "TestAdvancedCalculatorPass",
		"TestMemoryAllocatorException1", "TestMemoryAllocatorException2", "TestContainerConversionsFail",
		"TestContainerConversionsException", "TestLengthErrorException", "TestOverflowErrorException"
	};

	TestHarness testHarness{ "default", LOG_LEVEL::debug };
	testHarness.execute(tests);

	return 0;
}*/