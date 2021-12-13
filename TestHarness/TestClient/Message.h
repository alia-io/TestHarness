#pragma once

#include <chrono>
#include <string>
#include <thread>
#include <sstream>
#include <list>
#include "Timer.h"

using std::chrono::time_point;
using std::chrono::system_clock;

/*
*	-------------------------------------
*	CLIENT REQUEST MESSAGE -- JSON FORMAT
*	-------------------------------------
*
*	{
*		"source": { "version": "[IPv4/IPv6]", "ip": "[ip_address]", "port": "[port]" },
*		"destination: { "version": "[IPv4/IPv6]", "ip": "[ip_address]", "port": "[port]" },
*		"type": "client_request",
*		"author": "TestClient",
*		"timestamp": "[time&date]",
*		"body": { "count": "[num_tests]", "tests": [ "[test_name]", "[test_name]", ... ] }
*	}
*
*	--------------------------------------
*	SERVER RESPONSE MESSAGE -- JSON FORMAT
*	--------------------------------------
*
*	{
*		"source": { "version": "[IPv4/IPv6]", "ip": "[ip_address]", "port": "[port]" },
*		"destination: { "version": "[IPv4/IPv6]", "ip": "[ip_address]", "port": "[port]" },
*		"type": "test_result",
*		"author": "TestServer",
*		"timestamp": "[time&date]",
*		"body": { "name": "[test_name]", "result": "[pass/fail/exception]", "message": "[...]" }
*	}
*/

namespace TestMessenger {

	enum class IP_VERSION { IPv4, IPv6 };
	enum class MESSAGE_TYPE { client_request, test_result };
	enum class TEST_RESULT { exception, pass, fail };
	enum class LOG_LEVEL { info, debug, detail };

	class RequestItem {
	public:
		int testCount;
		std::list<std::string> testList{};
	};

	class TestItem {
	public:
		std::string testName;
		TEST_RESULT testResult;
		std::string testMessage;
	};

	class Message {
	private:

		class Address {
		public:
			IP_VERSION ipVer;
			std::string ipAddr;
			size_t port;
			void setValues(IP_VERSION ver, std::string addr, size_t pt);
		};

		Address source{};					// ip version, ip address, port
		Address destination{};				// ip version, ip address, port
		MESSAGE_TYPE messageType;			// client_request or test_result
		std::string author;					// "TestServer" or "TestClient"
		std::string timestamp;				// time & date
		std::string body;					// test list or test result
	public:
		Message(std::string jsonMessageString);	// constuctor from JSON message string
		Message(IP_VERSION sourceIpVer, std::string sourceIpAddr, size_t sourcePort,	// constructor for client request message
			IP_VERSION destIpVer, std::string destIpAddr, size_t destPort, std::list<std::string> testList);
		Message(IP_VERSION sourceIpVer, std::string sourceIpAddr, size_t sourcePort,	// constructor for test result message
			IP_VERSION destIpVer, std::string destIpAddr, size_t destPort, std::string testName);
		void setTestResult(TEST_RESULT testResult, std::string resultMessage);	// add the test result to the message
		std::string getJsonFormattedMessage();	// convert message to JSON formatted string
		IP_VERSION sourceIpVersion();
		std::string sourceIpAddress();
		size_t sourcePort();
		IP_VERSION destinationIpVersion();
		std::string destinationIpAddress();
		size_t destinationPort();
		RequestItem getRequestMessageBody();	// get message body as a RequestItem object
		TestItem getResultMessageBody();		// get message body as a TestItem object
	};

}