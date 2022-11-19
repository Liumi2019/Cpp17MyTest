#include <iostream>
#include <thread>
#include "CppThread.h"

namespace {
	void fun_thread1(int aSize, bool isRun) {
		for (int a = 0; a < aSize; a++) {
			std::cout << "a = " << a << " ";
			if (!isRun) {
				std::cout << std::endl;
				return;
			}
		}
		std::cout << std::endl;
	}

	void fun_thread2(int aSize, bool isRun1, bool isRun2) {
		for (int a = 0; a < aSize; a++) {
			std::cout << "b = " << a << " ";
			if (!isRun1) {
				std::cout << std::endl;
				return;
			}
			if (a == 50) {
				isRun2 = false;
			}
		}
		std::cout << std::endl;
	}
}

void test_thread() {
	bool runT1 = true;
	bool runT2 = true;

	std::thread t1(fun_thread1, 20, runT1);
	std::thread t2(fun_thread2, 10, runT2, runT1);

	t1.join();
	t2.join();
}
