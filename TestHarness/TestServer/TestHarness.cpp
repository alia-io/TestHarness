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

//default constructor
TestHarness::TestHarness() :suiteName("Default") {}

TestHarness::TestHarness(std::string name, LOG_LEVEL log) : suiteName{ name } {
	StaticLogger<1>::setLogLevel(log);
}

void TestHarness::execute(std::list<std::string> tests) {

	TestTimer timer{};
	const int NUM_TESTS = tests.size();
	const int NUM_THREADS = 3;

	counter.setTotalTests(NUM_TESTS);	//counter struct for # of pass, fail, and total tests

	Message requestMsg{ IP_VERSION::IPv4, "123.45.678.9", 9090, Server::ipVersion, Server::ipAddress, Server::portNumber, tests };

	timer.startTimer();						// Initiate start time

	std::vector<std::thread> threads{};
	for (int i = 0; i < NUM_THREADS; ++i) {
		threads.push_back(std::thread([=] { executeChild(); }));
	}

	// enqueue test requests
	handler.enqueueTestRequests(requestMsg);

	// receive & send out test results
	int numTestsComplete = 0;
	while (true) {
		
		Message message = handler.dequeueTestResult();
		TestItem result = message.getResultMessageBody();

		// increment totals & write result to console
		if (result.testResult == TEST_RESULT::pass) {
			counter.incrementTestPassed();
			StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::positive, result.testMessage });
		} else if (result.testResult == TEST_RESULT::fail) {
			counter.incrementTestFailed();
			StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::negative, result.testMessage });
		} else {
			counter.incrementTestFailed();
			StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::error, result.testMessage });
		}
		
		numTestsComplete++;
		if (numTestsComplete == NUM_TESTS) break;
	}

	timer.endTimer();	// Submit end time to determine how much time the test list took to run

	// write test result summary
	StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::summary, TestResultFormatter::testResultSummary(counter, timer) });

	for (auto& thr : threads) {
		if (thr.joinable()) thr.join();
	}
}

void TestHarness::executeChild() {
	while (true) {
		Message message = handler.dequeueTestRequest();
		bool (*ptr)() = TestGetter::getTest(message.getResultMessageBody().testName).pointer;
		TestRunner runner{ message.getResultMessageBody().testName, ptr };
		runner.runTest(&handler, message, StaticLogger<1>::getLogLevel());
	}
}

int main() {

	StaticLogger<1>::attach(&std::cout);
	StaticLogger<1>::start();
	StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "test" });

	std::list<std::string> tests{
		"TestBasicCalculatorPass", "TestBasicCalculatorFail", "TestBasicCalculatorException", "TestAdvancedCalculatorPass",
		"TestMemoryAllocatorException1", "TestMemoryAllocatorException2", "TestContainerConversionsFail",
		"TestContainerConversionsException", "TestLengthErrorException", "TestOverflowErrorException"
	};

	TestHarness testHarness{ "default", LOG_LEVEL::debug };
	testHarness.execute(tests);
}