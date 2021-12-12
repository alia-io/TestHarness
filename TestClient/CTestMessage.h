#pragma once

#include <chrono>
#include <string>
#include <thread>
#include <sstream>
#include "CTestTimer.h"

using std::chrono::time_point;
using std::chrono::system_clock;

/*
*	--------------------
*	MESSAGETYPE options:
*	--------------------
*
*	request - message containing a single DLL/TEST function pointer to be tested
*		source: parent process ID (TestHarness)
*		destination: child process ID (TestRunner)
*
*	result - message containing the result of a single DLL/TEST function pointer
*		source: child process ID (TestRunner)
*		destination: parent process ID (TestHarness)
*
*	request_list - message containing a list of DLLs to be tested
*		source: client IP address & port
*		destination: server IP address & port
*
*	result_list - message containing a list of the TEST results
*		source: server IP address & port
*		destination: client IP address & port
*/

namespace TestSuite {

	enum class THREAD_TYPE { parent, child };
	enum class IP_VERSION { IPV4 = 4, IPV6 = 6 };
	enum class MESSAGE_TYPE { request, result, request_list, result_list };

	class Address {
	public:
		virtual ~Address() = default;
	};

	class ThreadAddress : public Address {
	private:
		THREAD_TYPE type;
		size_t id;
	public:
		ThreadAddress(THREAD_TYPE threadType, std::thread::id threadId);
		ThreadAddress(THREAD_TYPE threadType, size_t threadId);
		THREAD_TYPE getType();
		size_t getId();
	};

	class ServerAddress : public Address {
		IP_VERSION version;
		std::string ip;
		size_t port;
	public:
		ServerAddress(IP_VERSION serverIpVersion, std::string serverIpAddress, size_t serverPort);
		IP_VERSION getVersion();
		std::string getIp();
		size_t getPort();
	};

	class TestMessage {
	private:
		Address* source;
		Address* destination;
		MESSAGE_TYPE type;
		std::string author;		// this could be a client user name or "TestHarness" server
		time_point<system_clock> timestamp;
		std::string body;
	public:
		TestMessage(THREAD_TYPE sourceThreadType, std::thread::id sourceThreadId,	// constructor for thread-to-thread communication
			THREAD_TYPE destinationThreadType, std::thread::id destinationThreadId,
			MESSAGE_TYPE messageType, std::string messageAuthor, std::string messageBody);
		TestMessage(IP_VERSION sourceIpVersion, std::string sourceIpAddress, size_t sourcePort,	// constructor for server-to-server communication
			IP_VERSION destinationIpVersion, std::string destinationIpAddress, size_t destinationPort,
			MESSAGE_TYPE messageType, std::string messageAuthor, std::string messageBody);
		TestMessage(Address* src, Address* dest, MESSAGE_TYPE messageType, std::string messageAuthor,
			time_point<system_clock> time, std::string messageBody);
		Address getSourceAddress();
		Address getDestinationAddress();
		MESSAGE_TYPE getMessageType();
		std::string getMessageBody();
		friend class TestMessageParser;
	};
}