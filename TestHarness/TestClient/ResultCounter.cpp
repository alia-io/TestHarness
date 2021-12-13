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

std::string ResultCounter::testResultSummary() {
	std::string out = " Total Tests           " + std::to_string(totalTests);
	out += "\n                        Tests Passed          " + std::to_string(testsPassed);
	out += "\n                        Tests Failed          " + std::to_string(testsFailed);
	//TODO:Add timer logic,below line gives a weird format
	//cout << left << setw(10) << "Total Time Taken " << right << setw(20) << timer.timeTaken() << endl;
	return out;
}