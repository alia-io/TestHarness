#include "TestMessage.h"

using namespace TestSuite;

ThreadAddress::ThreadAddress(THREAD_TYPE threadType, std::thread::id threadId) : type{ threadType } {
	id = std::hash<std::thread::id>{}(std::this_thread::get_id());
}

ThreadAddress::ThreadAddress(THREAD_TYPE threadType, size_t threadId) : type{ threadType }, id{ threadId } { }

THREAD_TYPE ThreadAddress::getType() { return type; }
size_t ThreadAddress::getId() { return id; }

ServerAddress::ServerAddress(IP_VERSION serverIpVersion, std::string serverIpAddress, size_t serverPort)
	: version{ serverIpVersion }, ip{ serverIpAddress }, port{ serverPort } { }

IP_VERSION ServerAddress::getVersion() { return version; }
std::string ServerAddress::getIp() { return ip; }
size_t ServerAddress::getPort() { return port; }

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

TestMessage::TestMessage(Address* src, Address* dest, MESSAGE_TYPE messageType, std::string messageAuthor,
	time_point<system_clock> time, std::string messageBody) : source{ src }, destination{ dest },
	type{ messageType }, author{ messageAuthor }, timestamp{ time }, body{ messageBody } { }

Address TestMessage::getSourceAddress() { return *source; }
Address TestMessage::getDestinationAddress() { return *destination; }
MESSAGE_TYPE TestMessage::getMessageType() { return type; }
std::string TestMessage::getMessageBody() { return body; }