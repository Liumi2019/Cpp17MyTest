#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

#include "CppThread.h"

namespace {

	std::mutex mtx;

	void fun_thread1(int aSize, bool isRun) {
		for (int a = 0; a < aSize; a++) {
			mtx.lock();
			std::cout << "a = " << a << " ";
			if (!isRun) {
				std::cout << std::endl;
				return;
			}
			mtx.unlock();
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

	std::thread&& func_return_thread() {
		std::thread tempT3(fun_thread1, 100, true);

		return std::move(tempT3);
	}
}

void test_thread_old() {
	bool runT1 = true;
	bool runT2 = true;

	std::thread t1(fun_thread1, 20, runT1);
	std::thread t2(fun_thread2, 10, runT2, runT1);

	// 线程转移使用权
	std::thread t3 = func_return_thread();

	t1.join();
	t2.join();

	if (t3.joinable()) {
		t3.join();
	}
}


namespace thread_cond {
	std::mutex mtx;
	std::condition_variable_any cond;

	void thread_wait() {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "thread_wait begin wait, id = " << std::this_thread::get_id() << std::endl;
		cond.wait(mtx);
		std::cout << "thread_wait after wait, id = " << std::this_thread::get_id() << std::endl;
	}

	void thread_notify() {
		std::cout << "thread_wait begin notify, id = " << std::this_thread::get_id() << std::endl;
		mtx.lock();
		cond.notify_all();
		mtx.unlock();
		std::cout << "thread_wait after notify, id = " << std::this_thread::get_id() << std::endl;
	}
}

void test_thread() {

	thread_cond::mtx.lock();
	std::thread thread1(thread_cond::thread_notify);

	thread_cond::thread_wait();
	thread_cond::mtx.unlock();

	thread1.join();
}