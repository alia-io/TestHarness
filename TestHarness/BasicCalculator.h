#pragma once
#include <string>
#include <stdexcept>

//////////////////////////////////////////////////////
// BasicCalculator.h								//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is used by some of the Test Driver classes to run the tests.
* Each function here is an arithmetic operation.
*
*/

class BasicCalculator
{
public:
	int add(int operand1, int operand2);
	int subtract(int operand1, int operand2);
	int multiply(int operand1, int operand2);
	int divide(int operand1, int operand2);
	bool isZero(int number);
};

