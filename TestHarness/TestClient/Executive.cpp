#include "Client.h"
#include <iostream>
#include <windows.h>

int main() {

	::Sleep(5000);	// delay to set up consoles

	std::list<std::string> testList {
		"TestBasicCalculatorPass", "TestBasicCalculatorFail", "TestBasicCalculatorException", "TestAdvancedCalculatorPass",
		"TestMemoryAllocatorException1", "TestMemoryAllocatorException2", "TestContainerConversionsFail",
		"TestContainerConversionsException", "TestLengthErrorException", "TestOverflowErrorException"
	};

	Client::runTests(LOG_LEVEL::detail, testList);

	return 0;
}