#include <iostream>
#include <vector>
#include <functional>
#include <initializer_list>
#include <tuple>

#include "Cpp17NewFeature.h"

// 容器类型自动推导
void testVector() {
	std::vector v1 = { 12, 13, 57 };

	for (auto i : v1) {
		std::cout << i << std::endl;
	}
}

// 字符串常量初始化
void initChar() {
	// 弃用
	char chr[] = "chr";
	const char chrConst[] = "chrConst";
	auto chrAuto = "123456789101112";

	chr[2] = '2';
	printChar(chr, arrySize(chr));
	printChar(const_cast<char*>(chrConst), arrySize(chrConst));
	// std::cout << sizeof(chrAuto) / sizeof(chrAuto[0]) << std::endl; // 编译警告提示 不能计算出长度
	std::cout << chrAuto[0] << std::endl;
}

void printChar(char* chr, const size_t& size) {
	size_t i = 0;
	while (i < size) {
		std::cout << chr[i];
		++i;
	}
	std::cout << std::endl;
}

// for 语句语法加强
void useVarInit() {
	int a = 5;
	int b = 6;
	if (int c = a + b; c > 10) {
		std::cout << "c > 10" << std::endl;
	}
	// c = 0; // 属于局部变量
}

// 初始化列表
class InitList {
public:
	InitList(std::initializer_list<int> list) {
		for (std::initializer_list<int>::iterator it = list.begin();
			it != list.end(); ++it) {
			vec.push_back(*it);
		}
	}

	void pintInfo() {
		for (auto i : vec) {
			std::cout << i << ", ";
		}
		std::cout << std::endl;
	}

private:
	std::vector<int> vec;
};

// 初始化列表
void useInitList() {
	// { } 内不能窄化
	InitList l1 = { 1, 3, 6, 10, 1 };
	l1.pintInfo();
}

// 结构化绑定
void useStructuredBinding() {
	std::tuple t1 = { "LL", 23, "boy" };
	// name 右值引用类型
	auto [name, age, gender] = t1;

	std::cout << "name:" << name << ", age: " << age << ", gender: " << gender << std::endl;
}

// 枚举类型转换
void useEnum() {
	enum class carName {
		BWM,
		Audi,
		Benci = 5,
		Daz,
		Wuling = 5,
		XiaoPeng
	};

	std::cout << static_cast<int>(carName::BWM) << std::endl; // 0
	std::cout << static_cast<int>(carName::Daz) << std::endl; // 6 默认加 1 只看前一个，不看后边的
}
