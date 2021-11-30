#pragma once
#include <string>

class TestItem {
private:
	std::string name;
	bool (*pointer)();
public:
	TestItem(std::string testName, bool (*testPointer)());
	std::string getName();
	auto* getPointer() { return pointer; }
};