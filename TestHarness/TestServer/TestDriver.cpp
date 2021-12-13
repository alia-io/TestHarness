#include "TestDriver.h"
#include <stdexcept>

int BasicCalculator::add(int operand1, int operand2) {
	return operand1 + operand2;
}

int BasicCalculator::subtract(int operand1, int operand2) {
	return operand1 - operand2;
}

int BasicCalculator::multiply(int operand1, int operand2) {
	return operand1 * operand2;
}

int BasicCalculator::divide(int operand1, int operand2) {
	if (operand2 == 0) {
		throw std::runtime_error("Math error: Attempted to divide by Zero.");
	}
	return operand1 / operand2;
}

bool BasicCalculator::isZero(int number) {
	bool result = false;
	if (number != 0) {
		result = true;
	}
	return result;
}

int AdvCalculator::exp(int operand1, int operand2) {
	if (operand2 != 0) { //check if the power is non-zero
		return (operand1 * exp(operand1, operand2 - 1)); //multiply the base with itself until power is zero
	}
	else {
		return 1; //power is zero and base^0=1
	}
}

int AdvCalculator::modulo(int operand1, int operand2) {
	return operand1 % operand2;
}

int AdvCalculator::factorial(int operand1) {
	if (operand1 != 0) { //check if the power is non-zero
		return (operand1 * factorial(operand1 - 1)); //multiply the operand with operand-1 recursively
	}
	else {
		return 1; //factorial of zero = 1
	}
}

int AdvCalculator::gcd(int operand1, int operand2) {
	if (operand1 == 0) {	//return gcd of the operand that is non-zero
		return operand2;
	}
	if (operand2 == 0) {
		return operand1;
	}

	if (operand1 > operand2) {
		return gcd(operand1 - operand2, operand2); //subtract the smaller num from the larger until they are equal
	}
	else {
		return gcd(operand1, operand2 - operand1);
	}
}

std::vector<std::string> MemoryAllocator::allocStringVector(int sz) {
	std::vector<std::string> vec(sz);
	return vec;
}

// allocates a list of doubles of size 'sz'.
std::list<double> MemoryAllocator::allocDoubleList(int sz) {
	std::list<double> lst(sz);
	return lst;
}

std::list<int> ContainerConversions::vectorToList(std::vector<int> vec) {
	std::list<int> lst(vec.size());
	auto it = lst.begin();
	for (int i = 0; i < vec.size(); ++i) {		// should throw overflow_error or similar?
		*it = vec[i];
		++it;
	}
	return lst;
}

std::vector<int> ContainerConversions::listToVector(std::list<int> lst) {
	std::vector<int> vec(lst.size());
	int i = 0;
	for (auto it = lst.begin(); it != lst.end(); ++it) {
		vec[i] = *it;
		++i;
	}
	return vec;
}