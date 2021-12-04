#pragma once
#include <stack>
#include "TestMessage.h"

namespace TestSuite {

	enum class TEST_RESULT { pass, fail, exception, invalid };

	static class TestMessageParser {
	public:
		static TEST_RESULT testResult(TestMessage message);
		static std::string testResultMessage(TestMessage message);
	};
}