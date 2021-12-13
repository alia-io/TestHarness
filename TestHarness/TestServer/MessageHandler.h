#pragma once
#include "BlockingQueue.h"
#include "Message.h"
#include "ResultFormatter.h"
#include "Server.h"
#include <thread>

class MessageHandler {
private:
	BlockingQueue<Message> testRequests{};
	BlockingQueue<Message> testResults{};
public:
	void enqueueTestRequests(Message requestMessage);
	void enqueueTestResult(Message resultMessage, TEST_RESULT result, std::string text);
	Message dequeueTestRequest();
	Message dequeueTestResult();
};