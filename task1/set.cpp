#include "set.h"

bool set::hasElement(int element) const{
    for (int i = 0; i < set::size(); i++){
        if(element == mem_arr[i])
            return true;
    }
    return false;
}

void set::insert(const int &element){
    if(hasElement(element) == true)
        return;
    m_size++;
    int* tmp = mem_arr;
    mem_arr = new int[m_size];
    for(int  i = 0; i < m_size - 1; i++){
        mem_arr[i] = tmp[i];
    }
    delete []tmp;
    mem_arr[m_size - 1] = element;
    return;
}
void set::dump(){
    for(int i = 0; i < set::size(); i++)
        std::cout << mem_arr[i] << std::endl;
}
//**********Operators********//
set operator&(const set& A, const set& B){
    set tmp;
    for(int i = 0; i < A.size(); i++){
        if(B.hasElement(A.mem_arr[i]))
            tmp.insert(A.mem_arr[i]);
    }
    return tmp;
}
set operator+(const set& A, const set& B){
    set tmp;
    for(int i = 0; i < A.size(); i++){
            tmp.insert(A.mem_arr[i]);
    }
    for(int i = 0; i < B.size(); i++){
            tmp.insert(B.mem_arr[i]);
    }
    return tmp;
}

set operator/(const set& A, const set& B){
    set tmp ;
    for(int i = 0;i < A.size(); i++){
        if(!B.hasElement(A.mem_arr[i])){
            tmp.insert(A.mem_arr[i]);
        }
    }
    return tmp;
}

std::ostream& operator<<( std::ostream& os, const set& m_set){
    for(int i = 0; i < m_set.size(); i++){
        os << m_set.mem_arr[i] << std::endl;
    }
    return os;
}
std::istream& operator>>( std::istream& is, set& m_set){
    int value = 0;
    char ch;
    while ((ch = is.get()) != '<');
    while(is >> value){
        m_set.insert(value);
        ch = is.get();
        if(ch == '>')
            break;
    }
    return is;
}
bool set::isEmpty(){
    if (m_size == 0)
        return true;
    return false;
}
