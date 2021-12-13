#include "Client.h"

int main() {

	std::list<std::string> testList {
		"TestBasicCalculatorPass", "TestBasicCalculatorFail", "TestBasicCalculatorException", "TestAdvancedCalculatorPass",
		"TestMemoryAllocatorException1", "TestMemoryAllocatorException2", "TestContainerConversionsFail",
		"TestContainerConversionsException", "TestLengthErrorException", "TestOverflowErrorException"
	};

	Client::runTests(LOG_LEVEL::detail, testList);

	return 0;
}