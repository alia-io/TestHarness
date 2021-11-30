#include "AdvCalculator.h"

//////////////////////////////////////////////////////
// AdvCalculator.cpp								//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* Implementation of AdvCalculator class.
*
* This class is used by some of the Test Driver classes to run the tests.
* Each function here is an arithmetic operation.
*
*/

int AdvCalculator::exp(int operand1, int operand2) {
	if (operand2 != 0) { //check if the power is non-zero
		return (operand1 * exp(operand1, operand2 - 1)); //multiply the base with itself until power is zero
	}
	else {
		return 1; //power is zero and base^0=1
	}
}

int AdvCalculator::modulo(int operand1, int operand2) {
	return operand1 % operand2;
}

int AdvCalculator::factorial(int operand1) {
	if (operand1 != 0) { //check if the power is non-zero
		return (operand1 * factorial(operand1 - 1)); //multiply the operand with operand-1 recursively
	}
	else {
		return 1; //factorial of zero = 1
	}
}

int AdvCalculator::gcd(int operand1, int operand2) {
	if (operand1 == 0) {	//return gcd of the operand that is non-zero
		return operand2;
	}
	if (operand2 == 0) {
		return operand1;
	}

	if (operand1 > operand2) {
		return gcd(operand1 - operand2, operand2); //subtract the smaller num from the larger until they are equal
	}
	else {
		return gcd(operand1, operand2 - operand1);
	}
}