#include "Message.h"
#include <iostream>
#include <stack>
#include <vector>

using namespace TestMessenger;

void Message::Address::setValues(IP_VERSION ver, std::string addr, size_t pt) {
	ipVer = ver;
	ipAddr = addr;
	port = pt;
}

/* constuctor from JSON message string */
Message::Message(std::string jsonMessageString) {
	
	enum class MESSAGE_STEP { ms_source, ms_destination, ms_version, ms_ip, ms_port, ms_type,
		ms_author, ms_timestamp, ms_body };
	std::stack<char> stk{};
	std::vector<MESSAGE_STEP> step{};
	std::string str = "";

	for (char ch : jsonMessageString) {

		if (step.size() == 1) {
			if (step.at(0) == MESSAGE_STEP::ms_body) {
				if (stk.size() == 1 && ch == '{') {
					stk.push(ch);
					body += ch;
				} else if (stk.size() == 2) {
					if (ch == '}' && stk.top() == '{') {
						stk.pop();
						step.pop_back();
					}
					body += ch;
				}
				continue;
			}
		}
		
		if (ch == '{') stk.push(ch);
		else if (ch == '}' && stk.size() > 0) {
			if (stk.top() == '{') stk.pop();
		} else if (ch == '"') {
			if (stk.size() > 0) {
				if (stk.top() == '"') {
					stk.pop();
					if (step.size() == 0 && stk.size() == 1) {
						if (str.compare("source") == 0) step.push_back(MESSAGE_STEP::ms_source);
						else if (str.compare("destination") == 0) step.push_back(MESSAGE_STEP::ms_destination);
						else if (str.compare("type") == 0) step.push_back(MESSAGE_STEP::ms_type);
						else if (str.compare("author") == 0) step.push_back(MESSAGE_STEP::ms_author);
						else if (str.compare("timestamp") == 0) step.push_back(MESSAGE_STEP::ms_timestamp);
						else if (str.compare("body") == 0) step.push_back(MESSAGE_STEP::ms_body);
					} else if (step.size() == 1 && stk.size() == 1) {
						if (step.at(0) == MESSAGE_STEP::ms_type) {
							if (str.compare("client_request") == 0) messageType = MESSAGE_TYPE::client_request;
							else if (str.compare("test_result") == 0) messageType = MESSAGE_TYPE::test_result;
						} else if (step.at(0) == MESSAGE_STEP::ms_author) {
							author = str;
						} else if (step.at(0) == MESSAGE_STEP::ms_timestamp) {
							timestamp = str;
						}
						step.pop_back();
					} else if (step.size() == 1 && stk.size() == 2) {
						if (step.at(0) == MESSAGE_STEP::ms_source || step.at(0) == MESSAGE_STEP::ms_destination) {
							if (str.compare("version") == 0) step.push_back(MESSAGE_STEP::ms_version);
							else if (str.compare("ip") == 0) step.push_back(MESSAGE_STEP::ms_ip);
							else if (str.compare("port") == 0) step.push_back(MESSAGE_STEP::ms_port);
						}
					} else if (step.size() == 2 && stk.size() == 2) {
						if (step.at(0) == MESSAGE_STEP::ms_source) {
							if (step.at(1) == MESSAGE_STEP::ms_version) {
								if (str.compare("IPv4") == 0) source.ipVer = IP_VERSION::IPv4;
								else if (str.compare("IPv6") == 0) source.ipVer = IP_VERSION::IPv6;
							} else if (step.at(1) == MESSAGE_STEP::ms_ip) source.ipAddr = str;
							else if (step.at(1) == MESSAGE_STEP::ms_port) {
								std::stringstream(str) >> source.port;
								step.pop_back();
							}
						} else if (step.at(0) == MESSAGE_STEP::ms_destination) {
							if (step.at(1) == MESSAGE_STEP::ms_version) {
								if (str.compare("IPv4") == 0) destination.ipVer = IP_VERSION::IPv4;
								else if (str.compare("IPv6") == 0) destination.ipVer = IP_VERSION::IPv6;
							} else if (step.at(1) == MESSAGE_STEP::ms_ip) destination.ipAddr = str;
							else if (step.at(1) == MESSAGE_STEP::ms_port) {
								std::stringstream(str) >> destination.port;
								step.pop_back();
							}
						}
						step.pop_back();
					}
					str = "";
				} else stk.push(ch);
			} else stk.push(ch);
		} else if (stk.size() > 0) {
			if (stk.top() == '"') str += ch;
		}
	}
}

