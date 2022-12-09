#ifndef CPP17_QUALIFIER_H
#define CPP17_QUALIFIER_H

#include <iostream>

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

    void printClass() {
        std::cout << "MyBase: " << mAge << std::endl;
    }
private:
    int mAge = -1;

};

namespace test_qualifier {
    void test_qualifier();
}

#endif