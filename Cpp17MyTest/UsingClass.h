#ifndef USING_CLASS_H
#define USING_CLASS_H

#include <iostream>

class HolderBase;
class Holder;

class Data {
public:
    Data() : _holderBase(nullptr){ ; }
    ~Data() {
        _holderBase = nullptr;
    }

    void Set(HolderBase* ptr);

    int Get();
    
private:
    HolderBase* _holderBase;
};

class HolderBase {
public:
    HolderBase() = default;
    ~HolderBase() = default;

    void printInfo() {
        std::cout << "HolderBase" << std::endl;
    }
};


class Holder : public HolderBase {
public:
    Holder(int _data) : data(_data) { ; }
    ~Holder() = default;

    int getData() {
        return data;
    }

private:
    int data;
};


void test_usingClass();

#endif
