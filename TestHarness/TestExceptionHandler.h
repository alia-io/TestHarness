#pragma once
#include <iostream>
#include <string>
#include "TestLogger.h"
#include "TestTimer.h"

//////////////////////////////////////////////////////
// TestExceptionHandler.h							//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is used to print out the caught excpetions and obtains the exception messages.
* Depending on the log level a different level of detail for the excpetion messages are returned.
*
*/

using namespace TestSuite;
using namespace std;

class TestExceptionHandler
{
public:
	string getCustomizedString(exception& e, LOGLEVEL logLevel);

};