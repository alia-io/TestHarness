#pragma once
#include <string>
using std::string;

class DllLoader {
public:
	void dllLoader(string dllName);
private:
	typedef bool(__cdecl* testFunc)();
};