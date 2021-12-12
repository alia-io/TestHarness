#include "TestLogger.h"

//////////////////////////////////////////////////////
// TestLogger.cpp									//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* This is the implementation of the TestLogger class
*
* This class is retrieve the logLevel and print the exception messages to a file.
* This class also includes a function for summarizing the test results into a pass/failed section
*
*/

using namespace TestSuite;
using std::cout;	// Identifiers neccesary to properly format output
using std::endl;
using std::setfill;
using std::setw;
using std::left;
using std::right;




TestLogger::TestLogger(LOG_LEVEL log) :logLevel(log) {

}

TestLogger::TestLogger() : logLevel(LOG_LEVEL::info) {

}

void TestLogger::writeLogInfoToOutput(TEST_RESULT result, std::string message, TestTimer timer) {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);		//retrieve handle for std ouput device
	if (result == TEST_RESULT::pass) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		cout << " [PASS] ";
	}
	else if (result == TEST_RESULT::fail) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout << " [FAIL] ";
	}
	else if (result == TEST_RESULT::exception) {
		SetConsoleTextAttribute(hConsole, 14);
		cout << " [EXCEPTION] ";
	}
	SetConsoleTextAttribute(hConsole, 15);
	cout << message << "\n\n";
}

LOG_LEVEL TestLogger::getLogLevel() { return logLevel; }

void TestLogger::setLogLevel(LOG_LEVEL log) { logLevel = log; }


void TestLogger::writeTestRunSummary(TestResultCounter counter, TestTimer timer) {
	cout << "Test Result Summary" << endl;	//print the summary of results for total, passed, and failed
	cout << "-------------------" << endl;
	cout << left << setw(10) << "Total Tests " << right << setw(10) << counter.getTestsTotal() << endl;
	cout << left << setw(10) << "Tests Passed" << right << setw(10) << counter.getTestsPassed() << endl;
	cout << left << setw(10) << "Tests Failed" << right << setw(10) << counter.getTestsFailed() << endl;
	//TODO:Add timer logic,below line gives a weird format
	//cout << left << setw(10) << "Total Time Taken " << right << setw(20) << timer.timeTaken() << endl;
}