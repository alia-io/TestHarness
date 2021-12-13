#pragma once

#include <chrono>
#include <string>
#include <thread>
#include <sstream>
#include <list>
#include "TestTimer.h"

using std::chrono::time_point;
using std::chrono::system_clock;


/*
*	-------------------------------------
*	CLIENT REQUEST MESSAGE -- JSON FORMAT
*	-------------------------------------
* 
*	{
*		"source": { "version": "[IPv4/IPv6]", "ip": "[ip_address]", "port": [port] },
*		"destination: { "version": "[IPv4/IPv6]", "ip": "[ip_address]", "port": [port] },
*		"type": "client_request",
*		"author": "TestClient",
*		"timestamp": "[time&date]",
*		"body": { "count": [num_tests], "tests": [ "[test_name]", "[test_name]", ... ] }
*	}
* 
*	--------------------------------------
*	SERVER RESPONSE MESSAGE -- JSON FORMAT
*	--------------------------------------
* 
*	{
*		"source": { "version": "[IPv4/IPv6]", "ip": "[ip_address]", "port": [port] },
*		"destination: { "version": "[IPv4/IPv6]", "ip": "[ip_address]", "port": [port] },
*		"type": "test_result",
*		"author": "TestServer",
*		"timestamp": "[time&date]",
*		"body": { "name": "[test_name]", "result": "[pass/fail/exception]", "message": "[...]" }
*	}
*/

namespace TestMessenger {
	
	enum class IP_VERSION { IPv4, IPv6 };
	enum class MESSAGE_TYPE { client_request, test_result };
	enum class TEST_RESULT { pass, fail, exception };

	class RequestItem {
	private:
		int testCount;
		std::list<std::string> testList;
	public:
		RequestItem(int count, std::list<std::string> list) : testCount{ count }, testList{ list } { }
	};

	class TestItem {
	private:
		std::string testName;
		TEST_RESULT testResult;
		std::string testMessage;
	public:
		TestItem(std::string name, TEST_RESULT result, std::string msg)
			: testName{ name }, testResult{ result }, testMessage{ msg } { }
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
		IP_VERSION destinationIpVersion();
		std::string destinationIpAddress();
		size_t destinationPort();
		auto getMessageBody();	// return message body as a RequestItem or TestItem object
	};

}