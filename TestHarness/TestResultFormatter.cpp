#include "TestResultFormatter.h"

std::string TestResultFormatter::testPassedMessage(std::string testName, TestTimer timer) {
	return " [PASS] " + testName + "\n        Time elapsed: " + std::to_string(timer.timeTaken()) + " ns.";
}

std::string TestResultFormatter::testFailedMessage(std::string testName, TestTimer timer) {
	return " [FAIL] " + testName + "\n        Time elapsed: " + std::to_string(timer.timeTaken()) + " ns.";
}

std::string TestResultFormatter::testExceptionMessage(std::string testName, std::exception& e, LOG_LEVEL logLevel) {
	switch (logLevel) {
	case LOG_LEVEL::info:	// level 1 logging
		return " [EXCEPTION] " + testName + "\n        Test failed with exception.";
	case LOG_LEVEL::detail:	// level 2 logging
		return " [EXCEPTION] " + testName + "\n        Test failed with exception: " + exceptionDetails(e);
	case LOG_LEVEL::debug:	// level 3 logging
		return " [EXCEPTION] " + testName + "\n        Test failed with exception: " + exceptionDetails(e)
			+ "\n        Exception occurred on " + TestTimer::currentTime() + ".";
	}

	return "";
}

std::string TestResultFormatter::exceptionDetails(std::exception& e) {
	if (typeid(e) == typeid(std::bad_alloc)) {
		return "Failure to allocate storage.";
	} else if (typeid(e) == typeid(std::bad_array_new_length)) {
		return "Invalid array lengths.";
	} else if (typeid(e) == typeid(std::bad_cast)) {
		return "A dynamic_cast to a reference type fails the\n        run-time check.";
	} else if (typeid(e) == typeid(std::bad_exception)) {
		return "Failure exception thrown during runtime.";
	} else if (typeid(e) == typeid(std::bad_typeid)) {
		return "A typeid operator is applied to a dereferenced\n        null pointer value of a polymorphic type.";
	} else if (typeid(e) == typeid(std::bad_weak_ptr)) {
		return "A std::weak_ptr refers to an already deleted \n        object.";
	} else if (typeid(e) == typeid(std::logic_error)) {
		return "Faulty logic within the program.";
	} else if (typeid(e) == typeid(std::runtime_error)) {
		return "Error detected during runtime.";
	} else if (typeid(e) == typeid(std::invalid_argument)) {
		return "Invalid argument.";
	} else if (typeid(e) == typeid(std::domain_error)) {
		return "Domain error, outside of the subset of values\n        domain is defined for.";
	} else if (typeid(e) == typeid(std::length_error)) {
		return "Length error.";
	} else if (typeid(e) == typeid(std::out_of_range)) {
		return "Out of range.";
	} else if (typeid(e) == typeid(std::range_error)) {
		return "Range error, result of computation cannot\n        be represeneted by destination type.";
	} else if (typeid(e) == typeid(std::overflow_error)) {
		return "Overflow error, result is either infinite\n        or too large to represent in the numeric type being returned by the function.";
	} else if (typeid(e) == typeid(std::underflow_error)) {
		return "Underflow error, result is not zero, but is\n        too small to be represented by any other value in the type being returned by\n        the function.";
	} else if (typeid(e) == typeid(std::system_error)) {
		return "System error, exception thrown by various\n        library functions.";
	} else if (typeid(e) == typeid(std::ios_base::failure)) {
		return "Exception thrown on failure by the functions\n        in the Input/Output library.";
	} else {
		return e.what();
	}
	return "";
}