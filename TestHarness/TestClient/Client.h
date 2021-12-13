#pragma once
#include "Message.h"

using namespace TestMessenger;

static class Client {
public:
	static const IP_VERSION ipVersion;
	static const std::string ipAddress;
	static const size_t portNumber;
};