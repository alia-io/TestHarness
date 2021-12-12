#pragma once
#include <string>

class TestItem {
private:
	std::string name;
	bool (*pointer)();
public:
	TestItem(std::string testName, bool (*testPtr)()) : name{ testName }, pointer{ testPtr } { }
	std::string getName() { return name; }
	auto* getPointer() { return pointer; }
};