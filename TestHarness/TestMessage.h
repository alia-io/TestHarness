#pragma once
#include <chrono>
#include <string>
#include <thread>

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
*	response - message containing the result of a single DLL/TEST function pointer
*		source: child process ID (TestRunner)
*		destination: parent process ID (TestHarness)
*
*	request_list - message containing a list of DLLs to be tested
*		source: client IP address & port
*		destination: server IP address & port
*
*	response_list - message containing a list of the TEST results
*		source: server IP address & port
*		destination: client IP address & port
*/

namespace TestSuite {

	enum class THREAD_TYPE { parent, child };
	enum class IP_VERSION { IPV4 = 4, IPV6 = 6 };
	enum class MESSAGE_TYPE { request, response, request_list, response_list };

	struct Address { };

	class ThreadAddress : public Address {
	private:
		const THREAD_TYPE type;
		const std::thread::id id;
	public:
		ThreadAddress(THREAD_TYPE threadType, std::thread::id threadId);
	};

	class ServerAddress : public Address {
		const IP_VERSION version;
		const std::string ip;
		const size_t port;
	public:
		ServerAddress(IP_VERSION serverIpVersion, std::string serverIpAddress, size_t serverPort);
	};

	class TestMessage {
	private:
		const Address* source;
		const Address* destination;
		const MESSAGE_TYPE type;
		const std::string author;		// this could be a client user name or "TestHarness" server
		time_point<system_clock> timestamp;
		const std::string body;
	public:
		TestMessage(THREAD_TYPE sourceThreadType, std::thread::id sourceThreadId,	// constructor for thread-to-thread communication
			THREAD_TYPE destinationThreadType, std::thread::id destinationThreadId,
			MESSAGE_TYPE messageType, std::string messageAuthor, std::string messageBody);
		TestMessage(IP_VERSION sourceIpVersion, std::string sourceIpAddress, size_t sourcePort,	// constructor for server-to-server communication
			IP_VERSION destinationIpVersion, std::string destinationIpAddress, size_t destinationPort,
			MESSAGE_TYPE messageType, std::string messageAuthor, std::string messageBody);
		Address getSourceAddress();
		Address getDestinationAddress();
		MESSAGE_TYPE getMessageType();
		std::string getMessage();
	};
}