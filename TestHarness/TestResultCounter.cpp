#include "TestResultCounter.h"

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

void TestResultCounter::setTotalTests(int count) { totalTests = count; };	// set the total test amount
void TestResultCounter::incrementTestPassed() { testsPassed++; };		// increment tests passed
void TestResultCounter::incrementTestFailed() { testsFailed++; };		// increment tests failed 


int TestResultCounter::getTestsPassed() { return testsPassed; };	// return counter variables
int TestResultCounter::getTestsFailed() { return testsFailed; };
int TestResultCounter::getTestsTotal() { return totalTests; }
