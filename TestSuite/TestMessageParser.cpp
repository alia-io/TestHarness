#include "TestMessageParser.h"

#include <iostream>
#include <thread>

using namespace TestSuite;

std::string TestMessageParser::convertMessageToJSONString(TestMessage message) {

	std::string str = "{ \"source\": { \"address\": ";
	if (typeid(*(message.source)) == typeid(ThreadAddress)) {
		ThreadAddress* src = dynamic_cast<ThreadAddress*>(message.source);
		str += "\"thread\", \"type\": ";
		if (src->getType() == THREAD_TYPE::parent) str += "\"parent\", ";
		else if (src->getType() == THREAD_TYPE::child) str += "\"child\", ";
		std::stringstream ss;
		ss << src->getId();
		str += "\"id\": " + ss.str();
	}
	else if (typeid(*(message.source)) == typeid(ServerAddress)) {
		ServerAddress* src = dynamic_cast<ServerAddress*>(message.source);
		str += "\"server\", \"version\": ";
		if (src->getVersion() == IP_VERSION::IPV4) str += "\"IPV4\", ";
		else if (src->getVersion() == IP_VERSION::IPV6) str += "\"IPV6\", ";
		str += "\"ip\": \"" + src->getIp() + "\", \"port\": " + std::to_string(src->getPort());
	}

	str += " }, \"destination\": { \"address\": ";
	if (typeid(*(message.destination)) == typeid(ThreadAddress)) {
		ThreadAddress* dest = dynamic_cast<ThreadAddress*>(message.destination);
		str += "\"thread\", \"type\": ";
		if (dest->getType() == THREAD_TYPE::parent) str += "\"parent\", ";
		else if (dest->getType() == THREAD_TYPE::child) str += "\"child\", ";
		std::stringstream ss;
		ss << dest->getId();
		str += "\"id\": " + ss.str();
	}
	else if (typeid(*(message.destination)) == typeid(ServerAddress)) {
		ServerAddress* dest = dynamic_cast<ServerAddress*>(message.destination);
		str += "\"server\", \"version\": ";
		if (dest->getVersion() == IP_VERSION::IPV4) str += "\"IPV4\", ";
		else if (dest->getVersion() == IP_VERSION::IPV6) str += "\"IPV6\", ";
		str += "\"ip\": \"" + dest->getIp() + "\", \"port\": " + std::to_string(dest->getPort());
	}

	str += " }, \"type\": ";
	if (message.type == MESSAGE_TYPE::request) str += "\"request\"";
	else if (message.type == MESSAGE_TYPE::result) str += "\"result\"";
	else if (message.type == MESSAGE_TYPE::request_list) str += "\"request_list\"";
	else if (message.type == MESSAGE_TYPE::result_list) str += "\"result_list\"";

	str += ", \"author\": \"" + message.author;
	str += "\", \"timestamp\": " + TestTimer::epochTimeFromTimePoint(message.timestamp);
	str += ", \"body\": " + message.body + " }";

	return str;
}

