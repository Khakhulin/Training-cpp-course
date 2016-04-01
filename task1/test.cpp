#include "set.h"
set ret_Value(){
    set obj;
    return obj;
}

int main(){
    set A;
    set B,C;
    A.insert(1);
    A.insert(2);
    A.insert(3);
    B.insert(4);
    B.insert(5);
    B.insert(6);
    B.insert(7);
    set Set;
    std::cout << "set  A" << A <<  "setB::\n";
    std::cout << B << "setC::\n" << C << std::endl;
    Set = A + B;
    std::cout << Set << std::endl;
    //Set = B;
    return 0;
}
