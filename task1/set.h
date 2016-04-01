#ifndef _SET_LIB
#define _SET_LIB
#include <iostream>
//it is realesation of structure of data : set
//Constructos:1)default:
//            2)copy constructor
//            3)move constructor
//Overload operators:
//            1) & :Intersection A&B
//            2) + :Union of two sets
//            3) - :difference
//            4) ==: equality of two sets
//            and two operators '='(simple and move)
//Overload of I/O operators:
//             Input must be <elements of set separated by comma>
//             Output prin all element of set per line
class set{
public:
    //Constructors
    set(){
        m_size = 0;
        mem_arr = new int[0];
    }
    set(const set& other){
            int s_x = other.size();
            mem_arr = new int[s_x];
            for(int i = 0; i < s_x; i++)
                mem_arr[i] = other.mem_arr[i];
            m_size = s_x;
    }
    set(set&& r_other){
        m_size = r_other.m_size;
        mem_arr = r_other.mem_arr;
        r_other.mem_arr = nullptr;
        r_other.m_size = 0;
    }
    ~set(){delete []mem_arr;}
    int size() const {return m_size;}
    bool isEmpty();
    bool hasElement(int element) const;
    void insert(const int &element);
    void dump();
    void swap(set& second){
        std::swap(m_size, second.m_size);
        std::swap(mem_arr, second.mem_arr);
    }
    //operators
    friend set operator&(const set &A, const set &B); //intersection
    friend set operator+(const set &A, const set &B); //union
    friend set operator / (const set& A, const set& B);
    const set& operator=(const set& right){
        set tmp(right);
        this->swap(tmp);
        return *this;
    }
    const set& operator=(set&& r_right){
        if(this != &r_right){
            mem_arr = r_right.mem_arr;
            m_size = r_right.m_size;
            r_right.m_size = 0;
            r_right.mem_arr = nullptr;
        }
        return *this;
    }
    bool operator==(const set& right){
        if(right.size() != size())
            return false;
        else{
            for(int i = 0; i < size(); i++)
                if(!right.hasElement(mem_arr[i]))
                    return false;
        }
        return true;
    }
    friend std::ostream& operator<<( std::ostream&, const set&);
    friend std::istream& operator>>( std::istream&, set&);
private:
    int m_size;
    int *mem_arr;
};
#endif
