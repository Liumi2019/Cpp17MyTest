# 学习 C++ 17 特性

> 参考项目：
1. changkun/modern-cpp-tutorial: git@github.com:changkun/modern-cpp-tutorial.git

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
// { } 可以保证数据不能窄化处理
InitList l1 = { 1, 3, 6, 10 };

// 定义变量时也可以这样处理，使用 {} 代替 ()调用初始化函数
// 编译报错，不能使用 double 初始化 int
int a{5.5};

```

### 6. 结构化绑定

```C++
std::tuple t1 = { "LL", 23, "boy" };
auto [name, age, gender] = t1;
std::cout << "name:" << name << ", age: " << age << ", gender: " << gender << std::endl;

// 函数返回多个值，结构体直接直接赋值等等
struct MyPair {
	string name;
	size_t age;
};

MyPair makeMyPair() {
	MyPair temp;
	temp.name = "hello";
	temp.age = 50;
	return temp;
}
// C++ 17 结构化绑定 
auto [name, age] = makeMyPair();
// 引用类型 可以达到相互修改的目的
auto& [name, age] = myPair;

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

### 10. 左值与右值
左值引用，用于方便地传递函数的参数变量，如下：
``` C++
// 1. 引用传参，函数值变更，传入的变量同样变更
void fun(int& val) {
	val = 50;
}

int a = 0;
fun(a); // a = 50，与函数的内部的变量一起变化

// 2. 返回值，不能返回局部变量（右值使用场景），一般返回静态变量
int& getStaticPool() {
	int pool = 50;
	return pool; // 错误，局部变量自动销毁
	static int pool = 100;
	return pool;
}

```

右值引用，使用将亡值，局部值，延长变量的寿命

``` C++
// 1. 引用传参，函数值变更，传入的变量同样变更
void fun(int&& val) {
	val = 50;
}

fun(50); // 50 字面值是一个右值

// 2. 变量资源转移

int a = 50;
int &&b = std::move(a); // a 应删除

// 3. 返回值优化，返回一个局部变量
int&& getStaticPool() {
	int pool = 50;
	return std::move(pool); // 没必要，现代的编译器已经将返回值自动优化
}

// 4. 二者不一样，第一个使用移动构造函数创建一个b3对象，第二个直接使用b2的资源，没有调用构造函数
Base b3 = std::move(b2);
Base&& b3 = std::move(b2);

```

### 11. 后置类型推导

后置类型推导可用于减少定义新类型如函数类型，元编程的类型定义

``` C++
int fun(int a) {
	return a <= 0 ? -a : a;
}
// 1. 函数指针类型
auto returnFunPtr() -> int (*) (int) {
	return fun;
}

// 2. 元编程函数实现返回值
template<typename T, typename U> 
auto add(T val1, U val2) -> decltype( val1 + val2) {
	return val1 + val2;
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

## 三、C++ 多线程

### 1. 创建一个线程
C++ 多线程类 thread 类常用的构造函数：
``` C++ 
// Fn 为执行函数，Args... 可变参数
template<class Fn, class... Args>
explicit thread(Fn&& fn, Args&&... args);

// 一个例子
// 线程函数入口
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
// 创建一个线程，参数可以任意个
std::thread t1(fun_thread1, 20, isRun);

```

thread 类没有复制构造函数，但可以使用移动构造函数，将使用权转移。


``` C++

std::thread&& func_return_thread() {
	std::thread tempT3(fun_thread1, 100, true);
	// tempT3 是一个将亡值
	return std::move(tempT3);
}

std::thread t3 = func_return_thread();

``` 

### 2. 线程同步
C++ 线程同步主要依赖互斥锁、条件变量
#### 2.1 互斥锁
互斥锁头文件 mutex, 常用的互斥锁包括：递归互斥锁、定时互斥锁、自动互斥锁，互斥锁包括两个成员函数：lock() 和 unlock()。

``` C++

mtx.lock(); // 加锁
std::cout << "a = " << a << " ";
mtx.unlock(); // 解锁

```

#### 2.2 条件变量
多线程的条件变量必须依赖互斥锁才能保证线程同步，头文件：condtion_variable。

``` C++
mtx.lock(); // 加锁 
cond.wait(mtx); // 等待，传入参数 mtx，运行时自带解锁操作
mtx.unlock(); // 解锁

cond.notify(); // 发送信号
```

例子，必须保证信号的执行在等待执行后，方法是通过加锁控制。

``` C++

thread_cond::mtx.lock(); // 锁必须在信号执行线程运行之前
std::thread thread1(thread_cond::thread_notify); // 发送信号的线程
thread_cond::thread_wait(); // 等待的线程，执行时会自动解锁操作
thread_cond::mtx.unlock(); // 解锁

```


## 四、 成员函数限定符

### 4.1 const 限定符

``` C++

class MyBase {
public:
    MyBase() { std::cout << "MyBase()" << std::endl; }
    MyBase(const MyBase& myBase) {
        mAge = myBase.mAge;
        std::cout << "MyBase(const MyBase& )" << std::endl;
    }
    MyBase(const MyBase&& myBase) {
        mAge = myBase.mAge;
        std::cout << "MyBase(const MyBase&& )" << std::endl;
    }
    MyBase& operator=(const MyBase& myBase) {
        mAge = myBase.mAge;
        std::cout << "operator=(const MyBase& )" << std::endl;
        return (*this);
    }
    MyBase& operator=(const MyBase&& myBase) {
        mAge = myBase.mAge;
        std::cout << "operator=(const MyBase&& )" << std::endl;
        return (*this);
    }
    ~MyBase() { std::cout << "~MyBase()" << std::endl; }

    MyBase At(int age) const& {
        std::cout << "At() const&" << std::endl;
        MyBase temp;
        temp.mAge = age;
        return temp;
    }

    MyBase At(int age)&& {
        std::cout << "At() &&" << std::endl;
        mAge = age;
        return std::move(*this);
    }

    MyBase At(int age)& {
        std::cout << "At()&" << std::endl;
        mAge = age;
        return (*this);
    }

private:
    int mAge;

};

// 返回一个 MyBase 对象
MyBase makeMyBase() {
	std::cout << "makeMyBase" << std::endl;
	return MyBase();
}
void test_qualifier() {
	MyBase myBase1;
	MyBase& myBase1_ref = myBase1;
	const MyBase& myBase1_cref = myBase1;
	
	MyBase myBase2 = myBase1_ref.At(0);  // 调用 At() &
	MyBase myBase2_ref = myBase1_ref.At(10);  // 调用 At() &
	MyBase myBase2_cref = myBase1_cref.At(20);  // 调用 At() const&
	// makeMyBase() 返回一个临时对象调用 At 成员函数
	MyBase myBase2_rref = makeMyBase().At(30);  // 调用 At()&&
}

```

## 五、不能实例化的类

### 5.1 纯虚类

包含纯虚函数的类不能实例化，且子类必须全部实现才能实例化

``` C++

class base {
public:
	base() {;}
	~base() {;}
	void setNum(int num) = 0; // 纯虚函数
};

```

### 5.2 构造函数、析构函数为私有
不能实例化，不能派生子类

``` C++

class base {
public:
	base() {;}
private:
	~base() {;}
};

```

### 5.3 析构函数为纯虚函数

不能实例化，可以派生子类，且子类也不可实例化

``` C++

class base {
public:
	base() {;}
	virtual ~base() = 0;
};

```

## 六、内存泄漏
使用 detach 分离线程可能导致线程泄漏