#include "TestDriver.h"

bool testBasicCalculatorPassScenario() {	// expect PASS
	BasicCalculatorTestDriverPass calc{};
	return calc.TEST();
}

bool testBasicCalculatorFailScenario() {	// expect FAIL
	BasicCalculatorTestDriverFail calc{};
	return calc.TEST();
}

bool testBasicCalculatorTestDriverExceptionScenario() {	// expect EXCEPTION
	BasicCalculatorTestDriverException calc{};
	return calc.TEST();
}

bool testAdvCalculatorTestDriverPassScenario() {	// expect PASS
	AdvCalculatorTestDriverPass calc{};
	return calc.TEST();
}

bool testMemoryAllocatorTestDriverExceptionScenario1() {	// expect EXCEPTION
	MemoryAllocatorTestDriverException1 allocator{};
	return allocator.TEST();
}

bool testMemoryAllocatorTestDriverExceptionScenario2() {	// expect EXCEPTION
	MemoryAllocatorTestDriverException2 allocator{};
	return allocator.TEST();
}

bool testContainerConversionsTestDriverFailScenario() {	// expect FAIL
	ContainerConversionsTestDriverFail converter{};
	return converter.TEST();
}

bool testContainerConversionsTestDriverExceptionScenario() {	// expect EXCEPTION
	ContainerConversionsTestDriverException converter{};
	return converter.TEST();
}

bool testLengthErrorTestDriverExceptionScenario() {	// expect EXCEPTION
	LengthErrorTestDriverException driver{};
	return driver.TEST();
}

bool testOverflowErrorTestDriverExceptionScenario() {	// expect EXCEPTION
	OverflowErrorTestDriverException driver{};
	return driver.TEST();
}

class Item {
public:
	std::string name;
	bool (*pointer)();
};

static class TestGetter {
public:
	static Item getTest(std::string testName) {
		if (testName.compare("TestBasicCalculatorPass") == 0) return Item{ testName, *testBasicCalculatorPassScenario };
		if (testName.compare("TestBasicCalculatorFail") == 0) return Item{ testName, *testBasicCalculatorFailScenario };
		if (testName.compare("TestBasicCalculatorException") == 0) return Item{ testName, *testBasicCalculatorTestDriverExceptionScenario };
		if (testName.compare("TestAdvancedCalculatorPass") == 0) return Item{ testName, *testAdvCalculatorTestDriverPassScenario };
		if (testName.compare("TestMemoryAllocatorException1") == 0) return Item{ testName, *testMemoryAllocatorTestDriverExceptionScenario1 };
		if (testName.compare("TestMemoryAllocatorException2") == 0) return Item{ testName, *testMemoryAllocatorTestDriverExceptionScenario2 };
		if (testName.compare("TestContainerConversionsFail") == 0) return Item{ testName, *testContainerConversionsTestDriverFailScenario };
		if (testName.compare("TestContainerConversionsException") == 0) return Item{ testName, *testContainerConversionsTestDriverExceptionScenario };
		if (testName.compare("TestLengthErrorException") == 0) return Item{ testName, *testLengthErrorTestDriverExceptionScenario };
		if (testName.compare("TestOverflowErrorException") == 0) return Item{ testName, *testOverflowErrorTestDriverExceptionScenario };
	}
};