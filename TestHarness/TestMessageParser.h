#pragma once
#include <stack>
#include "TestMessage.h"

namespace TestSuite {

	enum class TEST_RESULT { pass, fail, exception, invalid };

	static class TestMessageParser {
	public:
		static std::string convertMessageToJSONString(TestMessage message);
		static TestMessage convertJSONStringToMessage(std::string messageString);
		static std::string convertTestResultToJSONBody(TEST_RESULT result, std::string messageText);
		static TEST_RESULT getTestResultFromBody(TestMessage message);
		static std::string getTestResultMessageFromBody(TestMessage message);
	private:
		static ThreadAddress* convertJSONStringToThreadAddress(std::string addr);
		static ServerAddress* convertJSONStringToServerAddress(std::string addr);
	};
}