#pragma once
#include <list>
#include <vector>

//////////////////////////////////////////////////////
// ContainerConversions.h							//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is used by some of the Test Driver classes to run the tests.
* The functions here pass the elements of one type of container into a
* different type of container.
*
*/

class ContainerConversions {
public:
	std::list<int> vectorToList(std::vector<int>);
	std::vector<int> listToVector(std::list<int>);
};