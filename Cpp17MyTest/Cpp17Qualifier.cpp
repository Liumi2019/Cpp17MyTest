#include "Cpp17Qualifier.h"

namespace test_qualifier {
    MyBase makeMyBase() {
        std::cout << "makeMyBase" << std::endl;
        return MyBase();
    }
    void test_qualifier() {
        MyBase myBase1;
        MyBase& myBase1_ref = myBase1;
        const MyBase& myBase1_cref = myBase1;
        
        MyBase myBase2 = myBase1_ref.At(0);
        MyBase myBase2_ref = myBase1_ref.At(10);
        MyBase myBase2_cref = myBase1_cref.At(20);
        MyBase myBase2_rref = makeMyBase().At(30);

        myBase1_ref.printClass();
        myBase1_ref.At(200).printClass();
    }
}