#include "TestMessage.h"

using namespace TestSuite;

ThreadAddress::ThreadAddress(THREAD_TYPE threadType, std::thread::id threadId)
	: type{ threadType }, id{ threadId } { }

THREAD_TYPE ThreadAddress::getType() { return type; }
std::thread::id ThreadAddress::getId() { return id; }

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

Address TestMessage::getSourceAddress() { return *source; }
Address TestMessage::getDestinationAddress() { return *destination; }
time_point<system_clock> TestMessage::getTimestamp() { return timestamp; }
std::string TestMessage::getMessageBody() { return body; }

std::string TestMessage::toString() {
	
	std::string str = "{ \"source\": { \"address\": ";
	if (typeid(*source) == typeid(ThreadAddress)) {
		ThreadAddress* src = dynamic_cast<ThreadAddress*>(source);
		str += "\"thread\", \"type\": ";
		if (src->getType() == THREAD_TYPE::parent) str += "\"parent\", ";
		else if (src->getType() == THREAD_TYPE::child) str += "\"child\", ";
		std::stringstream ss;
		ss << src->getId();
		str += "\"id\": " + ss.str();
	} else if (typeid(*source) == typeid(ServerAddress)) {
		ServerAddress* src = dynamic_cast<ServerAddress*>(source);
		str += "\"server\", \"version\": ";
		if (src->getVersion() == IP_VERSION::IPV4) str += "\"IPV4\", ";
		else if (src->getVersion() == IP_VERSION::IPV6) str += "\"IPV6\", ";
		str += "\"ip\": \"" + src->getIp() + "\", \"port\": " + std::to_string(src->getPort());
	}

	str += " }, \"destination\": { \"address\": ";
	if (typeid(*destination) == typeid(ThreadAddress)) {
		ThreadAddress* dest = dynamic_cast<ThreadAddress*>(destination);
		str += "\"thread\", \"type\": ";
		if (dest->getType() == THREAD_TYPE::parent) str += "\"parent\", ";
		else if (dest->getType() == THREAD_TYPE::child) str += "\"child\", ";
		std::stringstream ss;
		ss << dest->getId();
		str += "\"id\": " + ss.str();
	} else if (typeid(*destination) == typeid(ServerAddress)) {
		ServerAddress* dest = dynamic_cast<ServerAddress*>(destination);
		str += "\"server\", \"version\": ";
		if (dest->getVersion() == IP_VERSION::IPV4) str += "\"IPV4\", ";
		else if (dest->getVersion() == IP_VERSION::IPV6) str += "\"IPV6\", ";
		str += "\"ip\": \"" + dest->getIp() + "\", \"port\": " + std::to_string(dest->getPort());
	}

	str += " }, \"type\": ";
	if (type == MESSAGE_TYPE::request) str += "\"request\"";
	else if (type == MESSAGE_TYPE::result) str += "\"result\"";
	else if (type == MESSAGE_TYPE::request_list) str += "\"request_list\"";
	else if (type == MESSAGE_TYPE::result_list) str += "\"result_list\"";

	str += ", \"author\": \"" + author + "\", \"timestamp\": " + TestTimer::epochTime(timestamp) + ", \"body\": " + body + " }";

	return str;
}