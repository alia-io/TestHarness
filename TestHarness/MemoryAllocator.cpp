#include "MemoryAllocator.h"
#include "TestRunner.h"
#include <iostream>

//////////////////////////////////////////////////////
// MemoryAllocator.cpp								//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* Implementation of MemoryAllocator class.
*
* This class is used to Test the application by allocating memory for containers
* correctly or incorrectly. The main purpose of this class is to be used to
* throw exceptions.
*/

// allocates a vector of strings of size 'sz'.
std::vector<std::string> MemoryAllocator::allocStringVector(int sz) {
	std::vector<std::string> vec(sz);
	return vec;
}

// allocates a list of doubles of size 'sz'.
std::list<double> MemoryAllocator::allocDoubleList(int sz) {
	std::list<double> lst(sz);
	return lst;
}