TestMessage TestMessageParser::convertJSONStringToMessage(std::string messageString) {

	Address* src = nullptr;
	Address* dest = nullptr;
	MESSAGE_TYPE msgType;
	std::string msgAuthor;
	time_point<system_clock> ts;
	std::string msgBody;

	enum MESSAGE_STEP { none, source, destination, type, author, timestamp, body };
	enum ADDRESS_TYPE { thread, server };
	MESSAGE_STEP messageStep = MESSAGE_STEP::none;
	ADDRESS_TYPE addressType;
	int bodyBrackets = 0;
	std::string str = "";

	for (char ch : messageString) {
		if (messageStep == MESSAGE_STEP::none) {
			str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
			if (ch == ',' && str.compare("{\"source\":{\"address\":\"thread\"") == 0) {
				messageStep = MESSAGE_STEP::source;
				addressType = ADDRESS_TYPE::thread;
			}
			else if (ch == ',' && str.compare("{\"source\":{\"address\":\"server\"") == 0) {
				messageStep = MESSAGE_STEP::source;
				addressType = ADDRESS_TYPE::server;
			}
			else if (ch == ',' && str.compare(",\"destination\":{\"address\":\"thread\"") == 0) {
				messageStep = MESSAGE_STEP::destination;
				addressType = ADDRESS_TYPE::thread;
			}
			else if (ch == ',' && str.compare(",\"destination\":{\"address\":\"server\"") == 0) {
				messageStep = MESSAGE_STEP::destination;
				addressType = ADDRESS_TYPE::server;
			}
			else if (ch == '"' && str.compare(",\"type\":") == 0) messageStep = MESSAGE_STEP::type;
			else if (ch == '"' && str.compare(",\"author\":") == 0) messageStep = MESSAGE_STEP::author;
			else if (ch == ':' && str.compare(",\"timestamp\"") == 0) messageStep = MESSAGE_STEP::timestamp;
			else if (ch == ':' && str.compare("\"body\"") == 0) messageStep = MESSAGE_STEP::body;
			else {
				str += ch;
				continue;
			}
		}
		else if (messageStep == MESSAGE_STEP::source && ch == '}') {
			if (addressType == ADDRESS_TYPE::thread) src = convertJSONStringToThreadAddress(str);
			else if (addressType == ADDRESS_TYPE::server) src = convertJSONStringToServerAddress(str);
			messageStep = MESSAGE_STEP::none;
		}
		else if (messageStep == MESSAGE_STEP::destination && ch == '}') {
			if (addressType == ADDRESS_TYPE::thread) dest = convertJSONStringToThreadAddress(str);
			else if (addressType == ADDRESS_TYPE::server) dest = convertJSONStringToServerAddress(str);
			messageStep = MESSAGE_STEP::none;
		}
		else if (messageStep == MESSAGE_STEP::type && ch == '"') {
			if (str.compare("request") == 0) msgType = MESSAGE_TYPE::request;
			else if (str.compare("result") == 0) msgType = MESSAGE_TYPE::result;
			else if (str.compare("request_list") == 0) msgType = MESSAGE_TYPE::request_list;
			else if (str.compare("result_list") == 0) msgType = MESSAGE_TYPE::result_list;
			messageStep = MESSAGE_STEP::none;
		}
		else if (messageStep == MESSAGE_STEP::author && ch == '"') {
			msgAuthor = str;
			messageStep = MESSAGE_STEP::none;
		}
		else if (messageStep == MESSAGE_STEP::timestamp && ch == ',') {
			str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
			ts = TestTimer::timePointFromEpochTime(str);
			messageStep = MESSAGE_STEP::none;
		}
		else if (messageStep == MESSAGE_STEP::body) {
			if (ch == '{') bodyBrackets++;
			if (bodyBrackets > 0) str += ch;
			if (ch == '}') bodyBrackets--;
			continue;
		}
		else {
			str += ch;
			continue;
		}
		str = "";
	}

	TestMessage msg{ src, dest, msgType, msgAuthor, ts, msgBody };
	return msg;
}

ThreadAddress* TestMessageParser::convertJSONStringToThreadAddress(std::string addr) {

	THREAD_TYPE threadType;
	size_t threadId;

	enum THREAD_STEP { none, type, id };
	THREAD_STEP currentStep = THREAD_STEP::none;
	std::string str = "";

	for (char ch : addr) {
		str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
		if (currentStep == THREAD_STEP::none) {
			if (ch == '"' && str.compare("\"type\":") == 0) {
				currentStep = THREAD_STEP::type;
				str = "";
			}
			else if (ch == ':' && str.compare(",\"id\"") == 0) {
				currentStep = THREAD_STEP::id;
				str = "";
			}
			else str += ch;
		}
		else if (currentStep == THREAD_STEP::type && ch == '"') {
			if (str.compare("parent") == 0) threadType = THREAD_TYPE::parent;
			else if (str.compare("child") == 0) threadType = THREAD_TYPE::child;
			currentStep = THREAD_STEP::none;
			str = "";
		}
		else str += ch;
	}

	if (currentStep == THREAD_STEP::id) {
		std::stringstream ss(str);
		ss >> threadId;
	}

	ThreadAddress ta{ threadType, threadId };
	return &ta;
}

