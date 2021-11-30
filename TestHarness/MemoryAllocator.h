#pragma once
#include <vector>
#include <list>
#include <string>

//////////////////////////////////////////////////////
// MemoryAllocator.h								//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* This class is used to Test the application by allocating memory for containers
* correctly or incorrectly. The main purpose of this class is to be used to
* throw exceptions.
*/

class MemoryAllocator {
public:
	std::vector<std::string> allocStringVector(int sz);
	std::list<double> allocDoubleList(int sz);
};