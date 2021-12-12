#include "TestMessageHandler.h"

void TestMessageHandler::enqueueClientRequest(std::string body)
{
	/*TestMessage message{THREAD_TYPE::child, std::this_thread::get_id(), THREAD_TYPE::parent, parentThreadId,
		MESSAGE_TYPE::result, "TestHarness", body };
	clientRequests.enQ(message);
	*/
}

void TestMessageHandler::enqueueClientResult(std::string body)
{
	/*TestMessage message{ THREAD_TYPE::child, std::this_thread::get_id(), THREAD_TYPE::parent, parentThreadId,
		MESSAGE_TYPE::result, "TestHarness", body };
	clientResults.enQ(message);*/
}

void TestMessageHandler::enqueueTestRequest(TestItem item) {
	testRequests.enQ(item);
}

void TestMessageHandler::enqueueTestResult(std::thread::id parentThreadId, TEST_RESULT result, std::string messageText) {
	TestMessage message{ THREAD_TYPE::child, std::this_thread::get_id(), THREAD_TYPE::parent, parentThreadId,
		MESSAGE_TYPE::result, "TestHarness", TestMessageParser::convertTestResultToJSONBody(result, messageText) };
	testResults.enQ(message);
}

TestMessage TestMessageHandler::dequeueClientRequest() { return clientRequests.deQ(); }
TestMessage TestMessageHandler::dequeueClientResult() { return clientResults.deQ(); }
TestItem TestMessageHandler::dequeueTestRequest() { return testRequests.deQ(); }
TestMessage TestMessageHandler::dequeueTestResult() { return testResults.deQ(); }