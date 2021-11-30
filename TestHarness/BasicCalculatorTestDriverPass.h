#pragma once
#include "ITest.h"
#include "BasicCalculator.h"

//////////////////////////////////////////////////////
// BasicCalculatorTestDriverPass.h					//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is part of the TEST functions that the TestHarness runs through
* Each function used in TEST is an arithmetic operation.
*
*/

class BasicCalculatorTestDriverPass : public ITest {
public:
	bool TEST() {
		BasicCalculator calc{};
		bool outcome = false;
		if (calc.add(2, 2) == 4 && calc.add(1, 0) == 1 && calc.add(0, 12) == 12 &&
			calc.subtract(2, 2) == 0 && calc.subtract(5, 2) == 3 && calc.subtract(0, 5) == -5 && calc.subtract(5, 0) == 5 &&
			calc.multiply(2, 1) == 2 && calc.multiply(-7, 7) == -49 && calc.multiply(0, 0) == 0 && calc.multiply(-4, -3) == 12 &&
			calc.divide(12, 2) == 6 && calc.divide(3, 3) == 1 && calc.divide(0, 4) == 0 && calc.divide(15, 1) == 15) {
			outcome = true;
		}
		return outcome;
	}
};