ServerAddress* TestMessageParser::convertJSONStringToServerAddress(std::string addr) {

	IP_VERSION ipVersion;
	std::string ipAddress;
	size_t serverPort;

	enum SERVER_STEP { none, version, ip, port };
	SERVER_STEP currentStep = SERVER_STEP::none;
	std::string str = "";

	for (char ch : addr) {
		str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
		if (currentStep == SERVER_STEP::none) {
			if (ch == '"' && str.compare("\"version\":") == 0) {
				currentStep = SERVER_STEP::version;
				str = "";
			}
			else if (ch == '"' && str.compare(",\"ip\":") == 0) {
				currentStep = SERVER_STEP::ip;
				str = "";
			}
			else if (ch == ':' && str.compare(",\"port\"")) {
				currentStep = SERVER_STEP::port;
				str = "";
			}
			else str += ch;
		}
		else if (currentStep == SERVER_STEP::version && ch == '"') {
			if (str.compare("IPV4") == 0) ipVersion = IP_VERSION::IPV4;
			else if (str.compare("IPV6") == 0) ipVersion = IP_VERSION::IPV6;
			currentStep = SERVER_STEP::none;
			str = "";
		}
		else if (currentStep == SERVER_STEP::ip && ch == '"') {
			ipAddress = str;
			currentStep = SERVER_STEP::none;
			str = "";
		}
		else str += ch;
	}

	if (currentStep == SERVER_STEP::port) {
		std::stringstream ss(str);
		ss >> serverPort;
	}

	ServerAddress sa{ ipVersion, ipAddress, serverPort };
	return &sa;
}

std::string TestMessageParser::convertRequestListToJSONBody(std::list<std::string> tests) {

	std::string body = "{ \"count\": " + std::to_string(tests.size()) + ", \"tests\": [ ";

	for (auto it = tests.begin(); it != tests.end(); it++) {
		if (it != tests.begin()) {
			body += ", ";
		}
		body += *it;
	}

	body += " ] }";
	return body;
}

std::string TestMessageParser::convertTestResultToJSONBody(TEST_RESULT result, std::string messageText) {
	if (result == TEST_RESULT::pass)
		return "{ \"result\": \"pass\", \"message\": \"" + messageText + "\" }";
	else if (result == TEST_RESULT::fail)
		return "{ \"result\": \"fail\", \"message\": \"" + messageText + "\" }";
	else if (result == TEST_RESULT::exception)
		return "{ \"result\": \"exception\", \"message\": \"" + messageText + "\" }";
	return "";
}

TEST_RESULT TestMessageParser::getTestResultFromBody(TestMessage message) {

	bool result = false;
	std::string str = "";

	for (char ch : message.body) {
		if (result) {
			if (ch == '\"') {
				str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
				if (str.compare("pass") == 0) return TEST_RESULT::pass;
				if (str.compare("fail") == 0) return TEST_RESULT::fail;
				if (str.compare("exception") == 0) return TEST_RESULT::exception;
				break;
			}
			else str += ch;
		}
		else {
			str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
			if (str.compare("{\"result\":\"") == 0) {
				result = true;
				str = ch;
			}
			else str += ch;
		}
	}

	return TEST_RESULT::invalid;
}

std::string TestMessageParser::getTestResultMessageFromBody(TestMessage message) {

	bool startMsg = false;
	bool resultMsg = false;
	std::string str = "";

	for (char ch : message.body) {
		if (resultMsg) {
			if (ch == '\"') return str;
			else str += ch;
		}
		else if (startMsg) {
			str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
			if (str.compare("\"message\":\"") == 0) {
				resultMsg = true;
				str = ch;
			}
			else str += ch;
		}
		else if (ch == ',') startMsg = true;
	}

	return "";
}