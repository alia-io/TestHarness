#pragma once
#include "ITest.h"
#include "MemoryAllocator.h"

//////////////////////////////////////////////////////
// MemoryAllocatorTestDriverException2.h			//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is part of the TEST functions that the TestHarness runs through
* It uses the MemoryAllocator class to throw an exception.
*
*/

class MemoryAllocatorTestDriverException2 : public ITest {
public:
	bool TEST() {
		MemoryAllocator allocator{};
		std::vector<std::string> vec = allocator.allocStringVector(5);
		if (vec.at(5) != "\0") {	// this should throw an exception
			return false;
		}
		return true;
	}
};