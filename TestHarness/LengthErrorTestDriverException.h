#pragma once
#include "ITest.h"
#include <vector>

//////////////////////////////////////////////////////
// LengthErrorTestDriverException.h					//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is part of the TEST functions that the TestHarness runs through.
* It exists to throw an exception.
*
*/

class LengthErrorTestDriverException : public ITest {
public:
	bool TEST() {
		std::vector<int> vec;
		vec.resize(vec.max_size() + 1);
		return true;
	}
};