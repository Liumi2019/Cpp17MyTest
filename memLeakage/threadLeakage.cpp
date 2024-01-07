#include "threadLeakage.h"

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

constexpr int leagth = 1000 * 1000 * 1000;

void threadLeakage() {

    std::thread thread1([]() {
        int i = 0;
        std::vector<int*> ptrs;
        while (i < 1000) {
            constexpr int size = 1080 * 1920 * 4 * 4;
            int* ptr = new int[size];
            printPtr(ptr, "new int*");
            std::this_thread::sleep_for(std::chrono::microseconds(50));
            std::cout << "thread1 new int" << std::endl;
            ptrs.push_back(ptr);
        }

        while (ptrs.size() > 0) {
            int* ptr = ptrs.back();
            printPtr(ptr, "delete int*");
            delete[] ptr;
            ptrs.pop_back();
        }

        std::cout << "test_threadLeakage end" << std::endl;
        });

    thread1.detach();
}

void printPtr(void* ptr, std::string info) {
    std::cout << "ptr: " << ptr << ", info: " << info << std::endl;
}
