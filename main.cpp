#include <iostream>
#include <vector>

#include "Cpp17MyTest/Cpp17MytestHead.h"

int main() {
	std::cout << "Start ..." << std::endl;

	test_qualifier::test_qualifier();

	int a(7.5);
	int b{ 7 };
	std::cout << a + b << std::endl;
	return 0;
}