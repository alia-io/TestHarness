#pragma once
//////////////////////////////////////////////////////
// TestResultCounter.h								//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is to record the count for the amount of passed, failed, and total tests.
*
*/


class ResultCounter
{
private:
	int testsPassed;
	int testsFailed;
	int totalTests;
public:
	void setTotalTests(int count);
	void incrementTestPassed();
	void incrementTestFailed();
	int getTestsPassed();
	int getTestsFailed();
	int getTestsTotal();
};

