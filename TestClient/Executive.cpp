#include "MainClient.h"

int main() {

	std::list<std::string> tests = {
		"TestBasicCalculatorPass.dll", "TestBasicCalculatorFail.dll", "TestBasicCalculatorException.dll", "TestAdvancedCalculatorPass.dll",
		"TestMemoryAllocatorException1.dll", "TestMemoryAllocatorException2.dll", "TestContainerConversionsFail.dll",
		"TestContainerConversionsException.dll", "TestLengthErrorException.dll", "TestOverflowErrorException.dll"
	};

	MainClient client{};
	client.runClient(tests);
}