#pragma once
#include "Message.h"

using namespace TestMessenger;

static class Client {
public:
	static const IP_VERSION ipVersion;
	static const std::string ipAddress;
	static const size_t portNumber;
	static void runTests(LOG_LEVEL logLevel, std::list<std::string> testList);
private:
	static void init();
	static void startListener(int numTests);
	static void sendRequest(LOG_LEVEL logLevel, std::list<std::string> testList);
};