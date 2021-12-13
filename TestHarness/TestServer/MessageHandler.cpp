#include "MessageHandler.h"

void MessageHandler::enqueueTestRequests(Message requestMsg) {
	for (std::string testName : requestMsg.getRequestMessageBody().testList) {
		Message msg{ Server::ipVersion, Server::ipAddress, Server::portNumber, requestMsg.sourceIpVersion(),
			requestMsg.sourceIpAddress(), requestMsg.sourcePort(), testName };
		testRequests.enQ(msg);
	}
}

void MessageHandler::enqueueTestResult(Message requestMsg, TEST_RESULT result, std::string text) {
	Message msg{ Server::ipVersion, Server::ipAddress, Server::portNumber, requestMsg.sourceIpVersion(),
		requestMsg.sourceIpAddress(), requestMsg.sourcePort(), requestMsg.getResultMessageBody().testName };
	msg.setTestResult(result, text);
	testResults.enQ(msg);
}

Message MessageHandler::dequeueTestRequest() { return testRequests.deQ(); }
Message MessageHandler::dequeueTestResult() { return testResults.deQ(); }