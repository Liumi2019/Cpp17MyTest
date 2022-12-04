#include "Cpp17RightValue.h"
#include <iostream>
#include <string>
#include <memory>

namespace test_right_value {

    void printMessage(std::string str) {
        std::cout << str << std::endl;
    }

    class Base {
    public:
        Base() : a(0) {
            printMessage("Base");
        }

        Base(const Base& base) {
            this->a = base.a;
            printMessage("Base(const Base&)");
        }

        Base& operator==(const Base& base) {
            this->a = base.a;
            printMessage("operator==(const Base&)");
            return *this;
        }

        Base(const Base&& base) {
            this->a = base.a;
            printMessage("Base(const Base&&)");
        }

        Base& operator==(const Base&& base) {
            this->a = base.a;
            printMessage("operator==(const Base&&)");
            return *this;
        }

        ~Base() {
            printMessage("~Base");
        }

        void setA(int a) {
            this->a = a;
        }

        int getA() {
            return this->a;
        }

    private:
        int a;
    };

    Base makeBase() {
        Base b;
        b.setA(-50);
        std::cout << "makeBase " << b.getA() << std::endl;
        return b;
    }

    Base* makeBasePool() {
        Base* bpool = new Base[3];
        bpool[0].setA(20);
        bpool[1].setA(30);
        bpool[2].setA(40);
        return bpool;
    }

    void test1() {
        // printMessage("b1");
        // Base b1(makeBase());
        // std::cout << b1.getA() << std::endl;
        printMessage("b2");
        Base b2 = makeBase();
        Base b3 = makeBase();
        std::cout << b2.getA() << std::endl;
    }

    void test2() {
        Base* p = makeBasePool();
        std::cout << p->getA() << std::endl;
        std::cout << (p + 1)->getA() << std::endl;
        std::cout << (p + 2)->getA() << std::endl;
        delete[] p;

        Base b2;
        b2.setA(80);
        Base b3 = std::move(b2);
        std::cout << b3.getA() << std::endl;
    }


    void test_right_value() {
        test1();
        // test2();
    }
}
