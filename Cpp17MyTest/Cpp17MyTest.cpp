#include "Cpp17MyTest.h"

#include <iostream>
#include <vector>

void testVector() {

	std::vector v1 = { 12, 13, 57 };

	for (auto i : v1) {
		std::cout << i << std::endl;
	}
}
