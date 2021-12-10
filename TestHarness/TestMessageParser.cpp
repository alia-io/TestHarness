#include "TestMessageParser.h"

#include <iostream>

using namespace TestSuite;

TEST_RESULT TestMessageParser::testResult(TestMessage message) {
	
	bool result = false;
	std::string str = "";
	std::string body = message.getMessageBody();

	for (char ch : body) {
		if (result) {
			if (ch == '\"') {
				str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
				if (str.compare("pass") == 0) return TEST_RESULT::pass;
				if (str.compare("fail") == 0) return TEST_RESULT::fail;
				if (str.compare("exception") == 0) return TEST_RESULT::exception;
				break;
			}
			else str += ch;
		} else {
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

std::string TestMessageParser::testResultMessage(TestMessage message) {

	bool startMsg = false;
	bool resultMsg = false;
	std::string str = "";
	std::string body = message.getMessageBody();

	for (char ch : body) {
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
		else {
			if (ch == ',') startMsg = true;
		}
	}

	return "";
}