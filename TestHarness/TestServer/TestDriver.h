#pragma once
#include <string>
#include <list>
#include <vector>
#include <bitset>

class ITest {
public:
	virtual bool TEST() = 0;
};

class BasicCalculator
{
public:
	int add(int operand1, int operand2);
	int subtract(int operand1, int operand2);
	int multiply(int operand1, int operand2);
	int divide(int operand1, int operand2);
	bool isZero(int number);
};

class AdvCalculator
{
public:
	int exp(int operand1, int operand2);
	int modulo(int operand1, int operand2);
	int factorial(int operand1);
	int gcd(int operand1, int operand2);
};

class MemoryAllocator {
public:
	std::vector<std::string> allocStringVector(int sz);
	std::list<double> allocDoubleList(int sz);
};

class ContainerConversions {
public:
	std::list<int> vectorToList(std::vector<int>);
	std::vector<int> listToVector(std::list<int>);
};

class BasicCalculatorTestDriverPass : public ITest {
public:
	bool TEST() {
		BasicCalculator calc{};
		bool outcome = false;
		if (calc.add(2, 2) == 4 && calc.add(1, 0) == 1 && calc.add(0, 12) == 12 &&
			calc.subtract(2, 2) == 0 && calc.subtract(5, 2) == 3 && calc.subtract(0, 5) == -5 && calc.subtract(5, 0) == 5 &&
			calc.multiply(2, 1) == 2 && calc.multiply(-7, 7) == -49 && calc.multiply(0, 0) == 0 && calc.multiply(-4, -3) == 12 &&
			calc.divide(12, 2) == 6 && calc.divide(3, 3) == 1 && calc.divide(0, 4) == 0 && calc.divide(15, 1) == 15) {
			outcome = true;
		}
		return outcome;
	}
};

class BasicCalculatorTestDriverFail : public ITest {
public:
	bool TEST() {
		BasicCalculator calc;
		bool outcome = false;
		if (calc.add(2, 2) != 4 && calc.add(3, 3) != 9 && calc.add(1, 0) != 1 && calc.add(0, 12) != 12 &&
			calc.subtract(2, 2) != 0 && calc.subtract(5, 2) != 3 && calc.subtract(0, 5) != -5 && calc.subtract(5, 0) == 5 &&
			calc.multiply(2, 1) != 2 && calc.multiply(-7, 7) != -49 && calc.multiply(0, 0) != 0 && calc.multiply(-4, -3) == 12 &&
			calc.divide(12, 2) != 6 && calc.divide(3, 3) != 1 && calc.divide(0, 4) == 0 && calc.divide(15, 1) == 15) {
			outcome = true;
		}
		return outcome;
	}
};

class BasicCalculatorTestDriverException : public ITest {
public:
	bool TEST() {
		BasicCalculator calc;
		bool outcome = false;
		if (calc.divide(12, 0) == 6) {
			outcome = true;
		}
		return outcome;
	}
};

class AdvCalculatorTestDriverPass : public ITest {
public:
	bool TEST() {
		AdvCalculator calc{};
		bool outcome = false;
		if (calc.exp(2, 2) == 4 && calc.exp(3, 3) == 27 && calc.exp(1, 0) == 1 && calc.exp(12, 0) == 1 &&
			calc.modulo(2, 2) == 0 && calc.modulo(5, 2) == 1 && calc.modulo(0, 5) == 0 &&
			calc.factorial(2) == 2 && calc.factorial(7) == 5040 && calc.factorial(0) == 1 && calc.factorial(1) == 1 &&
			calc.gcd(12, 2) == 2 && calc.gcd(3, 3) == 3 && calc.gcd(4, 0) == 4 && calc.gcd(0, 8) == 8) {
			outcome = true;
		}
		return outcome;
	}
};

class MemoryAllocatorTestDriverException1 : public ITest {
public:
	bool TEST() {
		MemoryAllocator allocator{};
		std::vector<std::string> vec(2);
		std::list<double> lst(100);
		if (vec == allocator.allocStringVector(-2) && lst == allocator.allocDoubleList(100)) { // expect exception here
			return true;
		}
		return false;
	}
};

class MemoryAllocatorTestDriverException2 : public ITest {
public:
	bool TEST() {
		MemoryAllocator allocator{};
		std::vector<std::string> vec = allocator.allocStringVector(5);
		if (vec.at(5) != "\0") {	// this should throw an exception
			return false;
		}
		return true;
	}
};

class ContainerConversionsTestDriverFail : public ITest {
public:
	bool TEST() {
		ContainerConversions converter{};
		std::vector<int> vec = { 1, 2, 3, 4, 5 };
		std::list<int> lst = converter.vectorToList(vec);
		int i = 1;							// this will cause a fail
		for (auto it = lst.begin(); it != lst.end(); ++it) {
			if (vec[i] != *it) return false;
			++i;
		}
		return true;
	}
};

class ContainerConversionsTestDriverException : public ITest {
public:
	bool TEST() {
		ContainerConversions converter{};
		std::list<int> lst = { 1, 2, 3, 4, 5 };
		std::vector<int> vec = converter.listToVector(lst);
		vec.at(5) = 6;				// this will cause an exception
		int i = 0;
		for (auto it = lst.begin(); it != lst.end(); ++it) {
			if (vec[i] != *it) {
				if (i == vec.size()) return true;
				else return false;
			}
		}
		return true;
	}
};

class LengthErrorTestDriverException : public ITest {
public:
	bool TEST() {
		std::vector<int> vec;
		vec.resize(vec.max_size() + 1);
		return true;
	}
};

class OverflowErrorTestDriverException : public ITest {
public:
	bool TEST() {
		std::bitset<100> bs;
		bs[99] = 1;
		bs[0] = 1;
		unsigned long ul = bs.to_ulong();
		return true;
	}
};