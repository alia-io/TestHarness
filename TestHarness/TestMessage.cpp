#include "TestMessage.h"

using namespace TestSuite;

ThreadAddress::ThreadAddress(THREAD_TYPE threadType, std::thread::id threadId)
	: type{ threadType }, id{ threadId } { }

ServerAddress::ServerAddress(IP_VERSION serverIpVersion, std::string serverIpAddress, size_t serverPort)
	: version{ serverIpVersion }, ip{ serverIpAddress }, port{ serverPort } { }

TestMessage::TestMessage(THREAD_TYPE sourceThreadType, std::thread::id sourceThreadId,
	THREAD_TYPE destinationThreadType, std::thread::id destinationThreadId,
	MESSAGE_TYPE messageType, std::string messageAuthor, std::string messageBody)
	: type{ messageType }, author{ messageAuthor }, body{ messageBody }
{
	ThreadAddress sourceAddress{ sourceThreadType, sourceThreadId };
	ThreadAddress destinationAddress{ destinationThreadType, destinationThreadId };
	source = &sourceAddress;
	destination = &destinationAddress;
	timestamp = system_clock::now();
}

TestMessage::TestMessage(IP_VERSION sourceIpVersion, std::string sourceIpAddress, size_t sourcePort,
	IP_VERSION destinationIpVersion, std::string destinationIpAddress, size_t destinationPort,
	MESSAGE_TYPE messageType, std::string messageAuthor, std::string messageBody)
	: type{ messageType }, author{ messageAuthor }, body{ messageBody }
{
	ServerAddress sourceAddress{ sourceIpVersion, sourceIpAddress, sourcePort };
	ServerAddress destinationAddress{ destinationIpVersion, destinationIpAddress, destinationPort };
	source = &sourceAddress;
	destination = &destinationAddress;
	timestamp = system_clock::now();
}

Address TestMessage::getSourceAddress() { return *source; }
Address TestMessage::getDestinationAddress() { return *destination; }
MESSAGE_TYPE TestMessage::getMessageType() { return type; }
std::string TestMessage::getMessage() { return body; }