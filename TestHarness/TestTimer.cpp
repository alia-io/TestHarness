#include "TestTimer.h"
#include <chrono>
#include <sstream>
#include <regex>

//////////////////////////////////////////////////////
// TestTimer.cpp									//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* Implementation of the TestTimer class.
* This class is used to report current time as well as instantiated time slices.
*
*/

using  std::chrono::system_clock;
using  std::chrono::duration_cast;
using  std::chrono::nanoseconds;

void TestTimer::startTimer() {
	startTime = system_clock::now();	// Sets a start time when called.  
}

void TestTimer::endTimer() {
	endTime = system_clock::now(); // Sets an end time when called.
}

double TestTimer::timeTaken() {
	return duration_cast<nanoseconds>(endTime - startTime).count(); // Used to determine amount of time between start and end time which is two points within code.
}

std::string TestTimer::currentTime() {		// Function that returns formatted current time
	time_t now = system_clock::to_time_t(system_clock::now());
	char buf[30]{ '\0' };
	ctime_s(buf, sizeof(buf), &now);
	std::stringstream stream;
	stream << buf;
	std::string time = std::regex_replace(stream.str(), std::regex("\\s+$"), std::string(""));
	return time;
}

int64_t TestTimer::epochTimeFromTimePoint(time_point<system_clock> timestamp) {
	return std::chrono::duration_cast<std::chrono::seconds>(timestamp.time_since_epoch()).count();
}

time_point<system_clock> TestTimer::timePointFromEpochTime(std::string epochTime) {
	int64_t epochTimeInt;
	std::istringstream iss(epochTime);
	iss >> epochTimeInt;
	time_point<system_clock> time{ std::chrono::seconds{epochTimeInt} };
	return time;
}