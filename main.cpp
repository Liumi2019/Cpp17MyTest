#include <iostream>
#include <vector>
#include <thread>
#include <chrono>


#include "Cpp17MytestHead.h"
#include "threadLeakage.h"

int main() {
	std::cout << "Start ..." << std::endl;

	// test_qualifier::test_qualifier();
	threadLeakage();

	std::this_thread::sleep_for(std::chrono::seconds(20));
	std::cout << "End." << std::endl;
	return 0;
}