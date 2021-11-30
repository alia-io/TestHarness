#pragma once
#include "ITest.h"
#include <bitset>

//////////////////////////////////////////////////////
// OverflowErrorTestDriverException.h				//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is part of the TEST functions that the TestHarness runs through.
* It exists to throw an exception.
*
*/

class OverflowErrorTestDriverException : public ITest {
public:
	bool TEST() {
		std::bitset<100> bs;
		bs[99] = 1;
		bs[0] = 1;
		unsigned long ul = bs.to_ulong();
		return true;
	}
};