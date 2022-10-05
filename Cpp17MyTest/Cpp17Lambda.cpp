#include"Cpp17Lambda.h"

void lambdaValue() {
	int a = 50;
	auto aPrint = [a](int b) { return a + b; };

	a = 100;
	std::cout << aPrint(60) << std::endl;  // 110 不是 160
}

void lambdaRef() {
	int a = 50;
	auto aPrint = [&a](int b) { return a + b; };

	a = 100;
	std::cout << aPrint(60) << std::endl;  // 110 不是 160
}

void lambdaGenerics()
{
	auto a = [](auto x, auto y) {
		return x + y;
	};

	std::cout << a(5, 10) << " " << a(5.1, 10.2) << std::endl;
}

void printA(int a) {
	std::cout << a << std::endl;
}
void usingFunctional()
{
	std::vector<std::function<void(int)>> funcV = { printA };
	funcV[0](30);
}

std::vector<int> getBuff() {
	std::vector<int> a = std::vector(1000, 20);
	std::cout << "*a: " << &a << std::endl;
	return a;
}

std::vector<int>&& getBuffMove() {
	std::vector<int> a = std::vector(1000, 20);
	std::cout << "*a: " << &a << std::endl;
	return std::move(a);
}

void usingRightVlaue()
{
	auto a1 = getBuff();
	std::cout << "*a1: " << &a1 << std::endl;

	auto a2 = getBuffMove();
	std::cout << "*a2: " << &a2 << std::endl;

}
