#include "BasicCalculator.h"

//////////////////////////////////////////////////////
// BasicCalculator.cpp								//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* Implementation of BasicCalculator class.
*
* This class is used by some of the Test Driver classes to run the tests.
* Each function here is an arithmetic operation.
*
*/

int BasicCalculator::add(int operand1, int operand2) {
	return operand1 + operand2;
}

int BasicCalculator::subtract(int operand1, int operand2) {
	return operand1 - operand2;
}

int BasicCalculator::multiply(int operand1, int operand2) {
	return operand1 * operand2;
}

int BasicCalculator::divide(int operand1, int operand2) {
	if (operand2 == 0) {
		throw std::runtime_error("Math error: Attempted to divide by Zero.");
	}
	return operand1 / operand2;
}

bool BasicCalculator::isZero(int number) {
	bool result = false;
	if (number != 0) {
		result = true;
	}
	return result;
}

