#include "TestExceptionHandler.h"

//////////////////////////////////////////////////////
// TestExceptionHandler.cpp							//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
* Implementation of TextExceptionHandler class.
*
* This class is used to print out the caught excpetions and obtains the exception messages.
* Depending on the log level a different level of detail for the excpetion messages are returned.
*
*/


using namespace TestSuite;

string TestExceptionHandler::getCustomizedString(exception& e, LOG_LEVEL logLevel) {
	string logDetail = ""; // initialize the return string for the exception handler
	string except_str = ""; // string that indicates the type of exception

	if (typeid(e) == typeid(std::bad_alloc)) {
		except_str = "Failure to allocate storage.";
	}
	else if (typeid(e) == typeid(std::bad_array_new_length)) {
		except_str = "Invalid array lengths.";
	}
	else if (typeid(e) == typeid(std::bad_cast)) {
		except_str = "A dynamic_cast to a reference type fails the";
		except_str += "\n run - time check.";
	}
	else if (typeid(e) == typeid(std::bad_exception)) {
		except_str = "Failure exception thrown during runtime.";
	}
	else if (typeid(e) == typeid(std::bad_typeid)) {
		except_str = "A typeid operator is applied to a dereferenced";
		except_str += "\n null pointer value of a polymorphic type.";
	}
	else if (typeid(e) == typeid(std::bad_weak_ptr)) {
		except_str = "A std::weak_ptr refers to an already deleted";
		except_str += "\n object.";
	}
	else if (typeid(e) == typeid(std::logic_error)) {
		except_str = "Faulty logic within the program.";
	}
	else if (typeid(e) == typeid(std::runtime_error)) {
		except_str = "Error detected during runtime.";
	}
	else if (typeid(e) == typeid(std::invalid_argument)) {
		except_str = "Invalid argument.";
	}
	else if (typeid(e) == typeid(std::domain_error)) {
		except_str = "Domain error, outside of the subset of values";
		except_str += "\n domain is defined for.";
	}
	else if (typeid(e) == typeid(std::length_error)) {
		except_str = "Length error.";
	}
	else if (typeid(e) == typeid(std::out_of_range)) {
		except_str = "Out of range.";
	}
	else if (typeid(e) == typeid(std::range_error)) {
		except_str = "Range error, result of computation cannot";
		except_str += "\n be represeneted by destination type.";
	}
	else if (typeid(e) == typeid(std::overflow_error)) {
		except_str = "Overflow error, result is either infinite";
		except_str += "\n or too large to represent in the numeric type being returned by the function.";
	}
	else if (typeid(e) == typeid(std::underflow_error)) {
		except_str = "Underflow error, result is not zero, but is";
		except_str += "\n too small to be represented by any other value in the type being returned by";
		except_str += "\n the function.";
	}
	else if (typeid(e) == typeid(std::system_error)) {
		except_str = "System error, exception thrown by various";
		except_str += "\n library functions.";
	}
	else if (typeid(e) == typeid(std::ios_base::failure)) {
		except_str = "Exception thrown on failure by the functions";
		except_str += "\n in the Input / Output library.";
	}
	else {
		except_str = e.what();
	}

	switch (logLevel) {
	case LOG_LEVEL::info:
		logDetail = " Test failed with exception."; // level 1 exception
		break;
	case LOG_LEVEL::detail:
		logDetail = " Test failed with the exception: " + except_str; // level 2 exception
		break;
	case LOG_LEVEL::debug:
		logDetail = " Test failed with the exception: " + except_str;
		logDetail += "\n Exception occurred on " + TestTimer::currentTime() + "."; // level 3 exception
		break;
	}

	return logDetail;

}