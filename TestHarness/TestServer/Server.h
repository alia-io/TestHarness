#pragma once
#include "Message.h"

using namespace TestMessenger;

static class Server {
public:
	static const IP_VERSION ipVersion;
	static const std::string ipAddress;
	static const size_t portNumber;
	static void runServer();
private:
	static void init();
	static void startListener();
};