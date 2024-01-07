#ifndef CPP17_NEW_FEATURE_H
#define CPP17_NEW_FEATURE_H

#include <iostream>
#include <vector>

// C++17 vector 类型自动推导
// vector<int> a = {1, 2}; -> vector a = {1, 2};
void testVector();

// 初始化字符串常量
void initChar();

void printChar(char* chr, const size_t& size);

// 模板数组引用
template <class T, size_t SIZE>
size_t arrySize(T(&a)[SIZE]) {
	return SIZE;
}

// for 语句语法加强
void useVarInit();

// 初始化列表
class InitList;

void useInitList();

// 容器绑定
void useStructuredBinding();

// 枚举类型转换
void useEnum();

#endif