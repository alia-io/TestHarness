#pragma once
#include "ITest.h"
#include "BasicCalculator.h"

//////////////////////////////////////////////////////
// BasicCalculatorTestDriverException.h				//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is part of the TEST functions that the TestHarness runs through
* Each function used in TEST is an arithmetic operation.
*
*/

class BasicCalculatorTestDriverException : public ITest {
public:
	bool TEST() {
		BasicCalculator calc;
		bool outcome = false;
		if (calc.divide(12, 0) == 6) {
			outcome = true;
		}
		return outcome;
	}
};