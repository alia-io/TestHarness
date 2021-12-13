#include "ResultCounter.h"

//////////////////////////////////////////////////////
// TestResultCounter.cpp							//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* This is the implementation of class TestResultCounter
* This class is to record the count for the amount of passed, failed, and total tests.
*
*/

void ResultCounter::setTotalTests(int count) { totalTests = count; };	// set the total test amount
void ResultCounter::incrementTestPassed() { testsPassed++; };		// increment tests passed
void ResultCounter::incrementTestFailed() { testsFailed++; };		// increment tests failed 


int ResultCounter::getTestsPassed() { return testsPassed; };	// return counter variables
int ResultCounter::getTestsFailed() { return testsFailed; };
int ResultCounter::getTestsTotal() { return totalTests; }
