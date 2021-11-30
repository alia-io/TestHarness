#include "TestMessageHandler.h"

void TestMessageHandler::enqueueTestRequest(TestItem item) {
	testRequests.enQ(item);
}

void TestMessageHandler::enqueueTestResult(std::thread::id parentThreadId, std::string body) {
	TestMessage message{ THREAD_TYPE::child, std::this_thread::get_id(), THREAD_TYPE::parent, parentThreadId,
		MESSAGE_TYPE::result, "TestHarness", body };
	testResults.enQ(message);
}

TestItem TestMessageHandler::dequeueTestRequest() { return testRequests.deQ(); }
TestMessage TestMessageHandler::dequeueTestResult() { return testResults.deQ(); }