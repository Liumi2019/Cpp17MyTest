#ifndef CPP17_MY_TEST_H
#define CPP17_MY_TEST_H

#include <iostream>
#include <vector>

// C++17 vector 类型自动推导
// vector<int> a = {1, 2}; -> vector a = {1, 2};
void testVector();

// 初始化字符串常量
void initChar();

void printChar(char* chr, const size_t& size);

template <class T, size_t SIZE>
size_t arrySize(T(&a)[SIZE]) {
	return SIZE;
}

void useLambda();

void useVarInit();

class InitList;
void useInitList();

void useStructuredBinding();

void useEnum();

#endif