#include "TestLogger.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include <iomanip>

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




TestLogger::TestLogger(LOGLEVEL log) :logLevel(log) {

}

TestLogger::TestLogger() : logLevel(LOGLEVEL::info) {

}

void TestLogger::writeLogInfoToOutput(std::string message, TestTimer timer) {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //retrieve handle for std ouput device
	SetConsoleTextAttribute(hConsole, 14);	//Set format parameters
	cout << "[Exception] ";					// print the test name
	SetConsoleTextAttribute(hConsole, 15);
	cout << message;
	cout << " Time elapsed: " << timer.timeTaken() << " ns.\n" << endl; // print the time taken
}

void TestLogger::writeLogInfoToOutput(std::string message, TestTimer timer, bool outcome) {
	HANDLE  hConsole;											// Additional logging in this function
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (outcome) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);	//Uses outcome boolean to display pass/fail
		cout << "[Pass] ";
	}
	else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout << "[Fail] ";
	}
	SetConsoleTextAttribute(hConsole, 15);
	cout << message;
	cout << " Time elapsed: " << timer.timeTaken() << " ns.\n" << endl;
}

LOGLEVEL TestLogger::getLogLevel() { return logLevel; }

void TestLogger::setLogLevel(LOGLEVEL log) {
	logLevel = log;
}


void TestLogger::writeTestRunSummary(TestResultCounter counter, TestTimer timer) {
	cout << "Test Result Summary" << endl;	//print the summary of results for total, passed, and failed
	cout << "-------------------" << endl;
	cout << left << setw(10) << "Total Tests " << right << setw(10) << counter.getTestsTotal() << endl;
	cout << left << setw(10) << "Tests Passed" << right << setw(10) << counter.getTestsPassed() << endl;
	cout << left << setw(10) << "Tests Failed" << right << setw(10) << counter.getTestsFailed() << endl;
	//TODO:Add timer logic,below line gives a weird format
	//cout << left << setw(10) << "Time Taken " << right << setw(20) << timer.timeTaken() << endl;
}