/* constructor for client request message */
Message::Message(IP_VERSION sourceIpVer, std::string sourceIpAddr, size_t sourcePort,
	IP_VERSION destIpVer, std::string destIpAddr, size_t destPort, std::list<std::string> testList)
{
	source.setValues(sourceIpVer, sourceIpAddr, sourcePort);
	destination.setValues(destIpVer, destIpAddr, destPort);
	messageType = MESSAGE_TYPE::client_request;
	author = "TestClient";
	timestamp = TestTimer::currentTime();
	body = R"({ "count": ")" + std::to_string(testList.size()) + R"(", "tests": [ )";
	for (auto it = testList.begin(); it != testList.end(); ++it) {
		if (it != testList.begin()) body += ", ";
		body += R"(")" + *it + R"(")";
	}
	body += R"( ] })";
}

/* constructor for test result message */
Message::Message(IP_VERSION sourceIpVer, std::string sourceIpAddr, size_t sourcePort,
	IP_VERSION destIpVer, std::string destIpAddr, size_t destPort, std::string testName)
{
	source.setValues(sourceIpVer, sourceIpAddr, sourcePort);
	destination.setValues(destIpVer, destIpAddr, destPort);
	messageType = MESSAGE_TYPE::test_result;
	author = "TestServer";
	timestamp = TestTimer::currentTime();
	body = R"({ "name": ")" + testName + R"(", "result": "", "message": "" })";
}

/* add the test result to the message */
void Message::setTestResult(TEST_RESULT testResult, std::string resultMessage) {
	int length = body.length();
	std::string newBody = body.substr(0, length - 18);
	if (testResult == TEST_RESULT::pass) newBody += "pass";
	else if (testResult == TEST_RESULT::fail) newBody += "fail";
	else if (testResult == TEST_RESULT::exception) newBody += "exception";
	newBody += body.substr(length - 18, 15) + resultMessage + body.substr(length - 3, 3);
	body = newBody;
}

/* convert message to JSON formatted string */
std::string Message::getJsonFormattedMessage() {
	std::string message = R"({ "source": { "version": "IPv)";
	if (source.ipVer == IP_VERSION::IPv4) message += "4";
	else if (source.ipVer == IP_VERSION::IPv6) message += "6";
	message += R"(", "ip": ")" + source.ipAddr + R"(", "port": ")" + std::to_string(source.port) + R"(" }, "destination": { "version": "IPv)";
	if (destination.ipVer == IP_VERSION::IPv4) message += "4";
	else if (destination.ipVer == IP_VERSION::IPv6) message += "6";
	message += R"(", "ip": ")" + destination.ipAddr + R"(", "port": ")" + std::to_string(destination.port) + R"(" }, "type": ")";
	if (messageType == MESSAGE_TYPE::client_request) message += "client_request";
	else if (messageType == MESSAGE_TYPE::test_result) message += "test_result";
	message += R"(", "author": ")" + author + R"(", "timestamp": ")" + timestamp + R"(", "body": )" + body + " }";
	return message;
}

IP_VERSION Message::destinationIpVersion() { return destination.ipVer; }
std::string Message::destinationIpAddress() { return destination.ipAddr; }
size_t Message::destinationPort() { return destination.port; }

/* return message body as a RequestItem or TestItem object */
auto Message::getMessageBody() {
	return "";
}

#define MESSAGE_TEST
// ------------ Test Stub ------------- //
#ifdef MESSAGE_TEST

int main() {
	
	std::list<std::string> tests{ "TestName1", "TestName2", "TestName3", "TestName4", "TestName5", "TestName6", "TestName7" };
	Message requestMsg{ IP_VERSION::IPv4, "111.11.111", 5555, IP_VERSION::IPv6, "9999.999.99.9", 1234, tests };
	std::string requestStr = requestMsg.getJsonFormattedMessage();
	std::cout << "\n" << requestStr << std::endl;
	Message requestStrToMsg{ requestStr };
	std::cout << "\n" << requestStrToMsg.getJsonFormattedMessage() << std::endl;
	std::cout << "\nequal = " << requestStr.compare(requestStrToMsg.getJsonFormattedMessage()) << std::endl;

	Message resultMsg{ IP_VERSION::IPv6, "123.45.678.90", 8080, IP_VERSION::IPv4, "987.65.432.10", 9090, "TestName" };
	std::string resultStr = resultMsg.getJsonFormattedMessage();
	std::cout << "\n" << resultStr << std::endl;
	Message resultStrToMsg{ resultStr };
	std::cout << "\n" << resultStrToMsg.getJsonFormattedMessage() << std::endl;
	std::cout << "\nequal = " << resultStr.compare(resultStrToMsg.getJsonFormattedMessage()) << std::endl;

	resultMsg.setTestResult(TEST_RESULT::fail, "test failed!\n     new line");
	std::string testResultStr = resultMsg.getJsonFormattedMessage();
	std::cout << "\n" << testResultStr << std::endl;
	Message testResultStrToMsg{ testResultStr };
	std::cout << "\n" << testResultStrToMsg.getJsonFormattedMessage() << std::endl;
	std::cout << "\nequal = " << testResultStr.compare(testResultStrToMsg.getJsonFormattedMessage()) << std::endl;

	return 0;
}
#endif