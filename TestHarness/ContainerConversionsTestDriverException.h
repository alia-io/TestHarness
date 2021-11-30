#pragma once
#include "ITest.h"
#include "ContainerConversions.h"

//////////////////////////////////////////////////////
// ContainerConversionsTestDriverException.h		//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is part of the TEST functions that the TestHarness runs through
* The function used in TEST passes the elements of one type of container
* into a different type of container.
*
*/

class ContainerConversionsTestDriverException : public ITest {
public:
	bool TEST() {
		ContainerConversions converter{};
		std::list<int> lst = { 1, 2, 3, 4, 5 };
		std::vector<int> vec = converter.listToVector(lst);
		vec.at(5) = 6;				// this will cause an exception
		int i = 0;
		for (auto it = lst.begin(); it != lst.end(); ++it) {
			if (vec[i] != *it) {
				if (i == vec.size()) return true;
				else return false;
			}
		}
		return true;
	}
};