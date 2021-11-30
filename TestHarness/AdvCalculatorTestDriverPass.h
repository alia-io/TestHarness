#pragma once
#include "ITest.h"
#include "AdvCalculator.h"

//////////////////////////////////////////////////////
// AdvCalculatorTestDriverPass.h					//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is part of the TEST functions that the TestHarness runs through
* Each function used in TEST is an arithmetic operation.
*
*/

class AdvCalculatorTestDriverPass : public ITest {
public:
	bool TEST() {
		AdvCalculator calc{};
		bool outcome = false;
		if (calc.exp(2, 2) == 4 && calc.exp(3, 3) == 27 && calc.exp(1, 0) == 1 && calc.exp(12, 0) == 1 &&
			calc.modulo(2, 2) == 0 && calc.modulo(5, 2) == 1 && calc.modulo(0, 5) == 0 &&
			calc.factorial(2) == 2 && calc.factorial(7) == 5040 && calc.factorial(0) == 1 && calc.factorial(1) == 1 &&
			calc.gcd(12, 2) == 2 && calc.gcd(3, 3) == 3 && calc.gcd(4, 0) == 4 && calc.gcd(0, 8) == 8) {
			outcome = true;
		}
		return outcome;
	}
};