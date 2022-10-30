#include <iostream>
#include <thread>
#include "CppThread.h"

void fun(int a, bool isRun) {
	for (int a = 0; a < 100; a++) {
		std::cout << "a = " << a << " ";
		if (isRun) {
			std::cout << std::endl;
			return;
		}
	}
	std::cout << std::endl;
}

void test_thread() {
	bool runT1 = false;
	bool runT2 = false;
	std::thread t1(fun, 200, runT1);
	std::thread t2(fun, 100, runT2);

	t1.join();
	t2.join();
}
