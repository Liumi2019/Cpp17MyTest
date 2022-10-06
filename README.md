# 学习 C++ 17 特性

> 参考项目：
1. changkun/modern-cpp-tutorial:
git@github.com:changkun/modern-cpp-tutorial.git

> 学习笔记
* github 地址: git@github.com:Liumi2019/Cpp17MyTest.git
* 时间: 2022/9/17
* 地点: 北京

## 一、C++ 新特性

### 1. 类型自动推导
```C++
// old
std::vector<int> a = {1, 2};

// C++ 17
std::vector a = {1, 2};
```

### 2. C++ Lambda 表达式

```C++
[ 捕获列表 ]( 参数 ){ 函数体 } -> ret { 类型推断 } 

[out = std::ref(std::cout << "hello world!")] () {
    out.get() << "end" << std::endl;
};
// 执行结果：hello world!

[out = std::ref(std::cout << "hello world!")] () {
    out.get() << " end" << std::endl;
}();
// 执行结果：hello world! end

```
多了一个 () 结果不一样。

### 3. 常量表达式

constexpr 类似于 1 + 2 + 3 表达式，数组初始化必须使用常量表达式才可以即：
``` C++
#define len_5 5
const int len_const_5 = 5;
constexpr int len_constexpr_5 = 5;

int arr[10];
int arr2[1+3];
int arr3[len_5];
int arr4[len_const_5]; // 不合法
int arr5[len_constexpr_5]; // 合法

```

### 4. if/switch 变量强化

```C++
	int a = 5;
	int b = 6;
	if (int c = a + b; c > 10) {
		std::cout << "c > 10" << std::endl;
	}
	// c = 0; // 属于局部变量

```

### 5. 初始化列表

```C++

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

InitList l1 = { 1, 3, 6, 10 };

```

### 6. 结构化绑定

```C++
	std::tuple t1 = { "LL", 23, "boy" };
	auto [name, age, gender] = t1;
	std::cout << "name:" << name << ", age: " << age << ", gender: " << gender << std::endl;

```

### 7. 自动类型推导

```C++
// 迭代器类型名称过长 使用auto 推断
std::vector<int>::iterator it = vec.begin();
auto it = vec.begin();

// decltype( 表达式 ) 推算类型 在函数编写时作为返回值推断
decltype(5 + 6) x;
int x;

// -> 尾部类型推导
template<typename T, typename U>
auto add(T x, U y) -> decltype(x + y)

// 高级用法
decltype(auto) func() {// 用于完美转发；
	return func1();  // 返回类型与 func1() 一致
}

```

### 8. 控制流
将模板特化简化成不同的条件语句执行，模板更简洁
```C++

// if constexpr() 决定函数执行那些语句
template<typename T> 
auto add(T x) {
	if constexpr(std::is_integral<T>::value) {
		return x + 1;
	} else {
		return x + 0.1;
	}
}

```

### 9. 变参数模板

```C++
template<typename... Ts>
void func(int a, Ts... args);  // 至少输入一个参数
sizeof...(args);  // 推断出有几个参数

// 如何展开变参数模板
// 1. 递归调用
template<typename T>
void func1(T a);
template<typename T, typename... Ts>
void func1(T a0, Ts... a) {
	std::cout << a0;
	func1(a...);
}

// 2. 变模板展开
template<typename T, typename... Ts>
void func1(T a0, Ts... a) {
	std::cout << a0;
	if constexpr(sizeof...(Ts) > 0) func1(a...);
}

// 3. 初始化列表展开
template<typename T, typename... Ts>
void func1(T a0, Ts... a) {
	std::cout << a0;
	void std::initializer_list<T>{
		([&a]{
			std::cout << a;
		}(), a0)...
	}
}

```


## 二、Lambda 表达式

### 1. 捕获列表
#### 1.1 值捕获
值捕获只补获当前值，

``` C++
void lambdaValue() {
	int a = 50;
	auto aPrint = [a](int b) { return a + b; };

	a = 100;
	std::cout << aPrint(60) << std::endl;  // 110 不是 160
}

```

#### 1.2 引用捕获
根据值的变化而变化

``` C++
void lambdaValue() {
	int a = 50;
	auto aPrint = [&a](int b) { return a + b; };

	a = 100;
	std::cout << aPrint(60) << std::endl;  // 160
}

```

#### 1.3 泛型捕获
允许使用任意类型，C++14可用

```C++
	auto a = [](auto x, auto y) {  // C++ 14 之后支持
		return x + y;
	};
```

### 2. 函数包容器

函数类型

```C++
using func = void(int);
void print1(int a) {
	std::cout << a << std::endl;
}
func = print1;  // 函数类型
func(20);

std::vector<std::functional<void(int)>> funcF = { print1 };
funcF[0](20);  // 使用数组管理函数对象

```



