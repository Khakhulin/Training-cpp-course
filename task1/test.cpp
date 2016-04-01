#include "set.h"
set ret_Value(){
    set obj;
    return obj;
}

int main(){
    set myset;
    myset.insert(5);
    myset.insert(3);
    myset.dump();
    set A;
    set B,C;
    std::string str;
    std::cin >> A >> B >> C;
    set Set;
    std::cout << "set A::\n" << A <<  "setB::\n";
    std::cout << B << "setC::\n" << C << std::endl;
    Set = A + B;

    std::cout << Set << std::endl;
    //Set = B;
    return 0;
}
