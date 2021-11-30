#pragma once
#include "ITest.h"
#include "MemoryAllocator.h"

//////////////////////////////////////////////////////
// MemoryAllocatorTestDriverException1.h			//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is part of the TEST functions that the TestHarness runs through
* It uses the MemoryAllocator class to throw an exception.
*
*/

class MemoryAllocatorTestDriverException1 : public ITest {
public:
	bool TEST() {
		MemoryAllocator allocator{};
		std::vector<std::string> vec(2);
		std::list<double> lst(100);
		if (vec == allocator.allocStringVector(-2) && lst == allocator.allocDoubleList(100)) { // expect exception here
			return true;
		}
		return false;
	}
};