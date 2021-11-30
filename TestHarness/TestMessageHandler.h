#pragma once
#include "TestBlockingQueue.h"
#include "TestMessage.h"
#include "TestItem.h"
#include <thread>

using namespace TestSuite;

class TestMessageHandler {
private:
	//TestBlockingQueue<TestMessage> clientRequests{};
	//TestBlockingQueue<TestMessage> clientResults{};
	TestBlockingQueue<TestItem> testRequests{};
	TestBlockingQueue<TestMessage> testResults{};
public:
	//void enqueueClientRequest(std::string body);
	//void enqueueClientResult(std::string body);
	void enqueueTestRequest(TestItem item);
	void enqueueTestResult(std::thread::id parentThreadId, std::string body);
	//TestMessage dequeueClientRequest();
	//TestMessage dequeueClientResult();
	TestItem dequeueTestRequest();
	TestMessage dequeueTestResult();
};